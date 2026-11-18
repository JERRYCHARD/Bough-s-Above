#include "InventorySubsystem.h"
#include "CurrencySubsystem.h"
#include "../Characters/StatCalculator.h"
#include "../Gear/GearSubsystem.h"
#include "../Traits/TraitSubsystem.h"

const FOwnedUnit* UInventorySubsystem::FindOwnedUnit(FName UnitID) const
{
	return OwnedUnits.FindByPredicate([UnitID](const FOwnedUnit& Owned)
		{
			return Owned.UnitID == UnitID;
		});
}

bool UInventorySubsystem::OwnsUnit(FName UnitID) const
{
	return FindOwnedUnit(UnitID) != nullptr;
}

void UInventorySubsystem::AddUnit(const FUnitData& Unit)
{
	if (!OwnsUnit(Unit.UnitID))
	{
		FOwnedUnit NewUnit;
		NewUnit.UnitID = Unit.UnitID;
		NewUnit.StarLevel = 0;
		OwnedUnits.Add(NewUnit);
		return;
	}

	if (UGameInstance* GI = GetGameInstance())
	{
		if (UCurrencySubsystem* Currency = GI->GetSubsystem<UCurrencySubsystem>())
		{
			Currency->AddShardsForDuplicate(Unit.Tier);
		}
	}
}

FUnitStats UInventorySubsystem::GetCalculatedStats(FName UnitID) const
{
	const FOwnedUnit* Owned = FindOwnedUnit(UnitID);
	if (!Owned || !UnitDatabase)
	{
		return FUnitStats();
	}

	for (const FUnitData& Unit : UnitDatabase->Units)
	{
		if (Unit.UnitID == UnitID)
		{
			TArray<FStatModifier> AllModifiers;

			if (UGameInstance* GI = GetGameInstance())
			{
				if (UGearSubsystem* Gear = GI->GetSubsystem<UGearSubsystem>())
				{
					AllModifiers.Append(Gear->GetEquippedModifiers(UnitID));
				}

				if (UTraitSubsystem* Traits = GI->GetSubsystem<UTraitSubsystem>())
				{
					const FName ActiveTraitID = (Owned->ActiveTraitSlot == 2) ? Owned->TraitSlot2 : Owned->TraitSlot1;

					if (!ActiveTraitID.IsNone() && Traits->TraitDatabase)
					{
						if (const FTraitData* ActiveTrait = Traits->TraitDatabase->FindTrait(ActiveTraitID))
						{
							AllModifiers.Append(ActiveTrait->StatModifiers);
						}
					}
				}
			}

			return UStatCalculator::CalculateStats(Unit.BaseStats, Owned->StarLevel, GrowthConfig, AllModifiers);
		}
	}

	return FUnitStats();
}

TArray<FInventoryDisplayEntry> UInventorySubsystem::GetOwnedUnitsByTier(ERarityTier Tier) const
{
	TArray<FInventoryDisplayEntry> Result;

	if (!UnitDatabase)
	{
		return Result;
	}

	for (const FOwnedUnit& Owned : OwnedUnits)
	{
		const FUnitData* UnitDef = UnitDatabase->Units.FindByPredicate([&Owned](const FUnitData& Unit)
			{
				return Unit.UnitID == Owned.UnitID;
			});

		if (UnitDef && UnitDef->Tier == Tier)
		{
			FInventoryDisplayEntry Entry;
			Entry.UnitID = Owned.UnitID;
			Entry.DisplayName = UnitDef->DisplayName;
			Entry.StarLevel = Owned.StarLevel;
			Entry.Tier = Tier;
			Entry.Attributes = UnitDef->Attributes;
			Result.Add(Entry);
		}
	}

	return Result;
}

bool UInventorySubsystem::TryStarUpUnit(FName UnitID)
{
	FOwnedUnit* Owned = OwnedUnits.FindByPredicate([UnitID](const FOwnedUnit& Unit)
		{
			return Unit.UnitID == UnitID;
		});

	if (!Owned || Owned->StarLevel >= 6 || !RarityTable || !UnitDatabase)
	{
		return false;
	}

	const FUnitData* UnitDef = UnitDatabase->Units.FindByPredicate([UnitID](const FUnitData& Unit)
		{
			return Unit.UnitID == UnitID;
		});

	if (!UnitDef)
	{
		return false;
	}

	const FRarityConfig* Config = RarityTable->FindConfig(UnitDef->Tier);
	if (!Config)
	{
		return false;
	}

	UGameInstance* GI = GetGameInstance();
	UCurrencySubsystem* Currency = GI ? GI->GetSubsystem<UCurrencySubsystem>() : nullptr;

	if (!Currency || !Currency->TrySpendShards(UnitDef->Tier, Config->ShardsToTierUp))
	{
		return false;
	}

	Owned->StarLevel += 1;
	return true;
}

FInventoryDisplayEntry UInventorySubsystem::GetUnitDisplayInfo(FName UnitID) const
{
	FInventoryDisplayEntry Entry;

	const FOwnedUnit* Owned = FindOwnedUnit(UnitID);
	if (!Owned || !UnitDatabase)
	{
		return Entry;
	}

	const FUnitData* UnitDef = UnitDatabase->Units.FindByPredicate([UnitID](const FUnitData& Unit)
		{
			return Unit.UnitID == UnitID;
		});

	if (UnitDef)
	{
		Entry.UnitID = UnitID;
		Entry.DisplayName = UnitDef->DisplayName;
		Entry.StarLevel = Owned->StarLevel;
		Entry.Tier = UnitDef->Tier;
		Entry.Attributes = UnitDef->Attributes;
	}

	return Entry;
}

FOwnedUnit UInventorySubsystem::GetOwnedUnit(FName UnitID) const
{
	if (const FOwnedUnit* Found = FindOwnedUnit(UnitID))
	{
		return *Found;
	}

	return FOwnedUnit();
}