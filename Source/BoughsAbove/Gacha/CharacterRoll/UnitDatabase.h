#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UnitTypes.h"
#include "UnitDatabase.generated.h"

UCLASS(BlueprintType)
class BOUGHSABOVE_API UUnitDatabase : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Units")
	TArray<FUnitData> Units;

	TArray<FUnitData> GetUnitsForTier(ERarityTier Tier) const;
};
