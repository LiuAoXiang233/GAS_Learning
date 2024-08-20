// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/SpellMenuWidgetController.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "Player/AuraPlayerState.h"

void USpellMenuWidgetController::SpellGlobeSelected(const FGameplayTag& AbilityTag)
{
	if (bWaitingForEquipSelection)
	{
		FGameplayTag AbilityType = AbilityInfo->FindAbilityInfoForTag(AbilityTag).AbilityType;
		EndWaitForEquippedDelegate.Broadcast(AbilityType);
		bWaitingForEquipSelection = false;
	}
	const int32 SpellPoints = GetAuraPS()->GetSpellPoints();
	const bool bTagisValid = AbilityTag.IsValid();
	const FAuraGameplayTags Tags = FAuraGameplayTags::Get();
	const bool bTagIsNone = AbilityTag.MatchesTag(Tags.Abilities_None);
	FGameplayTag AbilityStatus;

	ClickedGlobeData.AbilityTag = AbilityTag;

	FGameplayAbilitySpec* Spec = GetAuraASC()->GetAbilitySpecFromAbilityTag(AbilityTag);
	const bool bAbilitySpecIsNullptr = Spec == nullptr;
	if (bAbilitySpecIsNullptr || bTagIsNone || !bTagisValid)
	{
		AbilityStatus = Tags.Abilities_Status_Locked;
	}
	else
	{
		AbilityStatus = GetAuraASC()->GetStatusFromSpec(*Spec);
	}
	bool bSpendPointsButton = false;
	bool bEquippedButton = false;
	ShouldEnableButtons(AbilityStatus, SpellPoints, bSpendPointsButton, bEquippedButton);

	FString Description;
	FString NextLevelDescription;
	GetAuraASC()->GetDescriptionByAbilityTag(AbilityTag, Description, NextLevelDescription);
	SpellGlobeSelectedDelegate.Broadcast(bSpendPointsButton, bEquippedButton, Description, NextLevelDescription);
}

void USpellMenuWidgetController::SpendPointButtonPressed()
{
	if (GetAuraASC())
	{
		GetAuraASC()->ServerSpendSpellPoints(ClickedGlobeData.AbilityTag);
	}
	
}

void USpellMenuWidgetController::EquipButtonPressed()
{
	const FGameplayTag AbilityType = AbilityInfo->FindAbilityInfoForTag(ClickedGlobeData.AbilityTag).AbilityType;
	WaitForEquippedDelegate.Broadcast(AbilityType);
	
	bWaitingForEquipSelection = true;

	const FGameplayTag StatusTag = GetAuraASC()->GetStatusFromAbilityTag(ClickedGlobeData.AbilityTag);
	if (StatusTag.MatchesTagExact(FAuraGameplayTags::Get().Abilities_Status_Equipped))
	{
		SelectedSlot = GetAuraASC()->GetSlotFromAbilityTag(ClickedGlobeData.AbilityTag);
	}
	
}

void USpellMenuWidgetController::BroadcastInitalValues()
{
	BroadcastAbilityInfo();
	OnSpellPointsChangedDelegate.Broadcast(GetAuraPS()->GetSpellPoints());
}

void USpellMenuWidgetController::BindCallBackToDependencies()
{
	GetAuraASC()->AbilitiesStatusChanged.AddLambda(
		[this] (const FGameplayTag& AbilityTag, const FGameplayTag& StatusTag, int32 NewLevel)
		{

			if (ClickedGlobeData.AbilityTag.MatchesTagExact(AbilityTag))
			{
				ClickedGlobeData.AbilityStatusTag = StatusTag;
				bool bSpendPointsButton = false;
				bool bEquippedButton = false;
				ShouldEnableButtons(StatusTag, CurrentSpellPoints, bSpendPointsButton, bEquippedButton);

				FString Description;
				FString NextLevelDescription;
				GetAuraASC()->GetDescriptionByAbilityTag(AbilityTag, Description, NextLevelDescription);
				SpellGlobeSelectedDelegate.Broadcast(bSpendPointsButton, bEquippedButton, Description, NextLevelDescription);
			}
			if (AbilityInfo)
			{
				FAuraAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AbilityTag);
				Info.StatusTag = StatusTag;
				AbilityInfoDelegate.Broadcast(Info);
			}
		});

	GetAuraASC()->AbilityEquip.AddUObject(this, &USpellMenuWidgetController::OnAbilityEquipped);
	
	GetAuraPS()->OnSpellPointsChangedDelegate.AddLambda(
		[this] (int32 SpellPoints)
		{
			OnSpellPointsChangedDelegate.Broadcast(SpellPoints);
			CurrentSpellPoints = SpellPoints;

			bool bSpendPointsButton = false;
			bool bEquippedButton = false;
			ShouldEnableButtons(ClickedGlobeData.AbilityStatusTag, CurrentSpellPoints, bSpendPointsButton, bEquippedButton);
			FString Description;
			FString NextLevelDescription;
			GetAuraASC()->GetDescriptionByAbilityTag(ClickedGlobeData.AbilityTag, Description, NextLevelDescription);
			SpellGlobeSelectedDelegate.Broadcast(bSpendPointsButton, bEquippedButton, Description, NextLevelDescription);
		});
}

void USpellMenuWidgetController::GlobeDiselect()
{
	if (bWaitingForEquipSelection)
	{
		FGameplayTag AbilityType = AbilityInfo->FindAbilityInfoForTag(ClickedGlobeData.AbilityTag).AbilityType;
		EndWaitForEquippedDelegate.Broadcast(AbilityType);
		bWaitingForEquipSelection = false;
	}
	ClickedGlobeData.AbilityTag = FAuraGameplayTags::Get().Abilities_None;
	ClickedGlobeData.AbilityStatusTag = FAuraGameplayTags::Get().Abilities_Status_Locked;
	SpellGlobeSelectedDelegate.Broadcast(false, false, FString(), FString());

}

void USpellMenuWidgetController::SpellRowGlobePressed(const FGameplayTag& SlotTag, const FGameplayTag& AbilityType)
{
	if (!bWaitingForEquipSelection) return;
	const FGameplayTag SelectedAbilityType = AbilityInfo->FindAbilityInfoForTag(ClickedGlobeData.AbilityTag).AbilityType;
	if (!SelectedAbilityType.MatchesTagExact(AbilityType)) return;

	
	GetAuraASC()->ServerEquipAbility(ClickedGlobeData.AbilityTag, SlotTag);
		
	
}

void USpellMenuWidgetController::OnAbilityEquipped(const FGameplayTag& AbilityTag, const FGameplayTag& Status,
	const FGameplayTag& Slot, const FGameplayTag& PreSlot)
{
	FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();
	bWaitingForEquipSelection = false;

	FAuraAbilityInfo PreInfo;
	PreInfo.AbilityTag = GameplayTags.Abilities_None;
	PreInfo.StatusTag = GameplayTags.Abilities_Status_Unlocked;
	PreInfo.InputTag = PreSlot;
	AbilityInfoDelegate.Broadcast(PreInfo);

	FAuraAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AbilityTag);
	Info.StatusTag = Status;
	Info.InputTag = Slot;
	AbilityInfoDelegate.Broadcast(Info);

	EndWaitForEquippedDelegate.Broadcast( AbilityInfo->FindAbilityInfoForTag(ClickedGlobeData.AbilityTag).AbilityType);
}

void USpellMenuWidgetController::ShouldEnableButtons(const FGameplayTag& AbilityStatusTag, int32 SpellPoints,bool& bSpendPointsButton, bool& bEquippedButton)
{
	FAuraGameplayTags Tags = FAuraGameplayTags::Get();

	if (SpellPoints > 0)
	{
		bSpendPointsButton = true;
	}else
	{
		bSpendPointsButton = false;
	}
	
	if (AbilityStatusTag .MatchesTag(Tags.Abilities_Status_Locked))
	{
		bSpendPointsButton = false;
		bEquippedButton = false;
	}
	else if (AbilityStatusTag.MatchesTag(Tags.Abilities_Status_Eligible))
	{
		bEquippedButton = false;
		
	}
	else if (AbilityStatusTag.MatchesTag(Tags.Abilities_Status_Unlocked)|| AbilityStatusTag.MatchesTag(Tags.Abilities_Status_Equipped))
	{
		bEquippedButton = true;
	}
}
