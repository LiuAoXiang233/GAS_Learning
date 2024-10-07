// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/InventoryWidgetControllerBase.h"

#include "AbilitySystem/Data/InventoryItem.h"
#include "Inventory/Inventory.h"
#include "Inventory/UItem.h"
#include "Inventory/Widget2/InventoryWidget.h"

void UInventoryWidgetControllerBase::Init(UInventoryWidget* InWidget)
{
	if (InWidget)
	{
		Widget = InWidget;
	}

	
}

void UInventoryWidgetControllerBase::AddWidgetToScrollBox(UUItem* NewItem)
{
	// TODO: create Widget for Item， 并且设置该widget的信息， 然后添加绑定 
}

void UInventoryWidgetControllerBase::LoadMoreItems()
{
	if (!Inventory) return;

	// 计算还可以加载的最大物品数量
	int32 EndIndex = FMath::Min(CurrentLoadedItems + ItemsPerBatch, TotalItems);

	// 加载当前批次的物品
	for (int32 i = CurrentLoadedItems; i < EndIndex; ++i)
	{
		UUItem* Item = Inventory->Items[i];
		
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
	if (UUItem* TheItem = Inventory->FindItemFromName(ItemName))
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

bool UInventoryWidgetControllerBase::UseItem(const FString& ItemName)
{
	return Inventory->UseItem(ItemName);
}

void UInventoryWidgetControllerBase::OnScroll(float ScrollOffset)
{
	if (ScrollOffset >= 0.9f && CanLoadMoreItems())
	{
		LoadMoreItems(); 
	}
}

AInventory* UInventoryWidgetControllerBase::GetInventory() const
{
	if (Inventory)
	{
		return Inventory;
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
