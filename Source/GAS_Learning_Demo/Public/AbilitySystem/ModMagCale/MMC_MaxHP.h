// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_MaxHP.generated.h"

/**
 * 
 */
UCLASS()
class GAS_LEARNING_DEMO_API UMMC_MaxHP : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	UMMC_MaxHP();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

private:
	FGameplayEffectAttributeCaptureDefinition VigerDef;
	FGameplayEffectAttributeCaptureDefinition ResilienceDef;
	
};
