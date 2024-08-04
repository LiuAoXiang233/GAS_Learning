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

	bStartUpAbilitiesGiven = true;
	AbilitiesGivenDelegate.Broadcast(this);
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

void UAuraAbilitySystemComponent::ForEachAbility(const FForEachAbility& Delegate)
{
	FScopedAbilityListLock AbilityListLock(*this);
	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!Delegate.ExecuteIfBound(AbilitySpec))
		{
			UE_LOG(LogTemp, Error, TEXT("未能调用函数 [%hs]"), __FUNCTION__);
		}
		
	}
}

FGameplayTag UAuraAbilitySystemComponent::GetGameplayTagFormAbilitySpec(const FGameplayAbilitySpec& GameplayAbilitySpec)
{
	if (GameplayAbilitySpec.Ability)
	{
		for (FGameplayTag Tag : GameplayAbilitySpec.Ability.Get()->AbilityTags)
		{
			if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Abilities"))))
			{
				return Tag;
			}
		}
	}

	return FGameplayTag();
}

FGameplayTag UAuraAbilitySystemComponent::GetInputTagFormAbilitySpec(const FGameplayAbilitySpec& GameplayAbilitySpec)
{
	for (FGameplayTag Tag : GameplayAbilitySpec.DynamicAbilityTags)
	{
		if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("InputTag"))))
		{
			return Tag;
		}
	}

	return FGameplayTag();
}

void UAuraAbilitySystemComponent::OnRep_ActivateAbilities()
{
	Super::OnRep_ActivateAbilities();
	if (!bStartUpAbilitiesGiven)
	{
		bStartUpAbilitiesGiven = true;
		AbilitiesGivenDelegate.Broadcast(this);
	}
	
}


void UAuraAbilitySystemComponent::ClintEffectApplied_Implementation(UAbilitySystemComponent* AbilitySystemComponent,
                                                                    const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTags.Broadcast(TagContainer);
	
	
}
