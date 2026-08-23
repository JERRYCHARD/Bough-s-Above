#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BoughsAboveSaveGame.h"
#include "../Inventory/InventorySubsystem.h"
#include "../Gacha/GachaSubsystem/GachaSubsystem.h"
#include "SaveSubsystem.generated.h"

UCLASS()
class BOUGHSABOVE_API USaveSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Save")
	FString SaveSlotName = "PlayerSave";

	UFUNCTION(BlueprintCallable, Category = "Save")
	void SaveGame();

	UFUNCTION(BlueprintCallable, Category = "Save")
	void LoadGame();
};
