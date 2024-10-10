// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Item.h"

#include "Kismet/GameplayStatics.h"

UItem::UItem()
{
	
}

UItem::UItem(FName InItemID, FString InName, FString InDescription, int32 InQuantity, int32 InMaxStackSize)
{
	ItemInfo.Name = InName;
	ItemInfo.Description = InDescription;
	ItemInfo.ItemID = InItemID;
	ItemInfo.MaxStackSize = InMaxStackSize;
	Quantity = InQuantity;
	
}

void UItem::ChangeItemQuantity(int32 NewQuantity)
{
	Quantity = NewQuantity;
	
}

void UItem::AddToQuantity(int32 AddedNumber, bool bIsAdd)
{
	if (bIsAdd)
	{
		Quantity += AddedNumber;
	}
	else
	{
		Quantity -= AddedNumber;
	}


}


bool UItem::bSizeIsMaxStack() const
{
	if (Quantity >= ItemInfo.MaxStackSize)
	{
		return true;
	}
	return false;
}

