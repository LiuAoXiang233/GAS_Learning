// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbilitySystemComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/Abilities/AuraGameplayAbilities.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "Interaction/PlayerInterface.h"


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
			AbilitySpec.DynamicAbilityTags.AddTag(FAuraGameplayTags::Get().Abilities_Status_Equipped);
			GiveAbility(AbilitySpec);
		}
		
	}

	bStartUpAbilitiesGiven = true;
	AbilitiesGivenDelegate.Broadcast();
}

void UAuraAbilitySystemComponent::AddCharacterPassiveAbilities(
	const TArray<TSubclassOf<UGameplayAbility>>& PassiveAbilities)
{
	for (const TSubclassOf<UGameplayAbility> AbilityClass : PassiveAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		GiveAbilityAndActivateOnce(AbilitySpec);
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

void UAuraAbilitySystemComponent::ForEachAbility(const FForEachAbility& Delegate)
{
	FScopedAbilityListLock AbilityListLock(*this);
	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		// 执行这个委托，
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

FGameplayTag UAuraAbilitySystemComponent::GetStatusFromSpec(const FGameplayAbilitySpec& GameplayAbilitySpec)
{
	for (FGameplayTag StautsTags : GameplayAbilitySpec.DynamicAbilityTags)
	{
		if (StautsTags.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Abilities.Status"))))
		{
			return StautsTags;
		}
	}

	return FGameplayTag();
}

FGameplayAbilitySpec* UAuraAbilitySystemComponent::GetAbilitySpecFromAbilityTag(const FGameplayTag& AbilityTag)
{
	FScopedAbilityListLock AbilityListLock(*this);

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		for (FGameplayTag Tag : AbilitySpec.Ability.Get()->AbilityTags)
		{
			if (Tag.MatchesTag(AbilityTag))
			{
				return &AbilitySpec;
			}
		}
	}

	return nullptr;
}

void UAuraAbilitySystemComponent::UpgradeAttribute(const FGameplayTag& GameplayTag)
{
	if (GetAvatarActor()->Implements<UPlayerInterface>())
	{
		if (IPlayerInterface::Execute_GetAttributePoints(GetAvatarActor()) > 0)
		{
			ServerUpgradeAttribute(GameplayTag);
		}
	}
}

void UAuraAbilitySystemComponent::ServerSpendSpellPoints_Implementation(const FGameplayTag& GameplayTag)
{
	if (FGameplayAbilitySpec* AbilitySpec = GetAbilitySpecFromAbilityTag(GameplayTag))
	{

		if (GetAvatarActor()->Implements<UPlayerInterface>())
		{
			IPlayerInterface::Execute_AddToSpellPoints(GetAvatarActor(), -1);
		}
		
		
		FAuraGameplayTags Tags = FAuraGameplayTags::Get();
		FGameplayTag StatusTag = GetStatusFromSpec(*AbilitySpec);

		if (StatusTag.MatchesTagExact(Tags.Abilities_Status_Eligible))
		{
			AbilitySpec->DynamicAbilityTags.RemoveTag(Tags.Abilities_Status_Eligible);
			AbilitySpec->DynamicAbilityTags.AddTag(Tags.Abilities_Status_Unlocked);
			
		}
		else if (StatusTag.MatchesTagExact(Tags.Abilities_Status_Equipped)|| StatusTag.MatchesTagExact(Tags.Abilities_Status_Unlocked))
		{
			AbilitySpec->Level += 1;
		}

		ClintUpdateAbilitiesStatus(GameplayTag, GetStatusFromSpec(*AbilitySpec), AbilitySpec->Level);
		MarkAbilitySpecDirty(*AbilitySpec);
	}
}

void UAuraAbilitySystemComponent::ServerUpgradeAttribute_Implementation(const FGameplayTag& GameplayTag)
{
	FGameplayEventData Payload;
	Payload.EventTag = GameplayTag;
	Payload.EventMagnitude = 1.f;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetAvatarActor(), GameplayTag, Payload);

	if (GetAvatarActor()->Implements<UPlayerInterface>())
	{
		IPlayerInterface::Execute_AddToAttributePoints(GetAvatarActor(), -1);
	}
}

void UAuraAbilitySystemComponent::UpdateAbilityStatuses(int32 Level)
{
	UAbilityInfo* Info = UAuraAbilitySystemLibrary::GetAbilityInfo(GetAvatarActor());

	for (FAuraAbilityInfo& AbilityInfo : Info->AbilityInfomation)
	{
		if ( !AbilityInfo.AbilityTag.IsValid()) continue;
		if ( Level < AbilityInfo.LevelRequirement) continue;
		if ( GetAbilitySpecFromAbilityTag(AbilityInfo.AbilityTag) == nullptr)
		{
			FGameplayAbilitySpec Spec = FGameplayAbilitySpec(AbilityInfo.Ability, 1);
			Spec.DynamicAbilityTags.AddTag(FAuraGameplayTags::Get().Abilities_Status_Eligible);
			GiveAbility(Spec);
			MarkAbilitySpecDirty(Spec);
			ClintUpdateAbilitiesStatus(AbilityInfo.AbilityTag, FAuraGameplayTags::Get().Abilities_Status_Eligible, 1);
		}
	}
}

bool UAuraAbilitySystemComponent::GetDescriptionByAbilityTag(const FGameplayTag& AbilityTag, FString& Description,FString& NextLevelDescription)
{
	if (FGameplayAbilitySpec* AbilitySpec = GetAbilitySpecFromAbilityTag(AbilityTag))
	{
		if (UAuraGameplayAbilities* Ability = Cast<UAuraGameplayAbilities>(AbilitySpec->Ability))
		{
			Description = Ability->GetDescription(AbilitySpec->Level);
			NextLevelDescription = Ability->GetNextLevelDescription(AbilitySpec->Level + 1);
			return true;
		}
	}
	
	UAbilityInfo* AbilityInfo = UAuraAbilitySystemLibrary::GetAbilityInfo(GetAvatarActor());
	Description = UAuraGameplayAbilities::GetLockedDescription(AbilityInfo->FindAbilityInfoForTag(AbilityTag).LevelRequirement);
	NextLevelDescription = FString();
	return false;
}

void UAuraAbilitySystemComponent::ClintUpdateAbilitiesStatus_Implementation(const FGameplayTag& AbilityTag, const FGameplayTag& StatusTag,  int32 AbilityLevel)
{
	AbilitiesStatusChanged.Broadcast(AbilityTag, StatusTag, AbilityLevel);
}

void UAuraAbilitySystemComponent::OnRep_ActivateAbilities()
{
	Super::OnRep_ActivateAbilities();
	if (!bStartUpAbilitiesGiven)
	{
		bStartUpAbilitiesGiven = true;
		AbilitiesGivenDelegate.Broadcast();
	}
	
}


void UAuraAbilitySystemComponent::ClintEffectApplied_Implementation(UAbilitySystemComponent* AbilitySystemComponent,
                                                                    const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	EffectAssetTags.Broadcast(TagContainer);
	
	
}
