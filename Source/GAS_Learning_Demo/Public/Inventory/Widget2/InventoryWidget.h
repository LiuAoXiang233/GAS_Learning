// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/InventoryItem.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

class AInventory;
class UInventoryItem;
class UInventoryWidgetControllerBase;
class UScrollBox;
class UButton;
/**
 * 
 */
UCLASS()
class GAS_LEARNING_DEMO_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	
	UPROPERTY()
	TObjectPtr<UInventoryWidgetControllerBase> WidgetController;
	
protected:

	virtual void NativeConstruct() override;

	UPROPERTY(meta=(BindWidget))
	UButton* ExitButton;

	UPROPERTY(meta=(BindWidget))
	UScrollBox* ItemScrollBox;
	


public:

	UFUNCTION()
	void Exit();

	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UInventoryWidgetControllerBase* InWidgetController);
	
	UFUNCTION(BlueprintNativeEvent)
	void WidgetControllerSet();

	UFUNCTION(BlueprintPure)
	UInventoryWidgetControllerBase* GetInventoryWidgetController() const;

	void Init(AInventory* Inventory, UInventoryItem* InventoryItemInfo);
};
