#include "TraitDatabase.h"

TArray<FTraitData> UTraitDatabase::GetTraitsForTier(ETraitTier Tier) const
{
	TArray<FTraitData> Result;

	for (const FTraitData& Trait : Traits)
	{
		if (Trait.Tier == Tier)
		{
			Result.Add(Trait);
		}
	}

	return Result;
}

const FTraitData* UTraitDatabase::FindTrait(FName TraitID) const
{
	return Traits.FindByPredicate([TraitID](const FTraitData& Trait)
		{
			return Trait.TraitID == TraitID;
		});
}