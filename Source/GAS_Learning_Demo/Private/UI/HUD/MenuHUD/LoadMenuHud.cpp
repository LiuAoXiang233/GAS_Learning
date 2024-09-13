// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/MenuHUD/LoadMenuHud.h"

#include "Blueprint/UserWidget.h"
#include "UI/MVVM/MVVM_LoadScreenModel.h"
#include "UI/Widget/LoadMenuWidget.h"

void ALoadMenuHud::InitializeWidgetAndViewModel()
{
	MVVM_MenuViewModel = NewObject<UMVVM_LoadScreenModel>(this, MVVM_MenuViewModelClass);
	MenuWidget = CreateWidget<ULoadMenuWidget>(PlayerOwner, MenuWidgetClass);
}
