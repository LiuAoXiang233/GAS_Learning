// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/MenuHUD/CharacterSettingMenuHud.h"

#include "Blueprint/UserWidget.h"
#include "UI/MVVM/MVVM_CharacterSettingViewModel.h"
#include "UI/Widget/CharacterSettingMenu.h"

void ACharacterSettingMenuHud::InitializeWidgetAndViewModel()
{
	MVVM_MenuViewModel = NewObject<UMVVM_CharacterSettingViewModel>(this, MVVM_MenuViewModelClass);
	MenuWidget = CreateWidget<UCharacterSettingMenu>(PlayerOwner, MenuWidgetClass);
}
