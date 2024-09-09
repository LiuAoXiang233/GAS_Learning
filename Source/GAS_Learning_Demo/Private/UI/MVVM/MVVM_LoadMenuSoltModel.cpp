// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MVVM/MVVM_LoadMenuSoltModel.h"

void UMVVM_LoadMenuSoltModel::SetPlayerName(FString InPlayerName)
{
	UE_MVVM_SET_PROPERTY_VALUE(PlayerName, InPlayerName);
}

void UMVVM_LoadMenuSoltModel::InitializaSlot()
{
	SetWidgetSwitcherIndex.Broadcast(1);
}
