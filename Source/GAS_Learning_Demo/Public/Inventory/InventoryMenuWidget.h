// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/InventoryItem.h"
#include "Inventory/InventoryWidgetBase.h"
#include "InventoryMenuWidget.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCreateSubWidget, const UUItem*, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FClearSubWidget);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemQuantityAddedSignature, const int32, AddedQuantity);

/**
 * 
 */
UCLASS()
class GAS_LEARNING_DEMO_API UInventoryMenuWidget : public UInventoryWidgetBase
{
	GENERATED_BODY()
public:
	
	virtual void NativeConstruct() override;
	
	bool bIsChest = false;

	// 用于加载并显示一批物品
	void LoadMoreItems();

	// 检查是否可以加载更多物品
	bool CanLoadMoreItems() const;

	void SetInventory(AInventory* InInventory);

	UFUNCTION()
	void CreateNewSubWidget(const UUItem* Item);

	UFUNCTION()
	void AddItemQuantity(const int32 ItemQuantity);

	UFUNCTION(BlueprintCallable)
	FString GetDescriptionFromItem(const FString& ItemName) const;

	UFUNCTION(BlueprintCallable)
	int32 GetValueFromItem(const FString& ItemName) const;
	
	UFUNCTION(BlueprintCallable)
	bool UseItem(const FString& ItemName);

	UPROPERTY(BlueprintAssignable)
	FCreateSubWidget CreateSubWidget;
	UPROPERTY(BlueprintAssignable)
	FClearSubWidget ClearSubWidgetDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnItemQuantityAddedSignature OnItemQuantityAddedDelegate;
	// 滚动事件
	UFUNCTION(BlueprintCallable)
	void OnScroll(float ScrollOffset);
	
	UFUNCTION(BlueprintCallable)
	AInventory* GetInventory();

	UFUNCTION(BlueprintCallable)
	void refreshInventory();

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInventoryItem> InventoryItemInfo; 

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UUItem> TheClickedItem;
	
private:
	// 当前已经加载的物品数量
	int32 CurrentLoadedItems = 0;

	// 每次加载的物品数量（例如每次加载10个）
	int32 ItemsPerBatch = 10;

	// 最大物品数量
	int32 TotalItems;
	
	UPROPERTY()
	TObjectPtr<AInventory> Inventory;

};
