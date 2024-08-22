// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuraAbilityTypes.h"
#include "AbilitySystem/Abilities/AuraGameplayAbilities.h"
#include "Interaction/CombatInterface.h"
#include "AuraDamageGameplayAbilities.generated.h"

/**
 * 
 */
UCLASS()
class GAS_LEARNING_DEMO_API UAuraDamageGameplayAbilities : public UAuraGameplayAbilities
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintPure)
	FDamageEffectParams MakeDamageEffectParamsFromClassDefault(AActor* TargetActor = nullptr, FVector InRadialDamageOrigin = FVector::ZeroVector) const;

	UFUNCTION(BlueprintCallable)
	void CauseDamage(AActor* Target);

	UFUNCTION(BlueprintCallable)
	FTaggedMontage GetRandomTaggedMontageFromArray(const TArray<FTaggedMontage>& Montages);

	float GetAbilityDamage();

	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;
	
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FGameplayTag DamageType;
	
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FScalableFloat Damage;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float DebuffDamage = 5.f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float DebuffDuration = 3.f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float DebuffFrequence = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float DebuffChance = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float DeathImpulseMagnitude = 60.f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float KnockbackForceMagnitude = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float KnockbackChance = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	bool bIsRadialDamage = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	float DamageInnerRadius = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	float DamageOuterRadius = 0.f;
};
