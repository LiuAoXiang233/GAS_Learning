// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/PlayerClassDataAsset.h"
#include "UI/Widget/LoadScreenMenuBase.h"
#include "CharacterSettingMenu.generated.h"

/**
 * 
 */
UCLASS()
class GAS_LEARNING_DEMO_API UCharacterSettingMenu : public ULoadScreenMenuBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category="Player Class Data")
	TObjectPtr<UPlayerClassDataAsset> PlayerClassDataAsset;
	
};
