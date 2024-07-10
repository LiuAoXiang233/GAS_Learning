// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/AuraGameplayAbilities.h"
#include "AuraGameplayTags.h"


void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::ClintEffectApplied_Implementation);

	const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();
	
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("Tag : %s"), *GameplayTags.Attribute_Secondary_Armor.ToString()));
	
}

void UAuraAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities)
{
	for (const TSubclassOf<UGameplayAbility> AbilityClass : Abilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		if (const UAuraGameplayAbilities* AuraAbilities = Cast<UAuraGameplayAbilities>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(AuraAbilities->StartUpGameplayTag);
			GiveAbility(AbilitySpec);
		}
		
	}
}

void UAuraAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& GameplayTag)
{
	if ( !GameplayTag.IsValid() ) return;

	for ( FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities() )
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact( GameplayTag ))
		{
			AbilitySpecInputPressed(AbilitySpec);
			if ( !AbilitySpec.IsActive() )
			{
				TryActivateAbility( AbilitySpec.Handle );
			}
		}
		
	}
}

void UAuraAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& GameplayTag)
{
	if ( !GameplayTag.IsValid() ) return;

	for ( FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities() )
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact( GameplayTag ))
		{
			AbilitySpecInputReleased(AbilitySpec);
		}
		
	}
}


void UAuraAbilitySystemComponent::ClintEffectApplied_Implementation(UAbilitySystemComponent* AbilitySystemComponent,
                                                const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTags.Broadcast(TagContainer);
	
	
}
