// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Player/AuraPlayerController.h"
#include "InteractionComponent.generated.h"


class AAuraPlayerController;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractSignature, AAuraPlayerController*, PlayerController);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAS_LEARNING_DEMO_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UInteractionComponent();

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void ShowInteractionUI(AActor* TargetPlayer);
	
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void HideInteractionUI();

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void Interact(AActor* InstigatorActor, AAuraPlayerController* PlayerController);

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteractSignature OnInteractDelegate;

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY()
	TObjectPtr<UUserWidget> InteractionWidget;

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UUserWidget> InteractionWidgetClass;
};
