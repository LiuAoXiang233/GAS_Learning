// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MVVM/MVVM_CharacterSettingViewModel.h"

#include "AbilitySystem/Data/PlayerClassDataAsset.h"
#include "Game/AuraGameInstance.h"
#include "Game/AuraGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void UMVVM_CharacterSettingViewModel::SetCharacterClass(FString InCharacterClass)
{
	UE_MVVM_SET_PROPERTY_VALUE(CharacterClass, InCharacterClass);
}

void UMVVM_CharacterSettingViewModel::SetCharacterName(FString InCharacterName)
{
	UE_MVVM_SET_PROPERTY_VALUE(CharacterName, InCharacterName);
}

void UMVVM_CharacterSettingViewModel::ShowAttribute(const FGameplayTag CharacterClassTag, FString& Strength, FString& Intelligence, FString& Resilience, FString& Viger)
{
	FPlayerClassData Data = PlayerClassDataAsset->FindPlayerClassDataForTag(CharacterClassTag);
	Strength = FString::SanitizeFloat(Data.Strength);
	Intelligence = FString::SanitizeFloat(Data.Intelligence);
	Resilience = FString::SanitizeFloat(Data.Resilience);
	Viger = FString::SanitizeFloat(Data.Viger);
	
}

void UMVVM_CharacterSettingViewModel::EnterNameAndChooseClass(const FString InCharacterName, const FString InCharacterClass, const FGameplayTag InCharacterClassTag)
{

	// 原本这段代码放在MainMenuViewModel中，作为开始游戏（即 新的游戏开头的) 用于指定GameInstance中默认存档的名字和index
	// 但是在蓝图操作中无法起作用
	// 所以将其放在开始游戏之前，人物设定完成的时候
	FString DefaultLoadSlotName = FString("LoadMenuSoltModel_Default");
	int32 DefaultLoadSlotIndex = 0;
	if (AAuraGameModeBase* AuraGameMode  = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(this)))
	{
		UAuraGameInstance* GameInstance = Cast<UAuraGameInstance>(AuraGameMode->GetGameInstance());
		GameInstance->LoadSlotIndex = DefaultLoadSlotIndex;
		GameInstance->LoadSlotName = DefaultLoadSlotName;
		
	}

	
	// 设置 玩家名称和出身
	SetCharacterName(InCharacterName);
	SetCharacterClass(InCharacterClass);

	// 将 其 保存在默认存档中
	if (AAuraGameModeBase* AuraGameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(this)))
	{
		ULoadScreenSaveGame* SaveData = AuraGameMode->RetrieveInGameSaveData();

		// 对存档中的属性先进行初始化
		SaveData->InitializeSaveData();
		
		SaveData->PlayerName = InCharacterName;
		SaveData->PlayerClass = InCharacterClass;
		SaveData->PlayerInformation.PlayerClassTag = InCharacterClassTag;

		FPlayerClassData PlayerClassData = PlayerClassDataAsset->FindPlayerClassDataForTag(InCharacterClassTag);
		SaveData->PlayerInformation.Strength = PlayerClassData.Strength;
		SaveData->PlayerInformation.Intelligence = PlayerClassData.Intelligence;
		SaveData->PlayerInformation.Resilience = PlayerClassData.Resilience;
		SaveData->PlayerInformation.Viger = PlayerClassData.Viger;

		
		AuraGameMode->SaveInGameSaveData(SaveData);
		
	}
	
}
