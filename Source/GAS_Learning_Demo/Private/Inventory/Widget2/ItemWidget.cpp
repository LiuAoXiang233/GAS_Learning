// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Widget2/ItemWidget.h"
#include "Components/Button.h"
#include "Inventory/InventoryComponent.h"
#include "UI/WidgetController/InventoryWidgetControllerBase.h"


void UItemWidget::OnButtonClicked()
{
	OnItemClickedDelegate.Broadcast(TheItem);
}

void UItemWidget::OnButtonRightClicked()
{
	// 右键单击一次使用一个物品
	OnItemUsedDelegate.Broadcast(TheItem, 1, this);
}

void UItemWidget::OnItemQuantityToZero(UItem* InTheItem)
{
	if (TheItem == InTheItem)
	{
		RemoveFromParent();
	}
}

void UItemWidget::SetWidgetController(UInventoryWidgetControllerBase* InInventoryWidgetController)
{
	WidgetController = InInventoryWidgetController;

	WidgetController->GetInventoryComponent()->OnItemDestroyDelegate.AddDynamic(this, &UItemWidget::OnItemQuantityToZero);
	WidgetControllerSet();
}

void UItemWidget::WidgetControllerSet_Implementation()
{
}


void UItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button_Item->OnClicked.AddDynamic(this, &UItemWidget::OnButtonClicked);
	
}


FReply UItemWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	// 检查是否是左键点击
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Left mouse button clicked"));
		OnButtonClicked();
		return FReply::Handled();
	}

	// 检查是否是右键点击
	if (InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Right mouse button clicked"));
		OnButtonRightClicked();
		return FReply::Handled();
	}

	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}
