#include "InventorySubsystem.h"
#include "../Characters/StatCalculator.h"

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

	if (!RarityTable)
	{
		return;
	}

	const FRarityConfig* Config = RarityTable->FindConfig(Unit.Tier);
	if (!Config)
	{
		return;
	}

	int32& CurrentShards = ShardsByTier.FindOrAdd(Unit.Tier);

	if (CurrentShards < Config->ShardCap)
	{
		CurrentShards += 1;
		Gold += Config->DuplicateGoldReward;
	}
	else
	{
		Gold += Config->CappedShardGoldReward;
	}
}

bool UInventorySubsystem::TrySpendGems(int32 Amount)
{
	if (Gems < Amount)
	{
		return false;
	}

	Gems -= Amount;
	return true;
}

void UInventorySubsystem::AddGems(int32 Amount)
{
	Gems += Amount;
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
			return UStatCalculator::CalculateStats(Unit.BaseStats, Owned->StarLevel, GrowthConfig);
		}
	}

	return FUnitStats();
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

	int32* CurrentShards = ShardsByTier.Find(UnitDef->Tier);
	if (!CurrentShards || *CurrentShards < Config->ShardsToTierUp)
	{
		return false;
	}

	*CurrentShards -= Config->ShardsToTierUp;
	Owned->StarLevel += 1;
	return true;
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