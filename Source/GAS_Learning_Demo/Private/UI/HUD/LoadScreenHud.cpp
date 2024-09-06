// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/LoadScreenHud.h"

#include "Blueprint/UserWidget.h"
#include "UI/MVVM/MVVM_LoadScreenModel.h"
#include "UI/MVVM/MyMVVM_MainMenuModel.h"
#include "UI/Widget/LoadMenuWidget.h"
#include "UI/Widget/MainMenuWidget.h"


void ALoadScreenHud::BeginPlay()
{
	Super::BeginPlay();

	if (bIsMainMenu)
	{
		MVVM_MenuViewModel = NewObject<UMyMVVM_MainMenuModel>(this, MVVM_MenuViewModelClass);
		MenuWidget = CreateWidget<UMainMenuWidget>(PlayerOwner, MenuWidgetClass);
	}
	else
	{
		MVVM_MenuViewModel = NewObject<UMVVM_LoadScreenModel>(this, MVVM_MenuViewModelClass);
		MenuWidget = CreateWidget<ULoadMenuWidget>(PlayerOwner, MenuWidgetClass);
	}
	
	MenuWidget->AddToViewport();
	SetMenuWidgetViewModel();
}
