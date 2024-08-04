// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AsyncTasks/WaitCoolDownChange.h"

#include "AbilitySystemComponent.h"

UWaitCoolDownChange* UWaitCoolDownChange::WaitForCoolDownChange(UAbilitySystemComponent* AbilitySystemComponent,
                                                                const FGameplayTag& InGameplayTag)
{
	UWaitCoolDownChange* WaitCoolDownChange = NewObject<UWaitCoolDownChange>();
	WaitCoolDownChange->ASC = AbilitySystemComponent;
	WaitCoolDownChange->CoolDownTag = InGameplayTag;

	if (!AbilitySystemComponent || !InGameplayTag.IsValid())
	{
		WaitCoolDownChange->EndTask();
		return nullptr;
	}

	// 当 CoolDown 结束时的委托
	AbilitySystemComponent->RegisterGameplayTagEvent(
		InGameplayTag,
		EGameplayTagEventType::NewOrRemoved)
	.AddUObject(WaitCoolDownChange, &UWaitCoolDownChange::CoolDownTagChanged);

	// 当 CoolDown 开始时的委托
	AbilitySystemComponent->OnActiveGameplayEffectAddedDelegateToSelf.AddUObject(WaitCoolDownChange, &UWaitCoolDownChange::OnActiveEffectAdded);

	return WaitCoolDownChange;
}

void UWaitCoolDownChange::EndTask()
{
	if (!IsValid(ASC)) return;

	ASC->RegisterGameplayTagEvent(CoolDownTag, EGameplayTagEventType::NewOrRemoved).RemoveAll(this);

	SetReadyToDestroy();

	MarkAsGarbage();
}

void UWaitCoolDownChange::CoolDownTagChanged(const FGameplayTag InGameplayTag, int32 NewCount)
{
	if (NewCount == 0)
	{
		CoolDownEnd.Broadcast(0.f);
	}
	
}

void UWaitCoolDownChange::OnActiveEffectAdded(UAbilitySystemComponent* TargetAsc, const FGameplayEffectSpec& EffectSpec,
	FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{
	FGameplayTagContainer AssetTagContainer;
	EffectSpec.GetAllAssetTags(AssetTagContainer);
	FGameplayTagContainer GrantedTagContainer;
	EffectSpec.GetAllGrantedTags(GrantedTagContainer);

	if (AssetTagContainer.HasTagExact(CoolDownTag) || GrantedTagContainer.HasTagExact(CoolDownTag))
	{
		FGameplayEffectQuery GameplayEffectQuery = FGameplayEffectQuery::MakeQuery_MatchAllOwningTags(CoolDownTag.GetSingleTagContainer());
		TArray<float> Times = ASC->GetActiveEffectsDuration(GameplayEffectQuery);

		if (Times.Num() > 0)
		{
			float TimeRemaining = Times[0];

			for (int i = 0; i < Times.Num(); i++)
			{
				if (Times[i] > TimeRemaining)
				{
					TimeRemaining = Times[i];
				}
			}

			CoolDownStart.Broadcast(TimeRemaining);
		}
	}
}
