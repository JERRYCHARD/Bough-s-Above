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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	FName TraitSlot1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	FName TraitSlot2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	int32 ActiveTraitSlot = 1;
};