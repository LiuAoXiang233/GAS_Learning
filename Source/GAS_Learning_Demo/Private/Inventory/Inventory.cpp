// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Inventory.h"

#include "Inventory/Item.h"

AInventory::AInventory()
{
	
}

bool AInventory::ReplaceItems(TArray<UItem*> InItems)
{
	Items.Empty();
	for (UItem* Item : InItems)
	{
		// GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Green, FString("DestroyDelegate is Bind"));
		Items.Add(Item);
		
	}

	return true;
}

bool AInventory::AddItem(UItem* NewItem)
{
	if (!NewItem) return false;

	
	UItem* Item = FindItem_NotFull(NewItem->ItemInfo.ItemID);
	// 添加进背包中: 判断背包中原先是否有该物品，如果有则堆叠，如果没有直接添加
	if (Item && !Item->bSizeIsMaxStack())
	{
		
		// 计算堆栈
		const int32 CurrentItemNumber = Item->GetQuantity();
		const int32 AddedItemNumber = NewItem->GetQuantity();
		const int32 MaxStackNumber = Item->ItemInfo.MaxStackSize;

		const int32 AddNumber = FMath::Min(AddedItemNumber, MaxStackNumber - CurrentItemNumber);

		Item->AddToQuantity(AddNumber);
		NewItem->AddToQuantity(AddNumber, false);
		
	}
	else
	{
	
		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Green, FString("DestroyDelegate is Bind"));
		Items.Add(NewItem);
		OnItemAddedDelegate.Broadcast(NewItem);
	}

	
	return true;
}

bool AInventory::UseItem(UItem* TheUsedItem)
{
	TheUsedItem->AddToQuantity(1, false);
	return true;
}

void AInventory::RemoveItem(UItem* TheItem)
{
	GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, FString("Item is Begin Removed"));
	if (TheItem)
	{
		Items.Remove(TheItem);

		GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Green, FString("Item Is Removed"));
		
	}
	
	
}

bool AInventory::ReduceItem(UItem* TheItem, int32 ReduceNum)
{
	TheItem->AddToQuantity(ReduceNum);
	
	return true;
}

UItem* AInventory::FindItemFromID(FName ItemID)
{
	for (UItem* Item : Items)
	{
		if (Item->ItemInfo.ItemID == ItemID)
		{
			return Item;
		}
	}
	return nullptr;
}

UItem* AInventory::FindItemFromName(FString ItemName)
{
	for (UItem* Item : Items)
	{
		if (Item->ItemInfo.Name == ItemName)
		{
			return Item;
		}
	}
	return nullptr;
}

UItem* AInventory::FindItem_NotFull(FName ItemID)
{
	for (UItem* Item : Items)
	{
		if (Item->ItemInfo.ItemID == ItemID && !Item->bSizeIsMaxStack())
		{
			return Item;
		}
	}
	return nullptr;
}

UItem* AInventory::FindItem_Unique(FString ItemName, int32 ItemNum)
{
	for (UItem* Item : Items)
	{
		if (Item->ItemInfo.Name == ItemName && Item->GetQuantity() == ItemNum)
		{
			return Item;
		}
	}
	return nullptr;
}

TArray<UItem*> AInventory::GetItems() const
{
	return Items;
}
