#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GearTypes.h"
#include "GearDatabase.h"
#include "OwnedGear.h"
#include "../Gacha/GachaSubsystem/RarityTypes.h"
#include "GearSubsystem.generated.h"

UCLASS()
class BOUGHSABOVE_API UGearSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gear")
	UGearDatabase* GearDatabase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gear")
	TArray<FOwnedGear> OwnedGear;

	UFUNCTION(BlueprintCallable, Category = "Gear")
	bool TryPurchaseGear(FName GearID);

	UFUNCTION(BlueprintCallable, Category = "Gear")
	bool TryEquipGear(FName UnitID, FName GearID);

	UFUNCTION(BlueprintCallable, Category = "Gear")
	void UnequipGear(FName UnitID, EGearSlot Slot);

	UFUNCTION(BlueprintCallable, Category = "Gear")
	TArray<FStatModifier> GetEquippedModifiers(FName UnitID) const;
};
