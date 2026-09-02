#pragma once

#include "CoreMinimal.h"
#include "StatType.generated.h"

UENUM(BlueprintType)
enum class EUnitStatType : uint8
{
	PhysicalDamage,
	MagicDamage,
	Range,
	AttackSpeed,
	HP,
	Defense,
	MagicDefense,
	CritChance,
	CritDamage,
	Mana
};
