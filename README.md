# Boughs Above — Design Reference

Captures the planning session covering character stats, permanent vs.
match-scoped data, server architecture direction, and next-steps
sequencing. Still open to revision as systems get built.

---

## Roadmap / sequencing

Already built: rarity/pity, unit selection, inventory (shards/gold/gems),
save/load, `SummonSubsystem`.

Agreed next steps, in order:

1. **Character stat system** (design + code)
2. **Main menu UI**
3. **Summoning UI**
4. **Inventory UI** — displays a unit's stats, which is why stats needed
   to come first

Art (sprites, portraits) comes after the UI screens exist with
placeholders — building UI first defines the actual art requirements
(sizes, how many visual slots a unit needs) rather than guessing.

Blocked until character stats exist: traits, gear system, combat loop.

Deferred / backlog (not urgent, noted for later): daily/weekly
login rewards, banner system (for featured/rotating Champions),
account level, shops, friends system, guild system.

---

## Character stat block

Per-unit base stats:

- Physical Damage
- Magic Damage
- Range
- Attack Speed
- HP
- Defense (physical)
- Magic Defense
- Crit Chance
- Crit Damage

Higher rarity tiers have higher base stats. Higher-rarity units are
much harder to obtain through the in-match shop system specifically
(scarcity is enforced there, separate from gacha odds).

## Stat modifier layers (stack in this order)

1. **Base stats** — from rarity tier
2. **Star level** — linear stat growth as a unit stars up. Passive
   ability unlocks specifically at 3-star and 6-star (not every level)
3. **Merge tier (Copper → Silver → Gold)** — match-scoped, not saved.
   Stats increase on a curve, not linearly — 1 Silver is stronger than
   3 Copper. Resets each match, same idea as combining copies in TFT
4. **Attributes** (e.g. Brawler / Mage-style tags) — bonuses scale with
   how many units sharing an attribute are on the field at once.
   Calculated at match/formation time, not stored on the unit
5. **Gear** — weapon slot + armor slot (kept simple, 2 slots total)
6. **Trait** — see Trait system below

Calculation approach: store base data, then calculate outward through
star level → merge tier → attributes → gear → trait at the point stats
are actually needed (not baked into save data beyond star level, gear,
and traits).

---

## Trait system

Permanent (saved), like star level and gear.

- A unit can **hold 2 traits** at once
- The player can **switch between them** — lets the player pick which
  of the two held traits is active without re-rolling
- **Trait rolling is a separate action from summoning** — a unit is
  never summoned already carrying a trait (that idea has been
  scrapped); traits are rolled independently, on their own
- Reasoning: the rarest trait tier is capped at **1 unit per player's
  loadout** at a time (a per-player limit, not a global/contested
  one — mirrors the "only 1 Champion" and other per-tier cap patterns
  elsewhere in the design), so the 2-trait-hold-and-switch system gives
  players customization flexibility without making that scarcity feel
  overly punishing

---

## Permanent vs. match-scoped — the key data split

**Permanent (saved to player data):**
- Unit ownership (`FOwnedUnit` — already built)
- Star level per unit
- Gear per unit (once gear system exists)
- **Traits per unit** — see Trait system above
- **Loadout** — see below

**Match-scoped (never saved, exists only during a live match):**
- Merge tier (copper/silver/gold)
- Field limits per rarity (board caps, e.g. "max 3 Champions on the
  field" — same "each rarity has its own independent cap" pattern that
  shows up in shard caps and loadout composition)
- Bench — purely match-scoped, holding area during a live match for
  owned-but-not-fielded units (confirmed no persistent behavior)
- Attribute synergy bonuses
- Shop card effects (see below)

## Loadout

A permanent, player-configured selection of which owned units are
available to summon/draft in a match — separate from just *owning* a
unit. Structured **per rarity slot**, not a flat list:

- X of one rarity, Y of another, etc.
- **Champion is capped at exactly 1**
- Not every rarity slot needs to be filled to start a game

### New account seeding
- New accounts are given starter units: **one unit each of the first
  two rarities** (lowest tiers)
- Only **one unit of the first (lowest) rarity** is actually required
  to start a game — the rest of the loadout can be empty

## In-match shop & cards

- Sells cards (not units directly tied to merge tier — cards never
  change what merge tier a summoned unit starts at; summoned units are
  always Copper)
- Card effects are **match-wide rule modifiers**, not per-unit stats —
  e.g. increasing an attribute's bonus strength, or raising the max
  Champions allowed on the field
- This is a different data shape than gear: gear modifies one unit,
  cards modify match-wide rules/state

---

## Server / save architecture direction

Current local save (`SaveSubsystem`, `USaveGame`) is scoped as a
**placeholder for pre-server development** — not meant to be the
permanent architecture once real accounts/servers exist.

### Why: anti-manipulation for PvP + Monetization
Once servers exist, client-side save data can never be trusted as the
source of truth for anything that affects gameplay outcomes (this
matters once PvP and monetization are live — a modified client
shouldn't be able to fake results).

### The target model (server-authoritative)
- Local save either goes away or becomes a display-only cache — never
  trusted for gameplay-affecting state
- Client sends a *request* for an action (e.g. "summon once") — it
  never calculates the outcome itself and reports it
- The **server** is what actually rolls rarity, checks/deducts
  currency, updates inventory, and returns the result
- Client only ever renders what the server says happened
- Preferred pattern: server pushes an authoritative update after each
  action; client doesn't need to poll/re-fetch on a timer

### Why current architecture is already positioned well for this
`SummonSubsystem`, `GachaSubsystem`, and `InventorySubsystem` are
written as self-contained logic with no assumption about *where* they
run. The eventual migration is about relocating *where this logic
executes* (client → server), not redesigning *how it works*.

**Working principle going forward:** keep all gameplay-affecting logic
in C++ subsystems like these — never in Blueprint graphs or client-only
UI code. Blueprint/UI stays permanently client-side as the presentation
layer; these subsystems are the pieces that eventually move server-side.

---

## Open questions / things to settle later (not urgent)

- Exact loadout composition numbers (how many of each rarity slot)
- Exact card pool / what specific match-wide modifiers exist
- Exact trait pool / trait tier list and what each trait does
- How attribute synergy thresholds/bonuses scale with unit count
- Exact star-level stat growth formula (confirmed linear, exact
  numbers not yet set)
- Exact merge-tier stat curve (confirmed non-linear, "1 Silver > 3
  Copper," exact curve not yet set)
