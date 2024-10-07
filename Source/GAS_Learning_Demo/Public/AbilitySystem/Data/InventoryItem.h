// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InventoryItem.generated.h"


USTRUCT(BlueprintType)
struct FInventoryItemInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FName ItemID = FName("DefaultItem");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString Name = FString("Default Item");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString Description = FString("This is a default item.");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 Value = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 MaxStackSize = 64;
	
};

/**
 * 
 */
UCLASS()
class GAS_LEARNING_DEMO_API UInventoryItem : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FInventoryItemInfo> InventoryItemInfomation;

	FInventoryItemInfo FindItemDescriptionForName(const FString& ItemName, bool bLogNotFind = false) const;
};
