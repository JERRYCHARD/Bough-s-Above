#pragma once

#include "CoreMinimal.h"
#include "../Gear/GearTypes.h"
#include "OwnedUnit.generated.h"

USTRUCT(BlueprintType)
struct FOwnedUnit
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	FName UnitID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	int32 StarLevel = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	FEquippedGear EquippedGear;
};