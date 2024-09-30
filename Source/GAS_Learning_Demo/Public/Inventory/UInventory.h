// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UInventory.generated.h"

class UUItem;


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryUpdate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemQuantityAdded, const int32, AddedQuantity);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemAdded,  const UUItem*, Item);
/**
 * 
 */
UCLASS()
class GAS_LEARNING_DEMO_API UUInventory : public UObject
{
	GENERATED_BODY()

public:

	UUInventory();

	FOnInventoryUpdate OnInventoryUpdateDelegate;
	FOnItemQuantityAdded OnItemQuantityAddedDelegate;
	FOnItemAdded OnItemAddedDelegate;

	
	UPROPERTY()
	TArray<UUItem*> Items;

	bool ReplaceItems(TArray<UUItem*> InItems);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItem(UUItem* NewItem);
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool UseItem(FString ItemName);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool RemoveItem(FName ItemID);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	UUItem* FindItem(FName ItemID);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	UUItem* FindItemFromName(FString ItemName);
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	UUItem* FindItem_NotFull(FName ItemID);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TArray<UUItem*> GetItems() const;
};
