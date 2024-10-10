// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Inventory/Inventory.h"

#include "Chest.generated.h"


class AAuraPlayerController;
class UInteractionComponent;
class AAuraCharacter;
class UInventoryMenuWidget;
class UItem;

UCLASS(BlueprintType, Blueprintable)
class GAS_LEARNING_DEMO_API AChest : public AInventory
{
	GENERATED_BODY()
	
public:	

	AChest();

	virtual bool AddItem(UItem* NewItem) override;

	UFUNCTION()
	bool RetrieveItem(const FString& ItemName, const int32 ItemNum);

	UFUNCTION(BlueprintCallable)
	void OpenChest(AAuraPlayerController* PlayerController);

	UFUNCTION(BlueprintCallable)
	void CloseChestMenu();

	UFUNCTION(BlueprintCallable)
	void SetTheplayerWhoOpenedTheBox(AActor* Player);

protected:

	virtual void BeginPlay() override;
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
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UInteractionComponent> InteractionComponent;
	
};
