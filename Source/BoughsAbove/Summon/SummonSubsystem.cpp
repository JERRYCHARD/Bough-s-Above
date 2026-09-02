#include "SummonSubsystem.h"
#include "../Inventory/CurrencySubsystem.h"

FSummonResult USummonSubsystem::RollAndStore()
{
	FSummonResult Result;

	UGameInstance* GI = GetGameInstance();
	UGachaSubsystem* Gacha = GI ? GI->GetSubsystem<UGachaSubsystem>() : nullptr;
	UInventorySubsystem* Inventory = GI ? GI->GetSubsystem<UInventorySubsystem>() : nullptr;

	if (!Gacha || !Inventory)
	{
		return Result;
	}

	Result.Tier = Gacha->RollRarity();
	Result.Unit = Gacha->RollUnit(Result.Tier, FName(TEXT("your_champion_unit_id")));
	Inventory->AddUnit(Result.Unit);

	return Result;
}

int32 USummonSubsystem::GetAffordableSummonCount() const
{
	UGameInstance* GI = GetGameInstance();
	UCurrencySubsystem* Currency = GI ? GI->GetSubsystem<UCurrencySubsystem>() : nullptr;

	if (!Currency || CostPerSummon <= 0)
	{
		return 0;
	}

	const int32 Affordable = Currency->Gems / CostPerSummon;
	return FMath::Min(Affordable, 50);
}

TArray<FSummonResult> USummonSubsystem::SummonOnce()
{
	TArray<FSummonResult> Results;

	UGameInstance* GI = GetGameInstance();
	UCurrencySubsystem* Currency = GI ? GI->GetSubsystem<UCurrencySubsystem>() : nullptr;

	if (!Currency || !Currency->TrySpendGems(CostPerSummon))
	{
		return Results;
	}

	Results.Add(RollAndStore());
	return Results;
}

TArray<FSummonResult> USummonSubsystem::SummonTen()
{
	TArray<FSummonResult> Results;

	UGameInstance* GI = GetGameInstance();
	UCurrencySubsystem* Currency = GI ? GI->GetSubsystem<UCurrencySubsystem>() : nullptr;

	if (!Currency || !Currency->TrySpendGems(CostPerSummon * 10))
	{
		return Results;
	}

	for (int32 i = 0; i < 10; ++i)
	{
		Results.Add(RollAndStore());
	}

	Results.Sort([](const FSummonResult& A, const FSummonResult& B)
		{
			return static_cast<uint8>(A.Tier) > static_cast<uint8>(B.Tier);
		});

	return Results;
}

TArray<FSummonResult> USummonSubsystem::SummonUpToFifty()
{
	TArray<FSummonResult> Results;

	UGameInstance* GI = GetGameInstance();
	UCurrencySubsystem* Currency = GI ? GI->GetSubsystem<UCurrencySubsystem>() : nullptr;

	if (!Currency)
	{
		return Results;
	}

	while (Results.Num() < 50 && Currency->TrySpendGems(CostPerSummon))
	{
		Results.Add(RollAndStore());
	}

	Results.Sort([](const FSummonResult& A, const FSummonResult& B)
		{
			return static_cast<uint8>(A.Tier) > static_cast<uint8>(B.Tier);
		});

	return Results;
}
