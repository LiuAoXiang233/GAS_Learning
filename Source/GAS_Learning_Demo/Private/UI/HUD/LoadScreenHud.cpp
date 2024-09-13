// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/LoadScreenHud.h"
#include "Blueprint/UserWidget.h"
#include "UI/MVVM/MyMVVM_MainMenuModel.h"



void ALoadScreenHud::BeginPlay()
{
	Super::BeginPlay();

	InitializeWidgetAndViewModel();

	FInputModeUIOnly InputModeUIOnly;
	InputModeUIOnly.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	GetOwningPlayerController()->SetInputMode(InputModeUIOnly);
	GetOwningPlayerController()->SetShowMouseCursor(true);
	
	MenuWidget->AddToViewport();
	SetMenuWidgetViewModel();
}

void ALoadScreenHud::InitializeWidgetAndViewModel()
{
	MVVM_MenuViewModel = NewObject<UMVVM_ViewModelBase>(this, MVVM_MenuViewModelClass);
	MenuWidget = CreateWidget<UUserWidget>(PlayerOwner, MenuWidgetClass);
}
