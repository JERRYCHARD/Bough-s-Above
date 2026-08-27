#include "StatCalculator.h"

FUnitStats UStatCalculator::CalculateStats(const FUnitStats& BaseStats, int32 StarLevel, const FStatGrowthConfig& GrowthConfig)
{
	const int32 ClampedStarLevel = FMath::Clamp(StarLevel, 0, 6);

	FUnitStats Result = BaseStats;

	Result.PhysicalDamage += BaseStats.PhysicalDamage * (GrowthConfig.PhysicalDamageGrowthPercent / 100.f) * ClampedStarLevel;
	Result.MagicDamage += BaseStats.MagicDamage * (GrowthConfig.MagicDamageGrowthPercent / 100.f) * ClampedStarLevel;
	Result.AttackSpeed += BaseStats.AttackSpeed * (GrowthConfig.AttackSpeedGrowthPercent / 100.f) * ClampedStarLevel;
	Result.HP += BaseStats.HP * (GrowthConfig.HPGrowthPercent / 100.f) * ClampedStarLevel;
	Result.Defense += BaseStats.Defense * (GrowthConfig.DefenseGrowthPercent / 100.f) * ClampedStarLevel;
	Result.MagicDefense += BaseStats.MagicDefense * (GrowthConfig.MagicDefenseGrowthPercent / 100.f) * ClampedStarLevel;

	return Result;
}