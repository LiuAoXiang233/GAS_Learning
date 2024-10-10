// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryWidgetControllerBase.generated.h"


class UInventoryComponent;
class UItemWidget;
class UItem;
class AInventory;
class UInventoryItem;
class UInventoryWidget;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class GAS_LEARNING_DEMO_API UInventoryWidgetControllerBase : public UObject
{
	GENERATED_BODY()

public:
	void Init(UInventoryWidget* InWidget);
	
	UFUNCTION(BlueprintCallable)
	void AddWidgetToScrollBox(UItem* NewItem);

	AInventory* GetInventory() const;

	UInventoryComponent* GetInventoryComponent();

	void SetInventory(AInventory* NewInventory);

	void SetInventoryComponent(UInventoryComponent* InInventoryComponent);

	
	
	// 用于加载并显示一批物品
	void LoadMoreItems();

	// 检查是否可以加载更多物品
	bool CanLoadMoreItems() const;

	UFUNCTION(BlueprintCallable)
	FString GetDescriptionFromItem(const FString& ItemName) const;

	UFUNCTION(BlueprintCallable)
	int32 GetValueFromItem(const FString& ItemName) const;
	
	UFUNCTION(BlueprintCallable)
	bool UseItem(UItem* TheUsedItem);

	UFUNCTION(BlueprintCallable)
	void OnScroll(float ScrollOffset);

	UFUNCTION()
	void OnItemClicked(UItem* TheItem);

	UFUNCTION()
	void OnItemUsed(UItem* TheItem, int32 UsedQuantity, UItemWidget* TheUsedItemWidget);
	
private:

	UPROPERTY()
	TObjectPtr<UInventoryWidget> Widget;
	
	UPROPERTY()
	TObjectPtr<AInventory> Inventory;

	UPROPERTY()
	TObjectPtr<UInventoryComponent> InventoryComponent;

	// 当前已经加载的物品数量
	int32 CurrentLoadedItems = 0;

	// 每次加载的物品数量（例如每次加载10个）
	int32 ItemsPerBatch = 10;

	// 最大物品数量
	int32 TotalItems;

	UPROPERTY()
	TObjectPtr<UItem> TheClickedItem;
	
public:
	UPROPERTY(BlueprintReadWrite, Category="Item")
	TObjectPtr<UInventoryItem> AllItemInfo;

	UPROPERTY(EditDefaultsOnly, Category="Item")
	TSubclassOf<UItemWidget> ItemWidgetClass;
};


