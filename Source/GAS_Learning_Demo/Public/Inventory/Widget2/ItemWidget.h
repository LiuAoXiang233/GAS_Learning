// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class GAS_LEARNING_DEMO_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta=(BindWidget))
	UButton* Button_Item;

public:

	UPROPERTY(BlueprintReadWrite)
	int32 ItemQuantity = 0;

	UPROPERTY(BlueprintReadWrite)
	int32 ItemValue = 0;
	
	UPROPERTY(BlueprintReadWrite)
	FName ItemName = FName("");
	
	
};
