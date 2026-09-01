#pragma once

#include "CoreMinimal.h"
#include "../Gacha/GachaSubsystem/RarityTypes.h"
#include "InventoryDisplayEntry.generated.h"

USTRUCT(BlueprintType)
struct FInventoryDisplayEntry
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	FName UnitID;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	FText DisplayName;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	int32 StarLevel = 0;

	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
	ERarityTier Tier = ERarityTier::Novice;
};
