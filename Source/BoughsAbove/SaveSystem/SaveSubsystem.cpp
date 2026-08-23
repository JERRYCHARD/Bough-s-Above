#include "SaveSubsystem.h"
#include "Kismet/GameplayStatics.h"

void USaveSubsystem::SaveGame()
{
	UInventorySubsystem* Inventory = GetGameInstance()->GetSubsystem<UInventorySubsystem>();
	UGachaSubsystem* Gacha = GetGameInstance()->GetSubsystem<UGachaSubsystem>();

	if (!Inventory || !Gacha)
	{
		return;
	}

	UBoughsAboveSaveGame* SaveData = Cast<UBoughsAboveSaveGame>(UGameplayStatics::CreateSaveGameObject(UBoughsAboveSaveGame::StaticClass()));
	if (!SaveData)
	{
		return;
	}

	SaveData->OwnedUnits = Inventory->OwnedUnits;
	SaveData->ShardsByTier = Inventory->ShardsByTier;
	SaveData->Gold = Inventory->Gold;
	SaveData->Gems = Inventory->Gems;
	SaveData->PityCounters = Gacha->GetAllPityCounters();

	UGameplayStatics::SaveGameToSlot(SaveData, SaveSlotName, 0);
}

void USaveSubsystem::LoadGame()
{
	if (!UGameplayStatics::DoesSaveGameExist(SaveSlotName, 0))
	{
		return;
	}

	UBoughsAboveSaveGame* SaveData = Cast<UBoughsAboveSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
	if (!SaveData)
	{
		return;
	}

	UInventorySubsystem* Inventory = GetGameInstance()->GetSubsystem<UInventorySubsystem>();
	UGachaSubsystem* Gacha = GetGameInstance()->GetSubsystem<UGachaSubsystem>();

	if (!Inventory || !Gacha)
	{
		return;
	}

	Inventory->OwnedUnits = SaveData->OwnedUnits;
	Inventory->ShardsByTier = SaveData->ShardsByTier;
	Inventory->Gold = SaveData->Gold;
	Inventory->Gems = SaveData->Gems;
	Gacha->RestorePityCounters(SaveData->PityCounters);
}