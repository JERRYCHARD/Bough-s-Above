#pragma once

#include "CoreMinimal.h"
#include "OwnedGear.generated.h"

USTRUCT(BlueprintType)
struct FOwnedGear
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gear")
	FName GearID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gear")
	FName EquippedToUnitID;
};
