// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraGameplayAbilities.h"
#include "AuraProjectileSpell.generated.h"

class AAuraProjectile;
/**
 * 
 */
UCLASS()
class GAS_LEARNING_DEMO_API UAuraProjectileSpell : public UAuraGameplayAbilities
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;


public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AAuraProjectile> ProjectileClass; 
};
