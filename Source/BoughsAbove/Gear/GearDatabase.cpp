#include "GearDatabase.h"

const FGearItem* UGearDatabase::FindGear(FName GearID) const
{
	return GearItems.FindByPredicate([GearID](const FGearItem& Item)
		{
			return Item.GearID == GearID;
		});
}