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
	
	virtual FString GetDescription(int32 Level);
	virtual FString GetNextLevelDescription(int32 Level);
	static  FString GetLockedDescription(int32 Level);

protected:
	float GetManaCost(float InLevel = 1) const;
	float GetCooldown(float InLevel = 1) const;
};
