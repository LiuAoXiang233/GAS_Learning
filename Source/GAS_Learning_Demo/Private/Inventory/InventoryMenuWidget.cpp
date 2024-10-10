// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/InventoryMenuWidget.h"

#include "Character/AuraCharacter.h"
#include "Inventory/Inventory.h"
#include "Inventory/Item.h"

void UInventoryMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!bIsChest)
	{
		AAuraCharacter* Character = Cast<AAuraCharacter>(GetOwningPlayerPawn());
		if (Character && Character->GetInventory())
		{
			Inventory = Character->GetInventory();
        	TotalItems = Inventory->Items.Num();
			
		}
        
        	
		// 初始加载物品
		LoadMoreItems();
	}
	else
	{
		// 这是个箱子
		TotalItems = Inventory->Items.Num();
		
	}

	Inventory->OnInventoryUpdateDelegate.AddDynamic(this, &UInventoryMenuWidget::refreshInventory);
	Inventory->OnItemAddedDelegate.AddDynamic(this, &UInventoryMenuWidget::CreateNewSubWidget);
	
}

void UInventoryMenuWidget::LoadMoreItems()
{
	if (!Inventory) return;

	// 计算还可以加载的最大物品数量
	int32 EndIndex = FMath::Min(CurrentLoadedItems + ItemsPerBatch, TotalItems);

	// 加载当前批次的物品
	for (int32 i = CurrentLoadedItems; i < EndIndex; ++i)
	{
		UItem* Item = Inventory->Items[i];
		
		CreateSubWidget.Broadcast(Item);
		
	}

	// 更新已加载的物品数量
	CurrentLoadedItems = EndIndex;
}




bool UInventoryMenuWidget::CanLoadMoreItems() const
{
	return CurrentLoadedItems < TotalItems;
}

void UInventoryMenuWidget::SetInventory(AInventory* InInventory)
{
	Inventory = InInventory;
}

void UInventoryMenuWidget::CreateNewSubWidget(const UItem* Item) 
{
	CreateSubWidget.Broadcast(Item);
}

void UInventoryMenuWidget::AddItemQuantity(const int32 ItemQuantity)
{
	OnItemQuantityAddedDelegate.Broadcast(ItemQuantity);
}

FString UInventoryMenuWidget::GetDescriptionFromItem(const FString& ItemName) const
{
	if (UItem* TheItem = Inventory->FindItemFromName(ItemName))
	{
		return TheItem->ItemInfo.Description;
	}

	return FString();

}

int32 UInventoryMenuWidget::GetValueFromItem(const FString& ItemName) const
{
	FInventoryItemInfo Info = InventoryItemInfo->FindItemDescriptionForName(ItemName);
	if (Info.Name != FString(""))
	{
		return Info.Value;
	}
	return 0;
}

bool UInventoryMenuWidget::UseItem(const FString& ItemName)
{
	return true;
}

void UInventoryMenuWidget::OnScroll(float ScrollOffset)
{
	if (ScrollOffset >= 0.9f && CanLoadMoreItems())
	{
		LoadMoreItems(); 
	}
}

AInventory* UInventoryMenuWidget::GetInventory()
{
	if (Inventory)
	{
		return Inventory;
	}
	return nullptr;
}

void UInventoryMenuWidget::refreshInventory()
{
	
	if (Inventory) 
	{
		// 清空所有subsiwdget
		ClearSubWidgetDelegate.Broadcast();
		
		// 遍历 Inventory 中的物品并创建显示项
		for (const UItem* Item : Inventory->GetItems()) // 假设 GetItems() 返回当前物品列表
		{
			if (Item && Item->GetQuantity() > 0) // 只显示数量大于0的物品
			{
				CreateSubWidget.Broadcast(Item);		
			}
		}
	}
}
