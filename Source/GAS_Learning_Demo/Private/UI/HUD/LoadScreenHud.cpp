// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/LoadScreenHud.h"

#include "Blueprint/UserWidget.h"
#include "UI/Widget/LoadScreenMenuBase.h"

void ALoadScreenHud::BeginPlay()
{
	Super::BeginPlay();

	LoadScreenMenuWidget = CreateWidget<ULoadScreenMenuBase>(this, LoadScreenMenuWidgetClass);
	LoadScreenMenuWidget->AddToViewport();
}
