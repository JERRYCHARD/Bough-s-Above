#include "CurrencySubsystem.h"

bool UCurrencySubsystem::TrySpendGems(int32 Amount)
{
	if (Gems < Amount)
	{
		return false;
	}

	Gems -= Amount;
	return true;
}

void UCurrencySubsystem::AddGems(int32 Amount)
{
	Gems += Amount;
}

void UCurrencySubsystem::AddShardsForDuplicate(ERarityTier Tier)
{
	if (!RarityTable)
	{
		return;
	}

	const FRarityConfig* Config = RarityTable->FindConfig(Tier);
	if (!Config)
	{
		return;
	}

	int32& CurrentShards = ShardsByTier.FindOrAdd(Tier);

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

bool UCurrencySubsystem::TrySpendShards(ERarityTier Tier, int32 Amount)
{
	int32* CurrentShards = ShardsByTier.Find(Tier);
	if (!CurrentShards || *CurrentShards < Amount)
	{
		return false;
	}

	*CurrentShards -= Amount;
	return true;
}

int32 UCurrencySubsystem::GetShardCount(ERarityTier Tier) const
{
	const int32* CurrentShards = ShardsByTier.Find(Tier);
	return CurrentShards ? *CurrentShards : 0;
}