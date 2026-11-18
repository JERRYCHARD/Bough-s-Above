#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TraitTypes.h"
#include "TraitDatabase.h"
#include "TraitSubsystem.generated.h"

UCLASS()
class BOUGHSABOVE_API UTraitSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Trait")
	UTraitDatabase* TraitDatabase;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Trait")
	int32 CostPerRoll = 1;

	UFUNCTION(BlueprintCallable, Category = "Trait")
	bool TryRollTraitIntoSlot(FName UnitID, int32 SlotNumber);

	UFUNCTION(BlueprintCallable, Category = "Trait")
	void SetActiveTraitSlot(FName UnitID, int32 SlotNumber);

	UFUNCTION(BlueprintCallable, Category = "Trait")
	FText GetTraitDisplayName(FName TraitID) const;

private:
	FName RollTrait() const;
};