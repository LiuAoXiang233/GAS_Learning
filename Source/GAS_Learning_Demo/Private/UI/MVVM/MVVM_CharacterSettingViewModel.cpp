// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MVVM/MVVM_CharacterSettingViewModel.h"

void UMVVM_CharacterSettingViewModel::SetCharacterClass(FString InCharacterClass)
{
	UE_MVVM_SET_PROPERTY_VALUE(CharacterClass, InCharacterClass);
}

void UMVVM_CharacterSettingViewModel::SetCharacterName(FString InCharacterName)
{
	UE_MVVM_SET_PROPERTY_VALUE(CharacterName, InCharacterName);
}
