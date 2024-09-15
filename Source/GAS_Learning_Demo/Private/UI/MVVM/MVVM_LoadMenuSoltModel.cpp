// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MVVM/MVVM_LoadMenuSoltModel.h"

void UMVVM_LoadMenuSoltModel::SetPlayerName(FString InPlayerName)
{
	UE_MVVM_SET_PROPERTY_VALUE(PlayerName, InPlayerName);
}

void UMVVM_LoadMenuSoltModel::SetMapName(FString InMapName)
{
	UE_MVVM_SET_PROPERTY_VALUE(MapName, InMapName);
}

void UMVVM_LoadMenuSoltModel::SetCharacterClass(FString InCharacterClass)
{
	UE_MVVM_SET_PROPERTY_VALUE(CharacterClass, InCharacterClass);
}

void UMVVM_LoadMenuSoltModel::InitializaSlot() const
{
	const int32 WidgetSwitcherIndex = SlotStatus.GetValue();
	SetWidgetSwitcherIndex.Broadcast(WidgetSwitcherIndex);
}
