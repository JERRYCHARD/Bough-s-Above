#pragma once

#include "CoreMinimal.h"
#include "../Gacha/GachaSubsystem/RarityTypes.h"
#include "../Characters/StatModifier.h"
#include "GearTypes.generated.h"

UENUM(BlueprintType)
enum class EGearSlot : uint8
{
	Weapon,
	Armor
};

USTRUCT(BlueprintType)
struct FGearItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gear")
	FName GearID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gear")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gear")
	EGearSlot SlotType = EGearSlot::Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gear")
	ERarityTier Tier = ERarityTier::Novice;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gear")
	int32 ShardCost = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gear")
	TArray<FStatModifier> StatModifiers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gear")
	FName PassiveID;
};

USTRUCT(BlueprintType)
struct FEquippedGear
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gear")
	FName WeaponID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gear")
	FName ArmorID;
};
