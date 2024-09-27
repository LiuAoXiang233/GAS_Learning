// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/InventoryWidgetBase.h"
#include "InventoryMenuWidget.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCreateSubWidget, const UUItem*, Item);

/**
 * 
 */
UCLASS()
class GAS_LEARNING_DEMO_API UInventoryMenuWidget : public UInventoryWidgetBase
{
	GENERATED_BODY()
public:
	
	virtual void NativeConstruct() override;

	// 用于加载并显示一批物品
	void LoadMoreItems();

	// 检查是否可以加载更多物品
	bool CanLoadMoreItems() const;


	UFUNCTION(BlueprintCallable)
	FString GetDescriptionFromItem(const FString& ItemName) const;

	UPROPERTY(BlueprintAssignable)
	FCreateSubWidget CreateSubWidget;
	// 滚动事件
	UFUNCTION(BlueprintCallable)
	void OnScroll(float ScrollOffset);
	
	UFUNCTION(BlueprintCallable)
	UUInventory* GetInventory();

private:
	// 当前已经加载的物品数量
	int32 CurrentLoadedItems = 0;

	// 每次加载的物品数量（例如每次加载10个）
	int32 ItemsPerBatch = 10;

	// 最大物品数量
	int32 TotalItems;
	
	UPROPERTY()
	TObjectPtr<UUInventory> Inventory;
};
