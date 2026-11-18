#include "TraitSubsystem.h"
#include "../Inventory/CurrencySubsystem.h"
#include "../Inventory/InventorySubsystem.h"

FName UTraitSubsystem::RollTrait() const
{
	if (!TraitDatabase || TraitDatabase->Traits.Num() == 0)
	{
		return NAME_None;
	}

	float TotalWeight = 0.f;
	for (const FTraitData& Trait : TraitDatabase->Traits)
	{
		TotalWeight += Trait.RollRatePercent;
	}

	const float Roll = FMath::FRandRange(0.f, TotalWeight);
	float Accumulated = 0.f;

	for (const FTraitData& Trait : TraitDatabase->Traits)
	{
		Accumulated += Trait.RollRatePercent;
		if (Roll <= Accumulated)
		{
			return Trait.TraitID;
		}
	}

	return TraitDatabase->Traits.Last().TraitID;
}

bool UTraitSubsystem::TryRollTraitIntoSlot(FName UnitID, int32 SlotNumber)
{
	if (SlotNumber != 1 && SlotNumber != 2)
	{
		return false;
	}

	UGameInstance* GI = GetGameInstance();
	UCurrencySubsystem* Currency = GI ? GI->GetSubsystem<UCurrencySubsystem>() : nullptr;
	UInventorySubsystem* Inventory = GI ? GI->GetSubsystem<UInventorySubsystem>() : nullptr;

	if (!Currency || !Inventory || !Currency->TrySpendTraitCoupons(CostPerRoll))
	{
		return false;
	}

	FOwnedUnit* Owned = nullptr;
	for (FOwnedUnit& Unit : Inventory->OwnedUnits)
	{
		if (Unit.UnitID == UnitID)
		{
			Owned = &Unit;
			break;
		}
	}

	if (!Owned)
	{
		return false;
	}

	const FName RolledTraitID = RollTrait();

	if (SlotNumber == 1)
	{
		Owned->TraitSlot1 = RolledTraitID;
	}
	else
	{
		Owned->TraitSlot2 = RolledTraitID;
	}

	return true;
}

void UTraitSubsystem::SetActiveTraitSlot(FName UnitID, int32 SlotNumber)
{
	UGameInstance* GI = GetGameInstance();
	UInventorySubsystem* Inventory = GI ? GI->GetSubsystem<UInventorySubsystem>() : nullptr;
	if (!Inventory)
	{
		return;
	}

	for (FOwnedUnit& Unit : Inventory->OwnedUnits)
	{
		if (Unit.UnitID == UnitID)
		{
			Unit.ActiveTraitSlot = SlotNumber;
			return;
		}
	}
}

FText UTraitSubsystem::GetTraitDisplayName(FName TraitID) const
{
	if (TraitID.IsNone() || !TraitDatabase)
	{
		return FText::FromString(TEXT("-"));
	}

	const FTraitData* Trait = TraitDatabase->FindTrait(TraitID);
	return Trait ? Trait->DisplayName : FText::FromString(TEXT("-"));
}