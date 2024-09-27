// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/MVVM/MVVM_ViewModelBase.h"
#include "MVVM_InventoryViewModel.generated.h"


USTRUCT(BlueprintType)
struct FItemDetails
{
	GENERATED_BODY()
public:
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

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCurrentItemChanged);

/**
 * 
 */
UCLASS()
class GAS_LEARNING_DEMO_API UMVVM_InventoryViewModel : public UMVVM_ViewModelBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnCurrentItemChanged OnCurrentItemChangedDelegate;
	
	UFUNCTION(BlueprintCallable)
	FItemDetails GetCurrentItemDetails() const;

	UFUNCTION(BlueprintCallable)
	void SetCurrentItemDetails(const FItemDetails& ItemDetails);


private:
	UPROPERTY()
	FItemDetails CurrentItemDetails;
};
