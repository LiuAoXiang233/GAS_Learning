// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Inventory/Inventory.h"

#include "Chest.generated.h"


class AAuraCharacter;
class UInventoryMenuWidget;
class UUItem;

UCLASS(BlueprintType, Blueprintable)
class GAS_LEARNING_DEMO_API AChest : public AInventory
{
	GENERATED_BODY()
	
public:	

	AChest();

	virtual bool AddItem(UUItem* NewItem) override;

	UFUNCTION()
	bool RetrieveItem(const FString& ItemName, const int32 ItemNum);

	UFUNCTION(BlueprintCallable)
	void OpenChest();

	UFUNCTION(BlueprintCallable)
	void CloseChestMenu();

	UFUNCTION(BlueprintCallable)
	void SetTheplayerWhoOpenedTheBox(AActor* Player);

protected:

	virtual void BeginDestroy() override;
private:
	
	UPROPERTY(EditDefaultsOnly, Category="Chest Property")
	int32 StackSize = 0;

	UPROPERTY()
	TObjectPtr<AActor> TheplayerWhoOpenedTheBox;

	

public:

	UPROPERTY(BlueprintReadOnly, Category = "UI")
	TObjectPtr<UUserWidget> InventoryWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> InventoryWidgetClass;
	
	
};
