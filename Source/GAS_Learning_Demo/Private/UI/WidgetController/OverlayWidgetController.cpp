// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/Data/LevelUpInfo.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "Player/AuraPlayerState.h"

void UOverlayWidgetController::BroadcastInitalValues()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	
	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHP());
	OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMP());

	
}

void UOverlayWidgetController::BindCallBackToDependencies()
{


	AAuraPlayerState* AuraPlayerState = CastChecked<AAuraPlayerState>(PlayerState);
	AuraPlayerState->OnXPChangedDelegate.AddUObject(this, &UOverlayWidgetController::OnXpChanged);
	AuraPlayerState->OnLevelChangedDelegate.AddLambda([this] (int32 NewLevel)
	{
		OnPlayerLevelChangedDelegate.Broadcast(NewLevel);
	});
	
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetHealthAttribute()).AddLambda(
			[this] (const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);

			}
		);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetMaxHPAttribute()).AddLambda(
			[this] (const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);

			}
		);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	AuraAttributeSet->GetManaAttribute()).AddLambda(
		[this] (const FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);

		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	AuraAttributeSet->GetMaxMPAttribute()).AddLambda(
		[this] (const FOnAttributeChangeData& Data)
		{
			OnMaxManaChanged.Broadcast(Data.NewValue);

		}
	);

	if (UAuraAbilitySystemComponent* AuraASC = Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent))
	{
		
		
		if (AuraASC->bStartUpAbilitiesGiven)
		{
			OnInitializeStartupAbilities(AuraASC);
		}
		else
		{
			AuraASC->AbilitiesGivenDelegate.AddUObject(this, &UOverlayWidgetController::OnInitializeStartupAbilities);
		}
		
		
		AuraASC->EffectAssetTags.AddLambda(
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

void UOverlayWidgetController::OnInitializeStartupAbilities(UAuraAbilitySystemComponent* AuraAbilitySystemComponent)
{
	if (!AuraAbilitySystemComponent->bStartUpAbilitiesGiven) return;

	FForEachAbility Delegate;
	
	Delegate.BindLambda([this, AuraAbilitySystemComponent] ( const FGameplayAbilitySpec& AbilitySpec)
	{
		FAuraAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AuraAbilitySystemComponent->GetGameplayTagFormAbilitySpec(AbilitySpec));
		Info.InputTag = AuraAbilitySystemComponent->GetInputTagFormAbilitySpec(AbilitySpec);
		AbilityInfoDelegate.Broadcast(Info);
	});

	// 这个函数的意义在于遍历ASC里所有可以激活的Ability，并让各个AbilitySoec作为参数执行上面的Lambda函数。
	AuraAbilitySystemComponent->ForEachAbility(Delegate);
}

void UOverlayWidgetController::OnXpChanged(int32 InXP) const
{
	const AAuraPlayerState* AuraPlayerState = CastChecked<AAuraPlayerState>(PlayerState);
	const ULevelUpInfo* LevelUpInfo = AuraPlayerState->LevelUpInfo;

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


