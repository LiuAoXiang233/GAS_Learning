// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/InventoryMenuWidget.h"

#include "Character/AuraCharacter.h"
#include "Inventory/UInventory.h"
#include "Inventory/UItem.h"

void UInventoryMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AAuraCharacter* Character = Cast<AAuraCharacter>(GetOwningPlayerPawn());
	if (Character && Character->GetInventory())
	{
		Inventory = Character->GetInventory();
		TotalItems = Inventory->Items.Num();
	}

	// 初始加载物品
	LoadMoreItems();
}

void UInventoryMenuWidget::LoadMoreItems()
{
	if (!Inventory) return;

	// 计算还可以加载的最大物品数量
	int32 EndIndex = FMath::Min(CurrentLoadedItems + ItemsPerBatch, TotalItems);

	// 加载当前批次的物品
	for (int32 i = CurrentLoadedItems; i < EndIndex; ++i)
	{
		UUItem* Item = Inventory->Items[i];

		
		CreateSubWidget.Broadcast(Item);
		
	}

	// 更新已加载的物品数量
	CurrentLoadedItems = EndIndex;
}




bool UInventoryMenuWidget::CanLoadMoreItems() const
{
	return CurrentLoadedItems < TotalItems;
}

FString UInventoryMenuWidget::GetDescriptionFromItem(const FString& ItemName) const
{
	if (UUItem* TheItem = Inventory->FindItemFromName(ItemName))
	{
		return TheItem->Description;
	}

	return FString();

}

void UInventoryMenuWidget::OnScroll(float ScrollOffset)
{
	if (ScrollOffset >= 0.9f && CanLoadMoreItems())
	{
		LoadMoreItems(); 
	}
}

UUInventory* UInventoryMenuWidget::GetInventory()
{
	if (Inventory)
	{
		return Inventory;
	}
	return nullptr;
}
