// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractSignature);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAS_LEARNING_DEMO_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UInteractionComponent();

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void ShowInteractionUI();
	
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void HideInteractionUI();

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void Interact(AActor* InstigatorActor);

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteractSignature OnInteractDelegate;

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
