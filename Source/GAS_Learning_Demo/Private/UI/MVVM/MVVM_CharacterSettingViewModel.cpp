// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MVVM/MVVM_CharacterSettingViewModel.h"

#include "AbilitySystem/Data/PlayerClassDataAsset.h"

void UMVVM_CharacterSettingViewModel::SetCharacterClass(FString InCharacterClass)
{
	UE_MVVM_SET_PROPERTY_VALUE(CharacterClass, InCharacterClass);
}

void UMVVM_CharacterSettingViewModel::SetCharacterName(FString InCharacterName)
{
	UE_MVVM_SET_PROPERTY_VALUE(CharacterName, InCharacterName);
}

void UMVVM_CharacterSettingViewModel::ShowAttribute(const FGameplayTag CharacterClassTag, FString& Strength, FString& Intelligence, FString& Resilience, FString& Viger)
{
	FPlayerClassData Data = PlayerClassDataAsset->FindPlayerClassDataForTag(CharacterClassTag);
	Strength = FString::SanitizeFloat(Data.Strength);
	Intelligence = FString::SanitizeFloat(Data.Intelligence);
	Resilience = FString::SanitizeFloat(Data.Resilience);
	Viger = FString::SanitizeFloat(Data.Viger);
	
}

void UMVVM_CharacterSettingViewModel::EnterNameAndChooseClass(const FString InCharacterName, const FString InCharacterClass)
{
	SetCharacterName(InCharacterName);
	SetCharacterClass(InCharacterClass);
}
