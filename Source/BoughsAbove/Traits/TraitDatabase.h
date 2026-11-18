#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TraitTypes.h"
#include "TraitDatabase.generated.h"

UCLASS(BlueprintType)
class BOUGHSABOVE_API UTraitDatabase : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trait")
	TArray<FTraitData> Traits;

	TArray<FTraitData> GetTraitsForTier(ETraitTier Tier) const;
	const FTraitData* FindTrait(FName TraitID) const;
};
