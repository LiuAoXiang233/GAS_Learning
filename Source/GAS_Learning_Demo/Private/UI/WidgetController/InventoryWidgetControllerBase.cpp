// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/InventoryWidgetControllerBase.h"

#include "AbilitySystem/Data/InventoryItem.h"
#include "Inventory/Inventory.h"
#include "Inventory/Item.h"
#include "Inventory/Widget2/InventoryWidget.h"
#include "Inventory/Widget2/ItemWidget.h"

void UInventoryWidgetControllerBase::Init(UInventoryWidget* InWidget)
{
	// 此时Inventory已经初始化好了，无需担心
	if (InWidget)
	{
		Widget = InWidget;

		
		LoadMoreItems();
	}

	
}

void UInventoryWidgetControllerBase::AddWidgetToScrollBox(UItem* NewItem)
{
	// TODO: create Widget for Item， 并且设置该widget的信息， 然后添加绑定
	if (ItemWidgetClass)
	{
		UItemWidget* ItemWidget = CreateWidget<UItemWidget>(Widget, ItemWidgetClass);
		ItemWidget->TheItem = NewItem;
		ItemWidget->ItemName = NewItem->ItemInfo.Name;
		ItemWidget->ItemQuantity = NewItem->GetQuantity();
		ItemWidget->ItemValue = NewItem->ItemInfo.Value;

		// TODO: 为ItemWidget绑定委托
		ItemWidget->OnItemClickedDelegate.AddDynamic(this, &UInventoryWidgetControllerBase::OnItemClicked);
		ItemWidget->OnItemUsedDelegate.AddDynamic(this, &UInventoryWidgetControllerBase::OnItemUsed);
		ItemWidget->SetWidgetController(this);
		
		// 将该ItemWidget加入到Widget中
		Widget->AddWidgetToScrollBox(ItemWidget);
	}
}

void UInventoryWidgetControllerBase::LoadMoreItems()
{
	if (!Inventory) return;

	// 计算还可以加载的最大物品数量
	TotalItems = Inventory->Items.Num();
	int32 EndIndex = FMath::Min(CurrentLoadedItems + ItemsPerBatch, TotalItems);

	// 加载当前批次的物品
	for (int32 i = CurrentLoadedItems; i < EndIndex; ++i)
	{
		UItem* Item = Inventory->Items[i];
		
		// TODO: 创建SubWidget为Item，并添加到ScrollBox里
		AddWidgetToScrollBox(Item);
	}

	// 更新已加载的物品数量
	CurrentLoadedItems = EndIndex;
}

bool UInventoryWidgetControllerBase::CanLoadMoreItems() const
{
	return CurrentLoadedItems < TotalItems;
}

FString UInventoryWidgetControllerBase::GetDescriptionFromItem(const FString& ItemName) const
{
	if (UItem* TheItem = Inventory->FindItemFromName(ItemName))
	{
		return TheItem->ItemInfo.Description;
	}

	return FString();
}

int32 UInventoryWidgetControllerBase::GetValueFromItem(const FString& ItemName) const
{
	FInventoryItemInfo Info = AllItemInfo->FindItemDescriptionForName(ItemName);
	if (Info.Name != FString(""))
	{
		return Info.Value;
	}
	return 0;
}

bool UInventoryWidgetControllerBase::UseItem(UItem* TheUsedItem)
{
	return Inventory->UseItem(TheUsedItem);
}

void UInventoryWidgetControllerBase::OnScroll(float ScrollOffset)
{
	if (ScrollOffset >= 0.9f && CanLoadMoreItems())
	{
		LoadMoreItems(); 
	}
}

void UInventoryWidgetControllerBase::OnItemClicked(UItem* TheItem)
{
	if (TheClickedItem == TheItem)
	{
		// 如果第二次点击该物品，那么取消显示Description和Icon, 并把TheClickedItem置空
		Widget->HideDescriptionAndIcon();
		TheClickedItem = nullptr;
	}
	else
	{
		//	首次点击该Item
		
		// 主要设置当前选中的Item, 并且让Widget显示这个Item的图片信息和介绍
		TheClickedItem = TheItem;
        
		// TODO：显示图片和物品介绍
		//	1. 使用委托，通知widget显示	NO！
		//	2. 操控widget实现
		Widget->ShowDescriptionAndIcon(TheClickedItem->ItemInfo.Description);
		
	}
	
}

void UInventoryWidgetControllerBase::OnItemUsed(UItem* TheItem, int32 UsedQuantity, UItemWidget* TheUsedItemWidget)
{
	if (!TheItem) return;
	if (UsedQuantity <= 0) return;

	InventoryComponent->UseItem(TheItem, UsedQuantity);
	TheUsedItemWidget->ItemQuantity -= UsedQuantity;
	
}

AInventory* UInventoryWidgetControllerBase::GetInventory() const
{
	if (Inventory)
	{
		return Inventory;
	}
	return nullptr;
}

UInventoryComponent* UInventoryWidgetControllerBase::GetInventoryComponent()
{
	if (InventoryComponent)
	{
		return InventoryComponent;
	}
	return nullptr;
}

void UInventoryWidgetControllerBase::SetInventory(AInventory* NewInventory)
{
	if (NewInventory)
	{
		Inventory = NewInventory;
	}
}

void UInventoryWidgetControllerBase::SetInventoryComponent(UInventoryComponent* InInventoryComponent)
{
	if (InInventoryComponent)
	{
		InventoryComponent = InInventoryComponent;
	}
	
}
