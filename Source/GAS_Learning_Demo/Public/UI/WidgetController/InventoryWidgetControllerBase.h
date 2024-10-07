// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryWidgetControllerBase.generated.h"


class UUItem;
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
	void AddWidgetToScrollBox(UUItem* NewItem);

	AInventory* GetInventory() const;

	void SetInventory(AInventory* NewInventory);

	// 用于加载并显示一批物品
	void LoadMoreItems();

	// 检查是否可以加载更多物品
	bool CanLoadMoreItems() const;

	UFUNCTION(BlueprintCallable)
	FString GetDescriptionFromItem(const FString& ItemName) const;

	UFUNCTION(BlueprintCallable)
	int32 GetValueFromItem(const FString& ItemName) const;
	
	UFUNCTION(BlueprintCallable)
	bool UseItem(const FString& ItemName);

	UFUNCTION(BlueprintCallable)
	void OnScroll(float ScrollOffset);
	
private:

	UPROPERTY()
	TObjectPtr<UInventoryWidget> Widget;
	
	UPROPERTY()
	TObjectPtr<AInventory> Inventory;

	// 当前已经加载的物品数量
	int32 CurrentLoadedItems = 0;

	// 每次加载的物品数量（例如每次加载10个）
	int32 ItemsPerBatch = 10;

	// 最大物品数量
	int32 TotalItems;
	
public:
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UInventoryItem> AllItemInfo;
};


