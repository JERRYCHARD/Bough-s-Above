#pragma once

#include "CoreMinimal.h"
#include "../GachaSubsystem/RarityTypes.h"
#include "../../Characters/UnitStats.h"
#include "UnitTypes.generated.h"

USTRUCT(BlueprintType)
struct FUnitData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
    FName UnitID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	ERarityTier Tier = ERarityTier::Novice;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	FUnitStats BaseStats;
};
