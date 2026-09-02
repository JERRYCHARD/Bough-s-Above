#include "GearSubsystem.h"
#include "../Inventory/CurrencySubsystem.h"
#include "../Inventory/InventorySubsystem.h"

bool UGearSubsystem::TryPurchaseGear(FName GearID)
{
	if (!GearDatabase)
	{
		return false;
	}

	const FGearItem* Item = GearDatabase->FindGear(GearID);
	if (!Item)
	{
		return false;
	}

	UGameInstance* GI = GetGameInstance();
	UCurrencySubsystem* Currency = GI ? GI->GetSubsystem<UCurrencySubsystem>() : nullptr;

	if (!Currency || !Currency->TrySpendShards(Item->Tier, Item->ShardCost))
	{
		return false;
	}

	FOwnedGear NewGear;
	NewGear.GearID = GearID;
	NewGear.EquippedToUnitID = NAME_None;
	OwnedGear.Add(NewGear);

	return true;
}

bool UGearSubsystem::TryEquipGear(FName UnitID, FName GearID)
{
	if (!GearDatabase)
	{
		return false;
	}

	const FGearItem* Item = GearDatabase->FindGear(GearID);
	if (!Item)
	{
		return false;
	}

	FOwnedGear* GearToEquip = OwnedGear.FindByPredicate([GearID](const FOwnedGear& Owned)
		{
			return Owned.GearID == GearID && Owned.EquippedToUnitID.IsNone();
		});

	if (!GearToEquip)
	{
		return false;
	}

	UGameInstance* GI = GetGameInstance();
	UInventorySubsystem* Inventory = GI ? GI->GetSubsystem<UInventorySubsystem>() : nullptr;
	if (!Inventory)
	{
		return false;
	}

	// Unequip whatever was in that slot first (both from the unit and from the gear's owned record)
	UnequipGear(UnitID, Item->SlotType);

	GearToEquip->EquippedToUnitID = UnitID;

	FOwnedUnit* TargetUnit = nullptr;
	for (FOwnedUnit& Unit : Inventory->OwnedUnits)
	{
		if (Unit.UnitID == UnitID)
		{
			TargetUnit = &Unit;
			break;
		}
	}

	if (TargetUnit)
	{
		if (Item->SlotType == EGearSlot::Weapon)
		{
			TargetUnit->EquippedGear.WeaponID = GearID;
		}
		else
		{
			TargetUnit->EquippedGear.ArmorID = GearID;
		}
	}

	return true;
}

void UGearSubsystem::UnequipGear(FName UnitID, EGearSlot Slot)
{
	UGameInstance* GI = GetGameInstance();
	UInventorySubsystem* Inventory = GI ? GI->GetSubsystem<UInventorySubsystem>() : nullptr;
	if (!Inventory)
	{
		return;
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
		return;
	}

	const FName PreviousGearID = (Slot == EGearSlot::Weapon) ? Owned->EquippedGear.WeaponID : Owned->EquippedGear.ArmorID;

	if (!PreviousGearID.IsNone())
	{
		if (FOwnedGear* PreviousGear = OwnedGear.FindByPredicate([PreviousGearID](const FOwnedGear& G) { return G.GearID == PreviousGearID; }))
		{
			PreviousGear->EquippedToUnitID = NAME_None;
		}
	}

	if (Slot == EGearSlot::Weapon)
	{
		Owned->EquippedGear.WeaponID = NAME_None;
	}
	else
	{
		Owned->EquippedGear.ArmorID = NAME_None;
	}
}

TArray<FStatModifier> UGearSubsystem::GetEquippedModifiers(FName UnitID) const
{
	TArray<FStatModifier> Modifiers;

	if (!GearDatabase)
	{
		return Modifiers;
	}

	UGameInstance* GI = GetGameInstance();
	UInventorySubsystem* Inventory = GI ? GI->GetSubsystem<UInventorySubsystem>() : nullptr;
	if (!Inventory)
	{
		return Modifiers;
	}

	const FOwnedUnit* Owned = Inventory->OwnedUnits.FindByPredicate([UnitID](const FOwnedUnit& Unit)
		{
			return Unit.UnitID == UnitID;
		});

	if (!Owned)
	{
		return Modifiers;
	}

	if (const FGearItem* Weapon = GearDatabase->FindGear(Owned->EquippedGear.WeaponID))
	{
		Modifiers.Append(Weapon->StatModifiers);
	}

	if (const FGearItem* Armor = GearDatabase->FindGear(Owned->EquippedGear.ArmorID))
	{
		Modifiers.Append(Armor->StatModifiers);
	}

	return Modifiers;
}