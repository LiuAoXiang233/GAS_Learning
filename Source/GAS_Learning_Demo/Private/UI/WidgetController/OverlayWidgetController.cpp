// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/Data/LevelUpInfo.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "Player/AuraPlayerState.h"

void UOverlayWidgetController::BroadcastInitalValues()
{
	
	OnHealthChanged.Broadcast(GetAuraAS()->GetHealth());
	OnMaxHealthChanged.Broadcast(GetAuraAS()->GetMaxHP());
	OnManaChanged.Broadcast(GetAuraAS()->GetMana());
	OnMaxManaChanged.Broadcast(GetAuraAS()->GetMaxMP());

	
}

void UOverlayWidgetController::BindCallBackToDependencies()
{

	
	GetAuraPS()->OnXPChangedDelegate.AddUObject(this, &UOverlayWidgetController::OnXpChanged);
	GetAuraPS()->OnLevelChangedDelegate.AddLambda([this] (int32 NewLevel)
	{
		OnPlayerLevelChangedDelegate.Broadcast(NewLevel);
	});
	
	
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		GetAuraAS()->GetHealthAttribute()).AddLambda(
			[this] (const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);

			}
		);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		GetAuraAS()->GetMaxHPAttribute()).AddLambda(
			[this] (const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);

			}
		);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	GetAuraAS()->GetManaAttribute()).AddLambda(
		[this] (const FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);

		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	GetAuraAS()->GetMaxMPAttribute()).AddLambda(
		[this] (const FOnAttributeChangeData& Data)
		{
			OnMaxManaChanged.Broadcast(Data.NewValue);

		}
	);

	if (GetAuraASC())
	{
		
		
		if (GetAuraASC()->bStartUpAbilitiesGiven)
		{
			BroadcastAbilityInfo();
		}
		else
		{
			GetAuraASC()->AbilitiesGivenDelegate.AddUObject(this, &UOverlayWidgetController::BroadcastAbilityInfo);
		}

		GetAuraASC()->AbilityEquip.AddUObject(this, &UOverlayWidgetController::OnAbilityEquipped);
		
		GetAuraASC()->EffectAssetTags.AddLambda(
			[this] (const FGameplayTagContainer& GameplayAssetTagContainer)
			{
				for (const FGameplayTag& Tag : GameplayAssetTagContainer)
				{
					
					FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
					
					if ( Tag.MatchesTag(MessageTag) )
					{
						FUIWidegtRow* Row = GetDelegateRowByTag<FUIWidegtRow>(MessageWidgetDataTable, Tag);
						OnMessageWidgetDelegate.Broadcast(*Row);
					}
					
				}
				
			}
		);
	}

	
		
}


void UOverlayWidgetController::OnAbilityEquipped(const FGameplayTag& AbilityTag, const FGameplayTag& Status,
	const FGameplayTag& Slot, const FGameplayTag& PreSlot) const
{
	FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();
	FAuraAbilityInfo PreInfo;
	PreInfo.AbilityTag = GameplayTags.Abilities_None;
	PreInfo.StatusTag = GameplayTags.Abilities_Status_Unlocked;
	PreInfo.InputTag = PreSlot;
	AbilityInfoDelegate.Broadcast(PreInfo);

	FAuraAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AbilityTag);
	Info.StatusTag = Status;
	Info.InputTag = Slot;
	AbilityInfoDelegate.Broadcast(Info);
	
}

void UOverlayWidgetController::OnXpChanged(int32 InXP)
{
	const ULevelUpInfo* LevelUpInfo = GetAuraPS()->LevelUpInfo;

	const int32 Level = LevelUpInfo->FindLevelForXP(InXP);
	const int32 MaxLevel = LevelUpInfo->LevelUpInfomation.Num();

	if (Level <= MaxLevel && Level > 0)
	{
		const int32 LevelUpRequirement = LevelUpInfo->LevelUpInfomation[Level].LevelUpRequirement;
		const int32 PreLevelUpRequirement = LevelUpInfo->LevelUpInfomation[Level - 1].LevelUpRequirement;
		
		const int32 DeltaLevelUpRequirement = LevelUpRequirement - PreLevelUpRequirement;
		const int32 XpInThisLevel = InXP - PreLevelUpRequirement;

		const float XpBarPercent = static_cast<float>(XpInThisLevel) / static_cast<float>(DeltaLevelUpRequirement);

		OnLevelUpXPBarPercentChangedDelegate.Broadcast(XpBarPercent);
	}
}


