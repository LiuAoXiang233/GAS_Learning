// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Chest.h"
#include "Inventory/UItem.h"
#include "Blueprint/UserWidget.h"
#include "Character/AuraCharacter.h"
#include "Component/InteractionComponent/InteractionComponent.h"
#include "Inventory/InventoryMenuWidget.h"

// Sets default values


AChest::AChest()
{
	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("InteractionComponent"));
}

bool AChest::AddItem(UUItem* NewItem)
{
	if (Items.Num() >= StackSize) return false;
	return Super::AddItem(NewItem);
}

bool AChest::RetrieveItem(const FString& ItemName, const int32 ItemNum)
{
	if (InventoryWidget)
	{
		if (UInventoryMenuWidget* InventoryMenuWidget = Cast<UInventoryMenuWidget>(InventoryWidget))
		{
			// 减少仓库里的数量
			InventoryMenuWidget->GetInventory()->ReduceItem(InventoryMenuWidget->TheClickedItem->ItemInfo.Name, InventoryMenuWidget->TheClickedItem->Quantity, ItemNum);


			// 为背包中添加数量
			UUItem* NewItem = NewObject<UUItem>();
			NewItem->ItemInfo.ItemID = InventoryMenuWidget->TheClickedItem->ItemInfo.ItemID;
			NewItem->ItemInfo.Name = InventoryMenuWidget->TheClickedItem->ItemInfo.Name;
			NewItem->ItemInfo.Description = InventoryMenuWidget->TheClickedItem->ItemInfo.Description;
			NewItem->Quantity = ItemNum;
			NewItem->ItemInfo.MaxStackSize = InventoryMenuWidget->TheClickedItem->ItemInfo.MaxStackSize;
			

			AAuraCharacter* Player = Cast<AAuraCharacter>(TheplayerWhoOpenedTheBox);
			Player->GetInventory()->AddItem(NewItem);

			return true;
		}
		
	}
	return false; 
}

void AChest::OpenChest(AAuraPlayerController* PlayerController)
{
	if (PlayerController)
	{
		// 打开箱子；
		// TODO: 播放箱子打开动画
        
		// 打开箱子UI
		InventoryWidget = CreateWidget(PlayerController, InventoryWidgetClass);
        	
		UInventoryMenuWidget* InventoryMenuWidget = Cast<UInventoryMenuWidget>(InventoryWidget);
		InventoryMenuWidget->bIsChest = true;
		InventoryMenuWidget->SetInventory(this);
		InventoryWidget->AddToViewport();
		
	}
	
}

void AChest::CloseChestMenu()
{
	if (InventoryWidget)
	{
		InventoryWidget->RemoveFromParent();
	}
}

void AChest::SetTheplayerWhoOpenedTheBox(AActor* Player)
{
	if (IsValid(Player))
	{
		TheplayerWhoOpenedTheBox = Player;
	}
}

void AChest::BeginPlay()
{
	Super::BeginPlay();
	if (InteractionComponent)
	{
		InteractionComponent->OnInteractDelegate.AddDynamic(this, &AChest::OpenChest);
	}
}

