#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "../Gacha/GachaSubsystem/RarityTypes.h"
#include "../Gacha/GachaSubsystem/GachaRarityTable.h"
#include "CurrencySubsystem.generated.h"

UCLASS()
class BOUGHSABOVE_API UCurrencySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Currency")
	UGachaRarityTable* RarityTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Currency")
	TMap<ERarityTier, int32> ShardsByTier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Currency")
	int32 Gold = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Currency")
	int32 Gems = 0;

	UFUNCTION(BlueprintCallable, Category = "Currency")
	bool TrySpendGems(int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Currency")
	void AddGems(int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Currency")
	void AddShardsForDuplicate(ERarityTier Tier);

	UFUNCTION(BlueprintCallable, Category = "Currency")
	bool TrySpendShards(ERarityTier Tier, int32 Amount);

	UFUNCTION(BlueprintCallable, Category = "Currency")
	int32 GetShardCount(ERarityTier Tier) const;
};
