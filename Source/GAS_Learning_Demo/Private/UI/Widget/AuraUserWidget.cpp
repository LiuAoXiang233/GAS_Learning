// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/AuraUserWidget.h"

void UAuraUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WigetController = InWidgetController;
	WidgetControllerSet();
}

UObject* UAuraUserWidget::GetWidgetController()
{
	if (WigetController)
	{
		return WigetController;
	}

	return nullptr;
}
