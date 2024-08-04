// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AuraGameplayAbilities.generated.h"

/**
 * 
 */
UCLASS()
class GAS_LEARNING_DEMO_API UAuraGameplayAbilities : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	FGameplayTag StartUpGameplayTag;
	
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float AbilityLevel = 1.f;
};
