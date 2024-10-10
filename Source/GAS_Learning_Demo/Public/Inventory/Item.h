// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/InventoryItem.h"
#include "Item.generated.h"


/**
 * 
 */



UCLASS(BlueprintType, Blueprintable)
class GAS_LEARNING_DEMO_API UItem : public UObject
{
	GENERATED_BODY()

public:

	UItem();
	UItem(FName InItemID, FString InName, FString InDescription, int32 InQuantity, int32 InMaxStackSize);

	void ChangeItemQuantity(int32 NewQuantity);

	void AddToQuantity(int32 AddedNumber, bool bIsAdd = true);
	bool bSizeIsMaxStack() const;
	
	
	
	int32 GetQuantity() const {return Quantity;}

	/*
	 *
	 *	属性
	 */
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FInventoryItemInfo ItemInfo;

private:
	UPROPERTY(EditAnywhere, Category = "Item")
	int32 Quantity = 0;
	
	
};
