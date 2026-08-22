#include "GachaSubsystem.h"
#include "GachaRarityTable.h"

float UGachaSubsystem::GetEffectiveRate(const FRarityConfig& Config) const
{
	const int32* Counter = PityCounters.Find(Config.Tier);
	const int32 PullsSoFar = Counter ? *Counter : 0;

	if (Config.SoftPityStart > 0 && PullsSoFar >= Config.SoftPityStart)
	{
		const int32 PullsPastSoftPity = PullsSoFar - Config.SoftPityStart;
		const int32 Increments = PullsPastSoftPity / 1000;
		return Config.BaseRatePercent + Increments * Config.SoftPityIncrementPercentPer1000;
	}

	return Config.BaseRatePercent;
}

int32 UGachaSubsystem::GetPityCount(ERarityTier Tier) const
{
	const int32* Counter = PityCounters.Find(Tier);
	return Counter ? *Counter : 0;
}

ERarityTier UGachaSubsystem::RollRarity()
{
	if (!RarityTable)
	{
		return ERarityTier::Novice;
	}

	for (const FRarityConfig& Config : RarityTable->Rarities)
	{
		if (Config.HardPity > 0)
		{
			PityCounters.FindOrAdd(Config.Tier)++;
		}
	}

	for (int32 TierValue = static_cast<int32>(ERarityTier::Champion); TierValue >= static_cast<int32>(ERarityTier::Novice); --TierValue)
	{
		const ERarityTier Tier = static_cast<ERarityTier>(TierValue);
		const FRarityConfig* Config = RarityTable->FindConfig(Tier);

		if (!Config || Config->HardPity <= 0)
		{
			continue;
		}

		if (PityCounters[Tier] >= Config->HardPity)
		{
			PityCounters[Tier] = 0;
			return Tier;
		}
	}

	TArray<TPair<ERarityTier, float>> Weights;
	float TotalWeight = 0.f;

	for (const FRarityConfig& Config : RarityTable->Rarities)
	{
		const float Rate = GetEffectiveRate(Config);
		Weights.Add({ Config.Tier, Rate });
		TotalWeight += Rate;
	}

	const float Roll = FMath::FRandRange(0.f, TotalWeight);
	float Accumulated = 0.f;
	ERarityTier Result = ERarityTier::Novice;

	for (const TPair<ERarityTier, float>& Pair : Weights)
	{
		Accumulated += Pair.Value;
		if (Roll <= Accumulated)
		{
			Result = Pair.Key;
			break;
		}
	}

	if (PityCounters.Contains(Result))
	{
		PityCounters[Result] = 0;
	}

	return Result;
}

TArray<ERarityTier> UGachaSubsystem::RollRarityBatch(int32 Count)
{
	TArray<ERarityTier> Results;
	Results.Reserve(Count);

	for (int32 i = 0; i < Count; ++i)
	{
		Results.Add(RollRarity());
	}

	Results.Sort([](const ERarityTier& A, const ERarityTier& B)
		{
			return static_cast<uint8>(A) > static_cast<uint8>(B);
		});

	return Results;
}

float UGachaSubsystem::GetCurrentRate(ERarityTier Tier) const
{
	if (!RarityTable)
	{
		return 0.f;
	}

	const FRarityConfig* Config = RarityTable->FindConfig(Tier);
	if (!Config)
	{
		return 0.f;
	}

	return GetEffectiveRate(*Config);
}

FUnitData UGachaSubsystem::RollUnit(ERarityTier Tier, FName ChosenChampionID)
{
	if (!UnitDatabase)
	{
		return FUnitData();
	}

	if (Tier == ERarityTier::Champion)
	{
		for (const FUnitData& Unit : UnitDatabase->Units)
		{
			if (Unit.Tier == ERarityTier::Champion && Unit.UnitID == ChosenChampionID)
			{
				return Unit;
			}
		}
		return FUnitData();
	}

	TArray<FUnitData> Pool = UnitDatabase->GetUnitsForTier(Tier);
	if (Pool.Num() == 0)
	{
		return FUnitData();
	}

	const int32 RandomIndex = FMath::RandRange(0, Pool.Num() - 1);
	return Pool[RandomIndex];
}