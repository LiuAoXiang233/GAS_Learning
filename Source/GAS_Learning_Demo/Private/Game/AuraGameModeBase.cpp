// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/AuraGameModeBase.h"

#include "Game/LoadScreenSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "UI/MVVM/MVVM_LoadMenuSoltModel.h"

void AAuraGameModeBase::SaveSlotData(UMVVM_LoadMenuSoltModel* LoadSlotModel, const int32 SlotIndex)
{
	if (UGameplayStatics::DoesSaveGameExist(LoadSlotModel->LoadSlotName, SlotIndex))
	{
		UGameplayStatics::DeleteGameInSlot(LoadSlotModel->LoadSlotName, SlotIndex);
	}

	USaveGame* SaveGameObject = UGameplayStatics::CreateSaveGameObject(LoadScreenSaveGameClass);
	ULoadScreenSaveGame* LoadScreenSaveGame = Cast<ULoadScreenSaveGame>(SaveGameObject);
	
	LoadScreenSaveGame->PlayerName = LoadSlotModel->GetPlayerName();
	LoadScreenSaveGame->SaveSlotStatus = ESaveSlotStatus::Taken;

	UGameplayStatics::SaveGameToSlot(LoadScreenSaveGame, LoadSlotModel->LoadSlotName, SlotIndex);
	
}

ULoadScreenSaveGame* AAuraGameModeBase::GetSaveSlotData(const FString& SlotName, int32 SlotIndex) const
{
	USaveGame* SaveGameObject = nullptr;
	if (UGameplayStatics::DoesSaveGameExist(SlotName, SlotIndex))
	{
		SaveGameObject = UGameplayStatics::LoadGameFromSlot(SlotName, SlotIndex);
	}
	
	else
	{
		SaveGameObject = UGameplayStatics::CreateSaveGameObject(LoadScreenSaveGameClass);
	}

	ULoadScreenSaveGame* LoadSaveGame = Cast<ULoadScreenSaveGame>(SaveGameObject);
	
	return LoadSaveGame;
	
}
