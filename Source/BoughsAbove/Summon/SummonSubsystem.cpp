#include "SummonSubsystem.h"

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
	Result.Unit = Gacha->RollUnit(Result.Tier, NAME_None);
	Inventory->AddUnit(Result.Unit);

	return Result;
}

TArray<FSummonResult> USummonSubsystem::SummonOnce()
{
	TArray<FSummonResult> Results;

	UGameInstance* GI = GetGameInstance();
	UInventorySubsystem* Inventory = GI ? GI->GetSubsystem<UInventorySubsystem>() : nullptr;

	if (!Inventory || !Inventory->TrySpendGems(CostPerSummon))
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
	UInventorySubsystem* Inventory = GI ? GI->GetSubsystem<UInventorySubsystem>() : nullptr;

	if (!Inventory || !Inventory->TrySpendGems(CostPerSummon * 10))
	{
		return Results;
	}

	for (int32 i = 0; i < 10; ++i)
	{
		Results.Add(RollAndStore());
	}

	return Results;
}

TArray<FSummonResult> USummonSubsystem::SummonUpToFifty()
{
	TArray<FSummonResult> Results;

	UGameInstance* GI = GetGameInstance();
	UInventorySubsystem* Inventory = GI ? GI->GetSubsystem<UInventorySubsystem>() : nullptr;

	if (!Inventory)
	{
		return Results;
	}

	while (Results.Num() < 50 && Inventory->TrySpendGems(CostPerSummon))
	{
		Results.Add(RollAndStore());
	}

	return Results;
}

int32 USummonSubsystem::GetAffordableSummonCount() const
{
	UGameInstance* GI = GetGameInstance();
	UInventorySubsystem* Inventory = GI ? GI->GetSubsystem<UInventorySubsystem>() : nullptr;

	if (!Inventory || CostPerSummon <= 0)
	{
		return 0;
	}

	const int32 Affordable = Inventory->Gems / CostPerSummon;
	return FMath::Min(Affordable, 50);
}
