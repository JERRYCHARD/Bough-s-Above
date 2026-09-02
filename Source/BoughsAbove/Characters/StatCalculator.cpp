#include "StatCalculator.h"

void UStatCalculator::ApplyModifier(FUnitStats& Stats, const FStatModifier& Modifier)
{
	switch (Modifier.Stat)
	{
	case EUnitStatType::PhysicalDamage: Stats.PhysicalDamage += Modifier.Amount; break;
	case EUnitStatType::MagicDamage: Stats.MagicDamage += Modifier.Amount; break;
	case EUnitStatType::Range: Stats.Range += static_cast<int32>(Modifier.Amount); break;
	case EUnitStatType::AttackSpeed: Stats.AttackSpeed += Modifier.Amount; break;
	case EUnitStatType::HP: Stats.HP += Modifier.Amount; break;
	case EUnitStatType::Defense: Stats.Defense += Modifier.Amount; break;
	case EUnitStatType::MagicDefense: Stats.MagicDefense += Modifier.Amount; break;
	case EUnitStatType::CritChance: Stats.CritChance += Modifier.Amount; break;
	case EUnitStatType::CritDamage: Stats.CritDamage += Modifier.Amount; break;
	case EUnitStatType::Mana: Stats.Mana += Modifier.Amount; break;
	}
}

FUnitStats UStatCalculator::CalculateStats(const FUnitStats& BaseStats, int32 StarLevel, const FStatGrowthConfig& GrowthConfig, const TArray<FStatModifier>& GearModifiers)
{
	const int32 ClampedStarLevel = FMath::Clamp(StarLevel, 0, 6);

	FUnitStats Result = BaseStats;

	Result.PhysicalDamage += BaseStats.PhysicalDamage * (GrowthConfig.PhysicalDamageGrowthPercent / 100.f) * ClampedStarLevel;
	Result.MagicDamage += BaseStats.MagicDamage * (GrowthConfig.MagicDamageGrowthPercent / 100.f) * ClampedStarLevel;
	Result.AttackSpeed += BaseStats.AttackSpeed * (GrowthConfig.AttackSpeedGrowthPercent / 100.f) * ClampedStarLevel;
	Result.HP += BaseStats.HP * (GrowthConfig.HPGrowthPercent / 100.f) * ClampedStarLevel;
	Result.Defense += BaseStats.Defense * (GrowthConfig.DefenseGrowthPercent / 100.f) * ClampedStarLevel;
	Result.MagicDefense += BaseStats.MagicDefense * (GrowthConfig.MagicDefenseGrowthPercent / 100.f) * ClampedStarLevel;

	for (const FStatModifier& Modifier : GearModifiers)
	{
		ApplyModifier(Result, Modifier);
	}

	return Result;
}