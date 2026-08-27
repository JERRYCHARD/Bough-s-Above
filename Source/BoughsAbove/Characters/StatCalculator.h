#pragma once

#include "CoreMinimal.h"
#include "UnitStats.h"
#include "StatGrowthConfig.h"
#include "StatCalculator.generated.h"

UCLASS()
class BOUGHSABOVE_API UStatCalculator : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Stats")
	static FUnitStats CalculateStats(const FUnitStats& BaseStats, int32 StarLevel, const FStatGrowthConfig& GrowthConfig);
};
