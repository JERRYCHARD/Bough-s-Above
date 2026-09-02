#include "InventorySubsystem.h"
#include "CurrencySubsystem.h"
#include "../Characters/StatCalculator.h"
#include "../Gear/GearSubsystem.h"

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
			TArray<FStatModifier> GearModifiers;

			if (UGameInstance* GI = GetGameInstance())
			{
				if (UGearSubsystem* Gear = GI->GetSubsystem<UGearSubsystem>())
				{
					GearModifiers = Gear->GetEquippedModifiers(UnitID);
				}
			}

			return UStatCalculator::CalculateStats(Unit.BaseStats, Owned->StarLevel, GrowthConfig, GearModifiers);
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