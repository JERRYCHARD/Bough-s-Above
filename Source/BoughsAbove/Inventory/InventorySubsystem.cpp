#include "InventorySubsystem.h"

bool UInventorySubsystem::OwnsUnit(FName UnitID) const
{
	for (const FOwnedUnit& Owned : OwnedUnits)
	{
		if (Owned.UnitID == UnitID)
		{
			return true;
		}
	}
	return false;
}

FOwnedUnit* UInventorySubsystem::FindOwnedUnit(FName UnitID)
{
	return OwnedUnits.FindByPredicate([UnitID](const FOwnedUnit& Owned)
		{
			return Owned.UnitID == UnitID;
		});
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