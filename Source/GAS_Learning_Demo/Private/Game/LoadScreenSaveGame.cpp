// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/LoadScreenSaveGame.h"

void ULoadScreenSaveGame::InitializeSaveData()
{
	
	MapName = FString("Default Map");
	
	SaveSlotStatus = Vacant;
	
	PlayerInformation.Intelligence = 0.f;
	PlayerInformation.Strength = 0.f;
	PlayerInformation.Resilience = 0.f;
	PlayerInformation.Viger = 0.f;
	PlayerInformation.PlayerLevel = 0;
	PlayerInformation.PlayerXP = 0;
	PlayerInformation.AttributePoints = 0;
	PlayerInformation.SpellPoints = 0;
	PlayerInformation.PlayerTransform = FTransform();
	PlayerInformation.PlayerClassTag = FGameplayTag();
	
	PlayerName = FString("Default Name");

	PlayerClass = FString("Default Class");

}
