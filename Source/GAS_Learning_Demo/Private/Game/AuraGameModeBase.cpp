// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/AuraGameModeBase.h"

#include "Game/AuraGameInstance.h"
#include "Game/LoadScreenSaveGame.h"
#include "GameFramework/PlayerStart.h"
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
	LoadScreenSaveGame->MapName = LoadSlotModel->GetMapName();

	UGameplayStatics::SaveGameToSlot(LoadScreenSaveGame, LoadSlotModel->LoadSlotName, SlotIndex);
	
}

void AAuraGameModeBase::TravelToMap(UMVVM_LoadMenuSoltModel* LoadSlotModel)
{
	const FString MapName = LoadSlotModel->GetMapName();
	TSoftObjectPtr<UWorld> Level = Maps.FindChecked(MapName);
	UGameplayStatics::OpenLevelBySoftObjectPtr(LoadSlotModel, Level);
}

ULoadScreenSaveGame* AAuraGameModeBase::RetrieveInGameSaveData()
{
	if (UAuraGameInstance* GameInstance = Cast<UAuraGameInstance>(GetGameInstance()))
	{
		FString InLoadSlotName = GameInstance->LoadSlotName;
		int32 InLoadSlotIndex = GameInstance->LoadSlotIndex;

		return GetSaveSlotData(InLoadSlotName, InLoadSlotIndex);
	}

	return nullptr;
	
}

void AAuraGameModeBase::SaveInGameSaveData(ULoadScreenSaveGame* SaveGameData)
{
	if (UAuraGameInstance* GameInstance = Cast<UAuraGameInstance>(GetGameInstance()))
	{
		FString InLoadSlotName = GameInstance->LoadSlotName;
		int32 InLoadSlotIndex = GameInstance->LoadSlotIndex;

		UGameplayStatics::SaveGameToSlot(SaveGameData, InLoadSlotName, InLoadSlotIndex);
	}
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

AActor* AAuraGameModeBase::ChoosePlayerStart_Implementation(AController* Player)
{

	UAuraGameInstance* GameInstance = Cast<UAuraGameInstance>(GetGameInstance());
	
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), Actors);
	if (Actors.Num() > 0)
	{
		AActor* ChooseActor = Actors[0];

		for (AActor* Actor : Actors)
		{
			if (APlayerStart* PlayerStart = Cast<APlayerStart>(Actor))
			{
				if (PlayerStart->PlayerStartTag == GameInstance->PlayerStartTag)
				{
					ChooseActor = Actor;
					break;
				}
			}
		}
		return ChooseActor;
	}
	return nullptr;
}

void AAuraGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	Maps.Add(DefaultMapName, DefaultMap);
}
