// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Data/InventoryItem.h"

FInventoryItemInfo UInventoryItem::FindItemDescriptionForName(const FString& ItemName, bool bLogNotFind) const
{
	for (FInventoryItemInfo ItemInfo : InventoryItemInfomation)
	{
		if (ItemInfo.Name == ItemName)
		{
			return ItemInfo;
		}
	}

	return FInventoryItemInfo();
}
