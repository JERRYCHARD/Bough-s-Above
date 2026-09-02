#pragma once

#include "CoreMinimal.h"
#include "StatType.h"
#include "StatModifier.generated.h"

USTRUCT(BlueprintType)
struct FStatModifier
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modifier")
	EUnitStatType Stat = EUnitStatType::PhysicalDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Modifier")
	float Amount = 0.f;
};
