#pragma once

#include "CoreMinimal.h"
#include "UnitStats.generated.h"

USTRUCT(BlueprintType)
struct FUnitStats
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float PhysicalDamage = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float MagicDamage = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float Mana = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 Range = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float AttackSpeed = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float HP = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float Defense = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float MagicDefense = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float CritChance = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	float CritDamage = 0.f;
};
