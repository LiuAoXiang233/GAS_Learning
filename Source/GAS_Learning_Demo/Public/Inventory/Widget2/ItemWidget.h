// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemWidget.generated.h"


class UInventoryWidgetControllerBase;
class UButton;
class UItem;
/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemLeftClicked, UItem*, TheClickedItem);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnItemRightClicked, UItem*, TheClickedItem, int32, UseQuantity,UItemWidget*, TheUsedItemWidget);


UCLASS()
class GAS_LEARNING_DEMO_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION()
	void OnButtonClicked();

	UFUNCTION()
	void OnButtonRightClicked();

	UFUNCTION()
	void OnItemQuantityToZero(UItem* InTheItem);

	UFUNCTION()
	void SetWidgetController(UInventoryWidgetControllerBase* InInventoryWidgetController);

	UFUNCTION(BlueprintNativeEvent)
	void WidgetControllerSet();
	
protected:

	virtual void NativeConstruct() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	
	UPROPERTY(meta=(BindWidget))
	UButton* Button_Item;

public:

	UPROPERTY(BlueprintReadWrite)
	int32 ItemQuantity = 0;

	UPROPERTY(BlueprintReadWrite)
	int32 ItemValue = 0;
	
	UPROPERTY(BlueprintReadWrite)
	FString ItemName = FString("");

	UPROPERTY()
	TObjectPtr<UItem> TheItem;

	UPROPERTY()
	TObjectPtr<UInventoryWidgetControllerBase> WidgetController; 
	
	FOnItemLeftClicked OnItemClickedDelegate;
	FOnItemRightClicked OnItemUsedDelegate;


	
	
};
