#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "OwnedUnit.h"
#include "../Gacha/GachaSubsystem/RarityTypes.h"
#include "../Gacha/GachaSubsystem/GachaRarityTable.h"
#include "../Gacha/CharacterRoll/UnitTypes.h"
#include "../Gacha/CharacterRoll/UnitDatabase.h"
#include "../Characters/UnitStats.h"
#include "../Characters/StatGrowthConfig.h"
#include "InventorySubsystem.generated.h"

UCLASS()
class BOUGHSABOVE_API UInventorySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory")
	UGachaRarityTable* RarityTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory")
	UUnitDatabase* UnitDatabase;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory")
	FStatGrowthConfig GrowthConfig;

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

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	FUnitStats GetCalculatedStats(FName UnitID) const;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool TryStarUpUnit(FName UnitID);

private:
	const FOwnedUnit* FindOwnedUnit(FName UnitID) const;
};
