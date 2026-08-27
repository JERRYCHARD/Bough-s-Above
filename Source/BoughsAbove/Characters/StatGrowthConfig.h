#pragma once

#include "CoreMinimal.h"
#include "StatGrowthConfig.generated.h"

USTRUCT(BlueprintType)
struct FStatGrowthConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Growth")
	float PhysicalDamageGrowthPercent = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Growth")
	float MagicDamageGrowthPercent = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Growth")
	float AttackSpeedGrowthPercent = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Growth")
	float HPGrowthPercent = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Growth")
	float DefenseGrowthPercent = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Growth")
	float MagicDefenseGrowthPercent = 10.f;
};
