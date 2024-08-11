// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/AuraGameplayAbilities.h"

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
