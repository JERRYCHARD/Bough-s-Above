#pragma once

#include "CoreMinimal.h"
#include "RarityTypes.generated.h"

UENUM(BlueprintType)
enum class ERarityTier : uint8
{
	Novice,
	Seasoned,
	Attuned,
	Adept,
	Elite,
	Champion
};

USTRUCT(BlueprintType)
struct FRarityConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rarity")
	ERarityTier Tier = ERarityTier::Novice;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rarity")
	float BaseRatePercent = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rarity")
	int32 SoftPityStart = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rarity")
	float SoftPityIncrementPercentPer1000 = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rarity")
	int32 HardPity = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rarity")
	int32 ShardsToTierUp = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rarity")
	int32 ShardCap = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rarity")
	int32 DuplicateGoldReward = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rarity")
	int32 CappedShardGoldReward = 15;
};
