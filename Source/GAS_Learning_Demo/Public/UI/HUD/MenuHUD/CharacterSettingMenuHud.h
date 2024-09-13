// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HUD/LoadScreenHud.h"
#include "CharacterSettingMenuHud.generated.h"

/**
 * 
 */
UCLASS()
class GAS_LEARNING_DEMO_API ACharacterSettingMenuHud : public ALoadScreenHud
{
	GENERATED_BODY()
protected:
	virtual void InitializeWidgetAndViewModel() override;
};
