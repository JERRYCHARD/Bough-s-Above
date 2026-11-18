#pragma once

#include "CoreMinimal.h"
#include "../Characters/StatModifier.h"
#include "TraitTypes.generated.h"

UENUM(BlueprintType)
enum class ETraitTier : uint8
{
	Rare,
	Epic,
	Legendary,
	Mythic,
	Secret
};

USTRUCT(BlueprintType)
struct FTraitData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trait")
	FName TraitID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trait")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trait")
	ETraitTier Tier = ETraitTier::Rare;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trait")
	float RollRatePercent = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trait")
	TArray<FStatModifier> StatModifiers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trait")
	FName SpecialEffectID;
};
