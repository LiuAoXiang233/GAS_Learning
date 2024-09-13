// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/MenuHUD/MainMenuHud.h"

#include "Blueprint/UserWidget.h"
#include "UI/Widget/MainMenuWidget.h"
#include "UI/MVVM/MyMVVM_MainMenuModel.h"

void AMainMenuHud::InitializeWidgetAndViewModel()
{
	MVVM_MenuViewModel = NewObject<UMyMVVM_MainMenuModel>(this, MVVM_MenuViewModelClass);
	MenuWidget = CreateWidget<UMainMenuWidget>(PlayerOwner, MenuWidgetClass);
}
