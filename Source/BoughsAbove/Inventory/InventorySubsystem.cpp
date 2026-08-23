#include "InventorySubsystem.h"

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
		NewUnit.Level = 1;
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

