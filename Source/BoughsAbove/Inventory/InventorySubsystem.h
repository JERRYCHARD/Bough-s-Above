#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "OwnedUnit.h"
#include "../Gacha/GachaSubsystem/RarityTypes.h"
#include "../Gacha/GachaSubsystem/GachaRarityTable.h"
#include "../Gacha/CharacterRoll/UnitTypes.h"
#include "InventorySubsystem.generated.h"

UCLASS()
class BOUGHSABOVE_API UInventorySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory")
	UGachaRarityTable* RarityTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<FOwnedUnit> OwnedUnits;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TMap<ERarityTier, int32> ShardsByTier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 Gold = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 Gems = 0;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddUnit(const FUnitData& Unit);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool OwnsUnit(FName UnitID) const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool TrySpendGems(int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddGems(int32 Amount);

private:
	const FOwnedUnit* FindOwnedUnit(FName UnitID) const;
};
