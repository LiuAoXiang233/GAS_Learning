// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MVVM/MVVM_LoadScreenModel.h"

#include "Game/AuraGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "UI/MVVM/MVVM_LoadMenuSoltModel.h"

void UMVVM_LoadScreenModel::SetSelectSlotIndex(int InSelectSlotIndex)
{
	UE_MVVM_SET_PROPERTY_VALUE(SelectSlotIndex, InSelectSlotIndex);
}

void UMVVM_LoadScreenModel::SelectSlot(int32 Index)
{
	SetSelectSlotIndex(Index);
	SelectSlotDelegate.Broadcast(Index);
}


void UMVVM_LoadScreenModel::InitializeSlotWidgetViewModel()
{
	LoadMenuSoltModel_Default = NewObject<UMVVM_LoadMenuSoltModel>(this, SlotWidgetMenuViewModelClass);
	LoadMenuSoltModel_Default->LoadSlotName = FString("LoadMenuSoltModel_Default");
	LoadMenuSoltModel_1 = NewObject<UMVVM_LoadMenuSoltModel>(this, SlotWidgetMenuViewModelClass);
	LoadMenuSoltModel_1->LoadSlotName = FString("LoadMenuSoltModel_1");
	LoadMenuSoltModel_2 = NewObject<UMVVM_LoadMenuSoltModel>(this, SlotWidgetMenuViewModelClass);
	LoadMenuSoltModel_2->LoadSlotName = FString("LoadMenuSoltModel_2");
	LoadMenuSoltModel_3 = NewObject<UMVVM_LoadMenuSoltModel>(this, SlotWidgetMenuViewModelClass);
	LoadMenuSoltModel_3->LoadSlotName = FString("LoadMenuSoltModel_3");
	LoadMenuSoltModel_4 = NewObject<UMVVM_LoadMenuSoltModel>(this, SlotWidgetMenuViewModelClass);
	LoadMenuSoltModel_4->LoadSlotName = FString("LoadMenuSoltModel_4");


	LoadSlots.Add(0, LoadMenuSoltModel_Default);
	LoadSlots.Add(1, LoadMenuSoltModel_1);
	LoadSlots.Add(2, LoadMenuSoltModel_2);
	LoadSlots.Add(3, LoadMenuSoltModel_3);
	LoadSlots.Add(4, LoadMenuSoltModel_4);
}

UMVVM_LoadMenuSoltModel* UMVVM_LoadScreenModel::GetLoadSoltMenuModel(int32 index) const
{
	return LoadSlots.FindChecked(index);
}

void UMVVM_LoadScreenModel::SaveGameButtonPressed()
{
	AAuraGameModeBase* GameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(this));
	// TODO: 设置存档的 玩家姓名 游玩时间 地图所在位置

	LoadSlots[SelectSlotIndex]->SlotStatus = ESaveSlotStatus::Taken;
	LoadSlots[SelectSlotIndex]->SetPlayerName(FString(TEXT("灰姑娘")));
	
	GameMode->SaveSlotData(LoadSlots[SelectSlotIndex], SelectSlotIndex);
	LoadSlots[SelectSlotIndex]->InitializaSlot();
	
}

void UMVVM_LoadScreenModel::LoadData()
{
	const AAuraGameModeBase* AuraGameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(this));
	
	
	for (const TTuple<int32, UMVVM_LoadMenuSoltModel*>& LoadSlot : LoadSlots)
	{
		
		UMVVM_LoadMenuSoltModel* LoadMenuSoltModel = LoadSlot.Value;
		int32 LoadSlotIndex = LoadSlot.Key;


		if (const ULoadScreenSaveGame* GameData = AuraGameMode->GetSaveSlotData(LoadMenuSoltModel->LoadSlotName, LoadSlotIndex))
		{
			const FString PlayerName = GameData->PlayerName;
			const TEnumAsByte<ESaveSlotStatus> SlotStatus = GameData->SaveSlotStatus;
	
		
			LoadMenuSoltModel->SetPlayerName(PlayerName);
			LoadMenuSoltModel->SlotStatus = SlotStatus;
	
			LoadMenuSoltModel->InitializaSlot();
		}
		
	}
	
	
}

void UMVVM_LoadScreenModel::DeleteButtonPressed()
{
	if (SelectSlotIndex >= 0 && SelectSlotIndex <= 4)
	{
		UMVVM_LoadMenuSoltModel* LoadMenuSoltModel = LoadSlots[SelectSlotIndex];
		if (UGameplayStatics::DoesSaveGameExist(LoadMenuSoltModel->LoadSlotName, LoadMenuSoltModel->SlotIndex))
		{
			UGameplayStatics::DeleteGameInSlot(LoadMenuSoltModel->LoadSlotName, LoadMenuSoltModel->SlotIndex);
			LoadMenuSoltModel->SetPlayerName(FString("Default Name"));
			LoadMenuSoltModel->SlotStatus = ESaveSlotStatus::Vacant;
			LoadMenuSoltModel->InitializaSlot();
		}
	}
}
