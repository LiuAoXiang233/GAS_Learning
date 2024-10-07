// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/UItem.h"

UUItem::UUItem()
{
	
}

UUItem::UUItem(FName InItemID, FString InName, FString InDescription, int32 InQuantity, int32 InMaxStackSize)
{
	ItemInfo.Name = InName;
	ItemInfo.Description = InDescription;
	ItemInfo.ItemID = InItemID;
	ItemInfo.MaxStackSize = InMaxStackSize;
	Quantity = InQuantity;
	
}


bool UUItem::bSizeIsMaxStack() const
{
	if (Quantity >= ItemInfo.MaxStackSize)
	{
		return true;
	}
	return false;
}
