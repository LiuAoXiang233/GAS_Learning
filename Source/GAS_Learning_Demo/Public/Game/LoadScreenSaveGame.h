// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/SaveGame.h"
#include "Inventory/Inventory.h"
#include "LoadScreenSaveGame.generated.h"

/**
 * 
 */

class AInventory;
class UGameplayAbility;

UENUM(BlueprintType)
enum ESaveSlotStatus
{
	Vacant,
	Taken
};

USTRUCT()
struct FSavedActor
{
	GENERATED_BODY()

	UPROPERTY()
	FName ActorName = FName();

	UPROPERTY()
	FTransform Transform = FTransform();

	// 负责序列化我们要保存的Actor
	UPROPERTY()
	TArray<uint8> Bytes;
};

inline bool operator== (const FSavedActor& Left, const FSavedActor& Right)
{
	return Left.ActorName == Right.ActorName;
}


USTRUCT()
struct FSavedMap
{
	GENERATED_BODY()

	UPROPERTY()
	FString MapAssetName = FString();

	UPROPERTY()
	TArray<FSavedActor> SavedActors;
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

USTRUCT(BlueprintType)
struct FSaveAbilities
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Default Ability")
	TSubclassOf<UGameplayAbility> GameplayAbility;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameplayTag AbilityTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameplayTag AbilityType = FGameplayTag();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameplayTag AbilityStatus = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameplayTag AbilitySlot = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 AbilityLevel;
};

inline bool operator== (const FSaveAbilities& Left, const FSaveAbilities& Right)
{
	return Left.AbilityTag.MatchesTagExact(Right.AbilityTag);
}


USTRUCT()
struct FItemDataToSaveAndLoad
{
	GENERATED_BODY()

	UPROPERTY()
	FName ItemID;

	UPROPERTY()
	FString Name;

	UPROPERTY()
	int32 Quantity;

	UPROPERTY()
	FString Description;
	
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
	FString MapName = FString("StartMap");

	UPROPERTY()
	FString MapAssetName = FString("Default Map Asset Name");

	UPROPERTY()
	TEnumAsByte<ESaveSlotStatus> SaveSlotStatus = Vacant;

	UPROPERTY()
	bool bIsFirstSave = true;

	UPROPERTY()
	TArray<FSaveAbilities> SaveAbility;

	UPROPERTY()
	TArray<FSavedMap> SavedMaps;

	UPROPERTY()
	TArray<FItemDataToSaveAndLoad> SavedItems;
	
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

	FSavedMap GetSaveMapWithMapName(const FString& InMapName);
	bool HasMap(const FString& InMapName);
	
};
