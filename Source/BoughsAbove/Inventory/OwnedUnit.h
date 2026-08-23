#pragma once

#include "CoreMinimal.h"
#include "OwnedUnit.generated.h"

USTRUCT(BlueprintType)
struct FOwnedUnit
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	FName UnitID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	int32 Level = 1;
};