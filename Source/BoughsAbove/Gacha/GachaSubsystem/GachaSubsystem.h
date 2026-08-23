#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "RarityTypes.h"
#include "../CharacterRoll/UnitTypes.h"
#include "../CharacterRoll/UnitDatabase.h"
#include "GachaSubsystem.generated.h"

class UGachaRarityTable;

UCLASS()
class BOUGHSABOVE_API UGachaSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gacha")
	UGachaRarityTable* RarityTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gacha")
	UUnitDatabase* UnitDatabase;

	UFUNCTION(BlueprintCallable, Category = "Gacha")
	FUnitData RollUnit(ERarityTier Tier, FName ChosenChampionID);

	UFUNCTION(BlueprintCallable, Category = "Gacha")
	ERarityTier RollRarity();

	UFUNCTION(BlueprintCallable, Category = "Gacha")
	TArray<ERarityTier> RollRarityBatch(int32 Count);

	UFUNCTION(BlueprintCallable, Category = "Gacha")
	int32 GetPityCount(ERarityTier Tier) const;

	UFUNCTION(BlueprintCallable, Category = "Gacha")
	float GetCurrentRate(ERarityTier Tier) const;

	UFUNCTION(BlueprintCallable, Category = "Gacha")
	TMap<ERarityTier, int32> GetAllPityCounters() const;

	UFUNCTION(BlueprintCallable, Category = "Gacha")
	void RestorePityCounters(const TMap<ERarityTier, int32>& SavedCounters);

private:
	TMap<ERarityTier, int32> PityCounters;

	float GetEffectiveRate(const FRarityConfig& Config) const;
};
