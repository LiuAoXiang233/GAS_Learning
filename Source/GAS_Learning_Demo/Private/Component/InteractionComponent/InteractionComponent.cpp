// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/InteractionComponent/InteractionComponent.h"

#include "Blueprint/UserWidget.h"
#include "Character/AuraCharacter.h"
#include "Player/AuraPlayerController.h"

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UInteractionComponent::ShowInteractionUI(AActor* TargetPlayer)
{
	if (!TargetPlayer) return;
	if (InteractionWidgetClass )
	{
		AAuraCharacter* Player = Cast<AAuraCharacter>(TargetPlayer);
		AAuraPlayerController* TargetPlayerController = Cast<AAuraPlayerController>(Player->GetController());
		InteractionWidget = CreateWidget(TargetPlayerController, InteractionWidgetClass);
		InteractionWidget->AddToViewport();
	}
}

void UInteractionComponent::HideInteractionUI()
{
	if (InteractionWidget)
	{
		InteractionWidget->RemoveFromParent();
	}
}

void UInteractionComponent::Interact(AActor* InstigatorActor, AAuraPlayerController* PlayerController)
{
	if (InstigatorActor)
	{
		HideInteractionUI();
		OnInteractDelegate.Broadcast(PlayerController);
		//UE_LOG(LogTemp, Warning, TEXT("%s interacted with %s"), *InstigatorActor->GetName(), *GetOwner()->GetName());
	}
}


// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

