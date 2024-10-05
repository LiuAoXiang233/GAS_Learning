// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


class AInventory;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAS_LEARNING_DEMO_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	/**
	 * 
	 */
	UInventoryComponent();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	AInventory* Inventory;



protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
