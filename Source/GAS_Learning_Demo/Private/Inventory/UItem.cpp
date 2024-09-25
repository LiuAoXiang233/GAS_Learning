// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/UItem.h"

UUItem::UUItem()
{
	ItemID = FName("DefaultItem");
	Name = "Default Item";
	Description = "This is a default item.";
	Quantity = 1;
	MaxStackSize = 64;
}

UUItem::UUItem(FName InItemID, FString InName, FString InDescription, int32 InQuantity, int32 InMaxStackSize)
{
	ItemID = InItemID;
	Name = InName;
	Description = InDescription;
	Quantity = InQuantity;
	MaxStackSize = InMaxStackSize;
}


bool UUItem::bSizeIsMaxStack() const
{
	if (Quantity >= MaxStackSize)
	{
		return true;
	}
	return false;
}
