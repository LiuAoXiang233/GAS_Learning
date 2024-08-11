// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/AuraDamageGameplayAbilities.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

void UAuraDamageGameplayAbilities::CauseDamage(AActor* Target)
{
	FGameplayEffectSpecHandle GameplayEffectSpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffectClass, GetAbilityLevel());

	for (TTuple<FGameplayTag, FScalableFloat> Pair : DamageTypes)
	{
		const float ScaledDamage = Pair.Value.GetValueAtLevel(GetAbilityLevel());
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(GameplayEffectSpecHandle, Pair.Key, ScaledDamage);
	}

	GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(*GameplayEffectSpecHandle.Data.Get(), UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target));
}

FTaggedMontage UAuraDamageGameplayAbilities::GetRandomTaggedMontageFromArray(const TArray<FTaggedMontage>& Montages)
{
	if (Montages.Num() > 0)
	{
		const int32 RandomMontage = FMath::RandRange(0, Montages.Num() - 1);
		
		return Montages[RandomMontage];
	}

	return FTaggedMontage();
}

float UAuraDamageGameplayAbilities::GetDamageByDamageType(float Level, const FGameplayTag& DamageType)
{
	return DamageTypes[DamageType].GetValueAtLevel(Level);
}
