// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UItem.generated.h"


/**
 * 
 */
UCLASS()
class GAS_LEARNING_DEMO_API UUItem : public UObject
{
	GENERATED_BODY()

public:

	UUItem();


	void AddToQuantity(int32 AddedNumber);
	bool bSizeIsMaxStack() const;
	

	/*
	 *
	 *	属性
	 */
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FName ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 Quantity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 MaxStackSize;
	
	
};
