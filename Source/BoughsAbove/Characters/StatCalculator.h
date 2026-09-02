#pragma once

#include "CoreMinimal.h"
#include "UnitStats.h"
#include "StatGrowthConfig.h"
#include "../Gear/GearTypes.h"
#include "StatCalculator.generated.h"

UCLASS()
class BOUGHSABOVE_API UStatCalculator : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Stats")
	static FUnitStats CalculateStats(const FUnitStats& BaseStats, int32 StarLevel, const FStatGrowthConfig& GrowthConfig, const TArray<FStatModifier>& GearModifiers);

	static void ApplyModifier(FUnitStats& Stats, const FStatModifier& Modifier);
};