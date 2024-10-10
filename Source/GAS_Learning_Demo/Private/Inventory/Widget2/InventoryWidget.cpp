// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Widget2/InventoryWidget.h"

#include "Components/Button.h"
#include "Components/RichTextBlock.h"
#include "Components/ScrollBox.h"
#include "Inventory/InventoryComponent.h"
#include "Inventory/Widget2/ItemWidget.h"
#include "UI/WidgetController/InventoryWidgetControllerBase.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ExitButton->OnClicked.AddDynamic(this, &UInventoryWidget::Exit);
	
	if (!WidgetController && WidgetControllerClass)
	{
		WidgetController = NewObject<UInventoryWidgetControllerBase>(this, WidgetControllerClass);
		WidgetControllerSet();
		
	}
	WidgetController->Init(this);			// 这个函数里最后LoadMoreItems
	
	
}

void UInventoryWidget::Exit()
{
	RemoveFromParent();
	
}

bool UInventoryWidget::AddWidgetToScrollBox(UUserWidget* InWidget) const
{
	if (!InWidget) return false;
	if (UItemWidget* NewItemWidget = Cast<UItemWidget>(InWidget))
	{
		ItemScrollBox->AddChild(NewItemWidget);
		return true;
	}
	return false;
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

void UInventoryWidget::Init(UInventoryItem* InventoryItemInfo, UInventoryComponent* InventoryComponent)
{
	// 这个函数先一步NativeConstruct运行
	if (InventoryComponent && InventoryItemInfo)
	{
		if (!WidgetController && WidgetControllerClass)
		{
			WidgetController = NewObject<UInventoryWidgetControllerBase>(this, WidgetControllerClass);
		
		}
		WidgetController->SetInventory(InventoryComponent->Inventory);
		WidgetController->SetInventoryComponent(InventoryComponent);
		WidgetController->AllItemInfo = InventoryItemInfo;
		
		WidgetControllerSet();

	}
	
}

void UInventoryWidget::ShowDescriptionAndIcon(const FString& ItemDescription) const
{
	DescriptionTextBlock->SetRenderOpacity(1.f);
	FText Description = FText::FromString(ItemDescription);
	DescriptionTextBlock->SetText(Description);
}

void UInventoryWidget::HideDescriptionAndIcon()
{
	DescriptionTextBlock->SetRenderOpacity(0.f);
}
