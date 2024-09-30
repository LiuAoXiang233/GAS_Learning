// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CanTakeActor.generated.h"

class UUItem;

UCLASS()
class GAS_LEARNING_DEMO_API ACanTakeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACanTakeActor();

	UPROPERTY()
	TObjectPtr<UUItem> Item;

	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);

	virtual FString GetDescription();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	UPROPERTY(BlueprintReadOnly)
	FString Description;
private:

	UPROPERTY(EditDefaultsOnly , Category = "Item")
	FName ItemID;

	UPROPERTY(EditDefaultsOnly , Category = "Item")
	FString Name;

	

	UPROPERTY(EditDefaultsOnly , Category = "Item")
	int32 Quantity;

	UPROPERTY(EditDefaultsOnly, Category = "Item")
	int32 MaxStackSize;

};
