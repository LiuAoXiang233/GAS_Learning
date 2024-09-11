// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LoadScreenSaveGame.h"
#include "GameFramework/GameModeBase.h"
#include "AuraGameModeBase.generated.h"

class USaveGame;
class UMVVM_LoadMenuSoltModel;
class UAbilityInfo;
class UCharacterClassInfo;

/**
 * 
 */
UCLASS()
class GAS_LEARNING_DEMO_API AAuraGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Character Class Defaults")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;

	UPROPERTY(EditDefaultsOnly, Category = "Ability Info")
	TObjectPtr<UAbilityInfo> AbilityInfo;


	void SaveSlotData(UMVVM_LoadMenuSoltModel* LoadSlotModel, const int32 SlotIndex);

	void TravelToMap(UMVVM_LoadMenuSoltModel* LoadSlotModel);

	ULoadScreenSaveGame* RetrieveInGameSaveData();
	void SaveInGameSaveData(ULoadScreenSaveGame* SaveGameData);
	
	ULoadScreenSaveGame* GetSaveSlotData(const FString& SlotName, int32 SlotIndex) const;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USaveGame> LoadScreenSaveGameClass;

	UPROPERTY(EditDefaultsOnly)
	FName DefaultPlayerStartTag;
	
	UPROPERTY(EditDefaultsOnly)
	FString DefaultMapName;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> DefaultMap;
	
	UPROPERTY(EditDefaultsOnly)
	TMap<FString, TSoftObjectPtr<UWorld>> Maps;

	/*Public Override */
	AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	/*Publie Override End*/

	
protected:

	virtual void BeginPlay() override;
};
