// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Widget2/InventoryWidget.h"

#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "UI/WidgetController/InventoryWidgetControllerBase.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!WidgetController)
	{
		WidgetController = NewObject<UInventoryWidgetControllerBase>(this);
		WidgetController->Init(this);
	}

	
	ExitButton->OnClicked.AddDynamic(this, &UInventoryWidget::Exit);
	
}

void UInventoryWidget::Exit()
{
	RemoveFromParent();
	
}

void UInventoryWidget::SetWidgetController(UInventoryWidgetControllerBase* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}

void UInventoryWidget::WidgetControllerSet_Implementation()
{
	
}

UInventoryWidgetControllerBase* UInventoryWidget::GetInventoryWidgetController() const
{
	if (WidgetController)
	{
		return WidgetController;
	}
	
	return nullptr;
}

void UInventoryWidget::Init(AInventory* Inventory, UInventoryItem* InventoryItemInfo)
{
	if (Inventory && WidgetController && InventoryItemInfo)
	{
		WidgetController->SetInventory(Inventory);
		WidgetController->AllItemInfo = InventoryItemInfo;
	}
}
