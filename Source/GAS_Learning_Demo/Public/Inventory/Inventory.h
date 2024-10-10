// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryComponent.h"
#include "Inventory.generated.h"

class UItem;


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemAdded,  const UItem*, Item);

/**
 * 
 */
UCLASS()
class GAS_LEARNING_DEMO_API AInventory : public AActor
{
	GENERATED_BODY()

public:

	AInventory();

	FOnInventoryUpdate OnInventoryUpdateDelegate;
	FOnItemAdded OnItemAddedDelegate;
	
	
	UPROPERTY()
	TArray<UItem*> Items;

	bool ReplaceItems(TArray<UItem*> InItems);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	virtual bool AddItem(UItem* NewItem);

	
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool UseItem(UItem* TheUsedItem);

	UFUNCTION()
	void RemoveItem(UItem* TheItem);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool ReduceItem(UItem* TheItem, int32 ReduceNum);
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	UItem* FindItemFromID(FName ItemID);
	

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	UItem* FindItemFromName(FString ItemName);
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	UItem* FindItem_NotFull(FName ItemID);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	UItem* FindItem_Unique(FString ItemName, int32 ItemNum);
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TArray<UItem*> GetItems() const;
};
