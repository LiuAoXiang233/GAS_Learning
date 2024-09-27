// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/MVVM_InventoryViewModel.h"

FItemDetails UMVVM_InventoryViewModel::GetCurrentItemDetails() const
{
	if (CurrentItemDetails.Name != FString("DefaultName"))
	{
		return CurrentItemDetails;
	}

	FItemDetails NewItemDetails(FName("DefaultID"), FString("DefaultName"), FString("Empty"), 0, 64);
	return NewItemDetails;
}

void UMVVM_InventoryViewModel::SetCurrentItemDetails(const FItemDetails& ItemDetails)
{
	CurrentItemDetails.Description = ItemDetails.Description;
	CurrentItemDetails.Name = ItemDetails.Name;
	CurrentItemDetails.Quantity = ItemDetails.Quantity;
	CurrentItemDetails.ItemID = ItemDetails.ItemID;
	CurrentItemDetails.MaxStackSize = ItemDetails.MaxStackSize;

	OnCurrentItemChangedDelegate.Broadcast();
}
