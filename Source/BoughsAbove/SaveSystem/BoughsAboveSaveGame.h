#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "../Inventory/OwnedUnit.h"
#include "../Gacha/GachaSubsystem/RarityTypes.h"
#include "BoughsAboveSaveGame.generated.h"

UCLASS()
class BOUGHSABOVE_API UBoughsAboveSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Save")
	TArray<FOwnedUnit> OwnedUnits;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Save")
	TMap<ERarityTier, int32> ShardsByTier;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Save")
	int32 Gold = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Save")
	int32 Gems = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Save")
	TMap<ERarityTier, int32> PityCounters;
};
