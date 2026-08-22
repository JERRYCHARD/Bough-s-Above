#include "UnitDatabase.h"

TArray<FUnitData> UUnitDatabase::GetUnitsForTier(ERarityTier Tier) const
{
	TArray<FUnitData> Result;

	for (const FUnitData& Unit : Units)
	{
		if (Unit.Tier == Tier)
		{
			Result.Add(Unit);
		}
	}

	return Result;
}
