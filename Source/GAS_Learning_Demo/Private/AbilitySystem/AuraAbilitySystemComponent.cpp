// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAbilitySystemComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/Abilities/AuraGameplayAbilities.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "Game/LoadScreenSaveGame.h"
#include "Interaction/PlayerInterface.h"


void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::ClintEffectApplied_Implementation);

	const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();
	
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, FString::Printf(TEXT("Tag : %s"), *GameplayTags.Attribute_Secondary_Armor.ToString()));
	
}

void UAuraAbilitySystemComponent::AddCharacterAbilitiesFromSaveData(ULoadScreenSaveGame* SaveData)
{
	for (FSaveAbilities LoadedAbility : SaveData->SaveAbility)
	{
		FGameplayAbilitySpec LoadedAbilitySpec = FGameplayAbilitySpec(LoadedAbility.GameplayAbility, LoadedAbility.AbilityLevel);
		LoadedAbilitySpec.DynamicAbilityTags.AddTag(LoadedAbility.AbilitySlot);
		LoadedAbilitySpec.DynamicAbilityTags.AddTag(LoadedAbility.AbilityStatus);

		if (LoadedAbility.AbilityType == FAuraGameplayTags::Get().Abilities_Type_Offensive)
		{
			GiveAbility(LoadedAbilitySpec);
		}
		else if (LoadedAbility.AbilityType == FAuraGameplayTags::Get().Abilities_Type_Passive)
		{
			if (LoadedAbility.AbilityStatus == FAuraGameplayTags::Get().Abilities_Status_Equipped)
			{
				GiveAbilityAndActivateOnce(LoadedAbilitySpec);
			}
			else
			{
				GiveAbility(LoadedAbilitySpec);
			}
			
		}
	}
	bStartUpAbilitiesGiven = true;
	AbilitiesGivenDelegate.Broadcast();
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
		AbilitySpec.DynamicAbilityTags.AddTag(FAuraGameplayTags::Get().Abilities_Status_Equipped);
		GiveAbilityAndActivateOnce(AbilitySpec);
	}
}

void UAuraAbilitySystemComponent::AbilityInputTagPressed(const FGameplayTag& GameplayTag)
{
	if ( !GameplayTag.IsValid() ) return;
	FScopedAbilityListLock ActiveScopeLock(*this);

	for ( FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities() )
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact( GameplayTag ))
		{
			AbilitySpecInputPressed(AbilitySpec);
			if ( AbilitySpec.IsActive() )
			{
				InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputReleased, AbilitySpec.Handle, AbilitySpec.ActivationInfo.GetActivationPredictionKey());

			}
		}
		
	}
}
FGameplayAbilitySpec* UAuraAbilitySystemComponent::GetAbilitySpecWithSlot(const FGameplayTag& Slot)
{
	FScopedAbilityListLock ScopedAbilityListLock(*this);

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(Slot))
		{
			return &AbilitySpec;
		}
	}

	return nullptr;
	
}

bool UAuraAbilitySystemComponent::IsPassiveAbilityOfAbiltiySpec(const FGameplayAbilitySpec& Spec) const
{
	UAbilityInfo* AbilityInfo = UAuraAbilitySystemLibrary::GetAbilityInfo(GetAvatarActor());
	const FGameplayTag& AbilityTag = GetGameplayTagFormAbilitySpec(Spec);
	FAuraAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AbilityTag);

	return Info.AbilityType.MatchesTagExact(FAuraGameplayTags::Get().Abilities_Type_Passive);
}

bool UAuraAbilitySystemComponent::SpecHasAnySlot(const FGameplayAbilitySpec& Spec)
{
	return Spec.DynamicAbilityTags.HasTag(FGameplayTag::RequestGameplayTag(FName("InputTag")));
}



void UAuraAbilitySystemComponent::AssignSlotToAbility(FGameplayAbilitySpec& Spec, const FGameplayTag& Slot)
{
	ClearSlot(&Spec);
	Spec.DynamicAbilityTags.AddTag(Slot);
}

void UAuraAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& GameplayTag)
{
	if ( !GameplayTag.IsValid() ) return;
	FScopedAbilityListLock ActiveScopeLock(*this);

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
	FScopedAbilityListLock ActiveScopeLock(*this);

	for ( FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities() )
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact( GameplayTag ) && AbilitySpec.IsActive())
		{
			AbilitySpecInputReleased(AbilitySpec);
			InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputReleased, AbilitySpec.Handle, AbilitySpec.ActivationInfo.GetActivationPredictionKey());
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

FGameplayTag UAuraAbilitySystemComponent::GetStatusFromAbilityTag(const FGameplayTag& AbilityTag)
{
	if (FGameplayAbilitySpec* AbilitySpec = GetAbilitySpecFromAbilityTag(AbilityTag))
	{
		return GetStatusFromSpec(*AbilitySpec);
	}
	return FGameplayTag();
}

FGameplayTag UAuraAbilitySystemComponent::GetSlotFromAbilityTag(const FGameplayTag& AbilityTag)
{
	if (FGameplayAbilitySpec* AbilitySpec = GetAbilitySpecFromAbilityTag(AbilityTag))
	{
		return GetInputTagFormAbilitySpec(*AbilitySpec);
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

bool UAuraAbilitySystemComponent::SlotIsEmpty(const FGameplayTag& Slot)
{
	FScopedAbilityListLock AbilityListLock(*this);
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilityHasSlot(AbilitySpec, Slot))
		{
			return false;
		}
	}
	return true;
}

bool UAuraAbilitySystemComponent::AbilityHasSlot(const FGameplayAbilitySpec& AbilitySpec, const FGameplayTag& Slot)
{
	return AbilitySpec.DynamicAbilityTags.HasTagExact(Slot);
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

void UAuraAbilitySystemComponent::ClientEquipAbility_Implementation(const FGameplayTag& AbilityTag,
	const FGameplayTag& Status, const FGameplayTag& Slot, const FGameplayTag& PreSlot)
{
	AbilityEquip.Broadcast(AbilityTag, Status, Slot, PreSlot);
}

void UAuraAbilitySystemComponent::ServerEquipAbility_Implementation(const FGameplayTag& AbilityTag, const FGameplayTag& Slot)
{
	if (FGameplayAbilitySpec* Spec = GetAbilitySpecFromAbilityTag(AbilityTag))
	{
		const FGameplayTag& PreSlotTag = GetInputTagFormAbilitySpec(*Spec);
		const FGameplayTag& Status = GetStatusFromSpec(*Spec);

		const bool bStatusValid = Status == FAuraGameplayTags::Get().Abilities_Status_Equipped || Status == FAuraGameplayTags::Get().Abilities_Status_Unlocked;
		if (bStatusValid)
		{
			// 如果原来有哪个技能占用了这个slot，那么把原来那个技能的slot清除掉
			if(!SlotIsEmpty(Slot))			
			{
				FGameplayAbilitySpec* AbilitySpec = GetAbilitySpecWithSlot(Slot);

				if (AbilitySpec)
				{
					if (AbilityTag.MatchesTagExact(GetGameplayTagFormAbilitySpec(*AbilitySpec)))			// 如果Globe上的技能和我们选中的技能一样
					{
						//ClientEquipAbility(AbilityTag, Status, Slot, PreSlotTag);
						return;
					}

					if (IsPassiveAbilityOfAbiltiySpec(*AbilitySpec))										// 如果该技能为被动技能, 让技能停止
					{
						MulticastActivatePassiveSpell(GetGameplayTagFormAbilitySpec(*AbilitySpec), false);
						DeActivePassiveAbility.Broadcast(GetGameplayTagFormAbilitySpec(*AbilitySpec));
					}

					ClearSlot(AbilitySpec);
				}
			}

			// 如果自身有slot, 那么清除自身的 slot（如果自身是Equipped状态，那么自身原本就有一个slot，现在是重新分配，需要把原来的清除掉）
			if (!SpecHasAnySlot(*Spec))			// 如果自身没有slot，也就是说这是第一次加入到widget中
			{
				if (IsPassiveAbilityOfAbiltiySpec(*Spec))
				{
					TryActivateAbility(Spec->Handle);
					MulticastActivatePassiveSpell(GetGameplayTagFormAbilitySpec(*Spec), true);

				}
				Spec->DynamicAbilityTags.RemoveTag(GetStatusFromSpec(*Spec));
				Spec->DynamicAbilityTags.AddTag(FAuraGameplayTags::Get().Abilities_Status_Equipped);
			}
			AssignSlotToAbility(*Spec, Slot);
			

			MarkAbilitySpecDirty(*Spec);
		}
		ClientEquipAbility(AbilityTag, FAuraGameplayTags::Get().Abilities_Status_Equipped, Slot, PreSlotTag);
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

void UAuraAbilitySystemComponent::ClearSlot(FGameplayAbilitySpec* AbilitySpec)
{
	const FGameplayTag Slot = GetInputTagFormAbilitySpec(*AbilitySpec);
	AbilitySpec->DynamicAbilityTags.RemoveTag(Slot);
}

void UAuraAbilitySystemComponent::ClearAbilitiesOfSlot(const FGameplayTag& Slot)
{
	FScopedAbilityListLock ActiveScopeLock(*this);

	for (FGameplayAbilitySpec& Spec : GetActivatableAbilities())
	{
		if (AbilityHasSlot(&Spec, Slot))
		{
			ClearSlot(&Spec);
		}
	}
}

bool UAuraAbilitySystemComponent::AbilityHasSlot(FGameplayAbilitySpec* AbilitySpec, const FGameplayTag& Slot)
{
	for (FGameplayTag SlotTag : AbilitySpec->DynamicAbilityTags)
	{
		if (SlotTag.MatchesTagExact(Slot))
		{
			return true;
		}
	}
	return false;
}

void UAuraAbilitySystemComponent::MulticastActivatePassiveSpell_Implementation(const FGameplayTag& AbilityTag, bool bActivate)
{
	ActivatePassiveSpell.Broadcast(AbilityTag, bActivate);
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
