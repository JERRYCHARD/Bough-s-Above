#include "GachaRarityTable.h"

const FRarityConfig* UGachaRarityTable::FindConfig(ERarityTier Tier) const
{
	return Rarities.FindByPredicate([Tier](const FRarityConfig& Config)
		{
			return Config.Tier == Tier;
		});
}

int32 UGachaRarityTable::GetShardsToTierUp(ERarityTier Tier) const
{
	const FRarityConfig* Config = FindConfig(Tier);
	return Config ? Config->ShardsToTierUp : 0;
}