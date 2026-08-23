#pragma once

#include "CoreMinimal.h"
#include "../Gacha/GachaSubsystem/RarityTypes.h"
#include "../Gacha/CharacterRoll/UnitTypes.h"
#include "SummonResult.generated.h"

USTRUCT(BlueprintType)
struct FSummonResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Summon")
	ERarityTier Tier = ERarityTier::Novice;

	UPROPERTY(BlueprintReadWrite, Category = "Summon")
	FUnitData Unit;
};
