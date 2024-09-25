// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UInventory.generated.h"

class UUItem;
/**
 * 
 */
UCLASS()
class GAS_LEARNING_DEMO_API UUInventory : public UObject
{
	GENERATED_BODY()

public:

	UUInventory();
	
	UPROPERTY()
	TArray<UUItem*> Items;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItem(UUItem* NewItem);
	

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool RemoveItem(FName ItemID);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	UUItem* FindItem(FName ItemID);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	UUItem* FindItem_NotFull(FName ItemID);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TArray<UUItem*> GetItems() const;
};
