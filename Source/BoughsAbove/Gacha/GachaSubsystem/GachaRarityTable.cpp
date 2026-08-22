#include "GachaRarityTable.h"

const FRarityConfig* UGachaRarityTable::FindConfig(ERarityTier Tier) const
{
	return Rarities.FindByPredicate([Tier](const FRarityConfig& Config)
		{
			return Config.Tier == Tier;
		});
}