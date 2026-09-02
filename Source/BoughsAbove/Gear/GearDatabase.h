#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GearTypes.h"
#include "GearDatabase.generated.h"

UCLASS(BlueprintType)
class BOUGHSABOVE_API UGearDatabase : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gear")
	TArray<FGearItem> GearItems;

	const FGearItem* FindGear(FName GearID) const;
};
