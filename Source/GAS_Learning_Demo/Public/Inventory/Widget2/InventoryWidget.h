// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/InventoryItem.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

class UInventoryComponent;
class URichTextBlock;
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

public:
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventoryWidgetControllerBase> WidgetControllerClass;
protected:

	virtual void NativeConstruct() override;

	UPROPERTY(meta=(BindWidget))
	UButton* ExitButton;

	UPROPERTY(meta=(BindWidget))
	UScrollBox* ItemScrollBox;
	
	UPROPERTY(meta=(BindWidget))
	URichTextBlock* DescriptionTextBlock;

public:

	UFUNCTION()
	void Exit();

	UFUNCTION()
	bool AddWidgetToScrollBox(UUserWidget* InWidget) const;

	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UInventoryWidgetControllerBase* InWidgetController);
	
	UFUNCTION(BlueprintNativeEvent)
	void WidgetControllerSet();

	UFUNCTION(BlueprintPure)
	UInventoryWidgetControllerBase* GetInventoryWidgetController() const;

	void Init(UInventoryItem* InventoryItemInfo, UInventoryComponent* InventoryComponent);

	void ShowDescriptionAndIcon(const FString& ItemDescription) const;

	void HideDescriptionAndIcon();
};
