#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "RarityTypes.h"
#include "GachaRarityTable.generated.h"

UCLASS(BlueprintType)
class BOUGHSABOVE_API UGachaRarityTable : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rarity")
	TArray<FRarityConfig> Rarities;

	const FRarityConfig* FindConfig(ERarityTier Tier) const;
};
