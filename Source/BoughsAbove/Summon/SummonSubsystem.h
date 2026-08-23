#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SummonResult.h"
#include "../Gacha/GachaSubsystem/GachaSubsystem.h"
#include "../Inventory/InventorySubsystem.h"
#include "SummonSubsystem.generated.h"

UCLASS()
class BOUGHSABOVE_API USummonSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Summon")
	int32 CostPerSummon = 10;

	UFUNCTION(BlueprintCallable, Category = "Summon")
	TArray<FSummonResult> SummonOnce();

	UFUNCTION(BlueprintCallable, Category = "Summon")
	TArray<FSummonResult> SummonTen();

	UFUNCTION(BlueprintCallable, Category = "Summon")
	TArray<FSummonResult> SummonUpToFifty();

private:
	FSummonResult RollAndStore();
};
