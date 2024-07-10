// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbilitySystemLibrary.h"

#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Kismet/GameplayStatics.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (AAuraPlayerController* PlayerController = Cast<AAuraPlayerController>(UGameplayStatics::GetPlayerController(WorldContextObject, 0)))
	{
		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(PlayerController->GetHUD()))
		{
			AAuraPlayerState* PS = PlayerController->GetPlayerState<AAuraPlayerState>();
			UAttributeSet* As = PS->GetAttributeSet();
			UAbilitySystemComponent* Asc = PS->GetAbilitySystemComponent();
			
			const FWidgetControllerParams WidgetControllerParams = FWidgetControllerParams(PlayerController, PS, Asc, As);
			UOverlayWidgetController* WidgetController = AuraHUD->GetOverlayWidgetController(WidgetControllerParams);
			return WidgetController;
		}
	}

	return nullptr;
}

UAttributeMenuWidgetController* UAuraAbilitySystemLibrary::GetAttributeMenuWidgetController(
	const UObject* WorldContextObject)
{
	if (AAuraPlayerController* PlayerController = Cast<AAuraPlayerController>(UGameplayStatics::GetPlayerController(WorldContextObject, 0)))
	{
		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(PlayerController->GetHUD()))
		{
			AAuraPlayerState* PS = PlayerController->GetPlayerState<AAuraPlayerState>();
			UAttributeSet* As = PS->GetAttributeSet();
			UAbilitySystemComponent* Asc = PS->GetAbilitySystemComponent();
			
			const FWidgetControllerParams WidgetControllerParams = FWidgetControllerParams(PlayerController, PS, Asc, As);
			UAttributeMenuWidgetController* AttributeMenuWidgetController = AuraHUD->GetAttributeMenuWidgetController(WidgetControllerParams);
			return AttributeMenuWidgetController;
		}
	}

	return nullptr;
}
