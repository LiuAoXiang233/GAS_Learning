// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/AuraGameplayAbilities.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"

FString UAuraGameplayAbilities::GetDescription(int32 Level)
{
	return FString::Printf(TEXT("<Default>%s,</><Level>%d</>"), L"Default Ability Info - LoremIpsum LoremIpsum LoremIpsum LoremIpsum LoremIpsum LoremIpsum LoremIpsum LoremIpsum LoremIpsum LoremIpsum", Level);
}

FString UAuraGameplayAbilities::GetNextLevelDescription(int32 Level)
{
	return FString::Printf(TEXT("<Default>Next Level : </><Level>%d</>"), Level);
}

FString UAuraGameplayAbilities::GetLockedDescription(int32 Level)
{
	return FString::Printf(TEXT("<Default>Spell is locked, until </><Level>%d</>"), Level);
}

float UAuraGameplayAbilities::GetManaCost(float InLevel) const
{
	float ManaCost = 0.f;

	if (UGameplayEffect* GameplayEffect = GetCostGameplayEffect())
	{
		for (FGameplayModifierInfo Mod : GameplayEffect->Modifiers)
		{
			if (Mod.Attribute == UAuraAttributeSet::GetManaAttribute())
			{
				Mod.ModifierMagnitude.GetStaticMagnitudeIfPossible(InLevel, ManaCost);
				break;
			}
		}
	}
	
	
	return ManaCost;
}

float UAuraGameplayAbilities::GetCooldown(float InLevel) const
{
	float Cooldown = 0.f;

	if (UGameplayEffect* GameplayEffect = GetCooldownGameplayEffect())
	{
		GameplayEffect->DurationMagnitude.GetStaticMagnitudeIfPossible(InLevel, Cooldown);
	}
	return Cooldown;
}
