// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MVVM/MyMVVM_MainMenuModel.h"

#include "Game/AuraGameInstance.h"
#include "Game/AuraGameModeBase.h"
#include "Kismet/GameplayStatics.h"


void UMyMVVM_MainMenuModel::StartButtonPressed()
{

	FString DefaultLoadSlotName = FString("LoadMenuSoltModel_Default");
	int32 DefaultLoadSlotIndex = 0;
	if (AAuraGameModeBase* AuraGameMode  = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(this)))
	{
		UAuraGameInstance* GameInstance = Cast<UAuraGameInstance>(AuraGameMode->GetGameInstance());
		GameInstance->LoadSlotIndex = DefaultLoadSlotIndex;
		GameInstance->LoadSlotName = DefaultLoadSlotName;
		
	}
}

void UMyMVVM_MainMenuModel::ContinueButtonPressed()
{
	OpenLoadMenuDelegate.Broadcast();

}

void UMyMVVM_MainMenuModel::ExitButtonPressed()
{


}

void UMyMVVM_MainMenuModel::EnterNameButtonPressed(FText InName)
{
	if (AAuraGameModeBase* AuraGameMode  = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(this)))
	{
		ULoadScreenSaveGame* SaveGame = AuraGameMode->RetrieveInGameSaveData();

		if (SaveGame == nullptr) return;

		SaveGame->PlayerName = InName.ToString();

		AuraGameMode->SaveInGameSaveData(SaveGame);
	}
}
