// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/UInventory.h"

#include "Inventory/UItem.h"

UUInventory::UUInventory()
{
	
}

bool UUInventory::AddItem(UUItem* NewItem)
{
	if (!NewItem) return false;

	
	UUItem* Item = FindItem_NotFull(NewItem->ItemID);
	// 添加进背包中: 判断背包中原先是否有该物品，如果有则堆叠，如果没有直接添加
	if (Item && !Item->bSizeIsMaxStack())
	{
		
		// 计算堆栈
		const int32 CurrentItemNumber = Item->Quantity;
		const int32 AddedItemNumber = NewItem->Quantity;
		const int32 MaxStackNumber = Item->MaxStackSize;

		const int32 AddNumber = FMath::Min(AddedItemNumber, MaxStackNumber - CurrentItemNumber);

		Item->Quantity += AddNumber;
		NewItem->Quantity -= AddNumber;

		return true;
	}
	else
	{
		Items.Add(NewItem);
		return true;
	}
	
	
}

bool UUInventory::RemoveItem(FName ItemID)
{
	if (UUItem* Item = FindItem(ItemID))
	{
		Items.Remove(Item);
		return true;
	}
	return false;
}

UUItem* UUInventory::FindItem(FName ItemID)
{
	for (UUItem* Item : Items)
	{
		if (Item->ItemID == ItemID)
		{
			return Item;
		}
	}
	return nullptr;
}

UUItem* UUInventory::FindItem_NotFull(FName ItemID)
{
	for (UUItem* Item : Items)
	{
		if (Item->ItemID == ItemID && !Item->bSizeIsMaxStack())
		{
			return Item;
		}
	}
	return nullptr;
}

TArray<UUItem*> UUInventory::GetItems() const
{
	return Items;
}
