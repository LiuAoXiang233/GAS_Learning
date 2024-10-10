// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/InventoryComponent.h"

#include "Inventory/Inventory.h"
#include "Inventory/Item.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Inventory = CreateDefaultSubobject<AInventory>(FName("Inventory"));
	
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// 初始化背包
	if (!Inventory)
	{
		Inventory = NewObject<AInventory>();
	}
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventoryComponent::AddItemToInventory(UItem* NewItem)
{
	if (Inventory)
	{
		Inventory->AddItem(NewItem);
	}
}

void UInventoryComponent::ReplaceInventory(AInventory* NewInventory)
{
	if (NewInventory && Inventory)
	{
		Inventory->ReplaceItems(NewInventory->GetItems());
	}
}

void UInventoryComponent::UseItem(UItem* TheItem, int32 UsedQuantity)
{
	if (TheItem && UsedQuantity > 0)
	{
		TheItem->AddToQuantity(UsedQuantity, false);

		if (TheItem->GetQuantity() <= 0)
		{
			Inventory->RemoveItem(TheItem);
			OnItemDestroyDelegate.Broadcast(TheItem);
		}
	}
}

