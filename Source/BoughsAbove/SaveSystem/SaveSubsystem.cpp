#include "SaveSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "../Inventory/CurrencySubsystem.h"

void USaveSubsystem::SaveGame()
{
	UInventorySubsystem* Inventory = GetGameInstance()->GetSubsystem<UInventorySubsystem>();
	UGachaSubsystem* Gacha = GetGameInstance()->GetSubsystem<UGachaSubsystem>();
	UCurrencySubsystem* Currency = GetGameInstance()->GetSubsystem<UCurrencySubsystem>();

	if (!Inventory || !Gacha || !Currency)
	{
		return;
	}

	UBoughsAboveSaveGame* SaveData = Cast<UBoughsAboveSaveGame>(UGameplayStatics::CreateSaveGameObject(UBoughsAboveSaveGame::StaticClass()));
	if (!SaveData)
	{
		return;
	}

	SaveData->OwnedUnits = Inventory->OwnedUnits;
	SaveData->ShardsByTier = Currency->ShardsByTier;
	SaveData->Gold = Currency->Gold;
	SaveData->Gems = Currency->Gems;
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
	UCurrencySubsystem* Currency = GetGameInstance()->GetSubsystem<UCurrencySubsystem>();

	if (!Inventory || !Gacha || !Currency)
	{
		return;
	}

	Inventory->OwnedUnits = SaveData->OwnedUnits;
	Currency->ShardsByTier = SaveData->ShardsByTier;
	Currency->Gold = SaveData->Gold;
	Currency->Gems = SaveData->Gems;
	Gacha->RestorePityCounters(SaveData->PityCounters);
}