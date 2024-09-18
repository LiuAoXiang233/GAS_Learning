// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/SaveGame.h"
#include "LoadScreenSaveGame.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum ESaveSlotStatus
{
	Vacant,
	Taken
};

USTRUCT(BlueprintType)
struct FPlayerInformation
{
	GENERATED_BODY()

	UPROPERTY()
	FGameplayTag PlayerClassTag = FGameplayTag();
	
	UPROPERTY()
	FTransform PlayerTransform = FTransform();
	
	UPROPERTY()
	int32 PlayerLevel = 0;

	UPROPERTY()
	int32 PlayerXP = 0;

	UPROPERTY()
	int32 SpellPoints = 0;

	UPROPERTY()
	int32 AttributePoints = 0;

	UPROPERTY()
	float Strength = 0;

	UPROPERTY()
	float Intelligence = 0;

	UPROPERTY()
	float Resilience = 0;

	UPROPERTY()
	float Viger = 0;
};

UCLASS()
class GAS_LEARNING_DEMO_API ULoadScreenSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FString SlotName = FString();

	UPROPERTY()
	int32 SlotIndex;

	UPROPERTY()
	FString MapName = FString("Default Map");

	UPROPERTY()
	TEnumAsByte<ESaveSlotStatus> SaveSlotStatus = Vacant;


	/*Player*/
	
	UPROPERTY()
	FPlayerInformation PlayerInformation;
	
	UPROPERTY()
	FString PlayerName = FString("Default Name");

	UPROPERTY()
	FString PlayerClass = FString("Default Class");
	
	/*Player End*/


	// 初始化
	void InitializeSaveData();
	
};
