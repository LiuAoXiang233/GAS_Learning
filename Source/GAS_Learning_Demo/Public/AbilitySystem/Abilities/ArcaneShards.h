// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraDamageGameplayAbilities.h"
#include "ArcaneShards.generated.h"

/**
 * 
 */
UCLASS()
class GAS_LEARNING_DEMO_API UArcaneShards : public UAuraDamageGameplayAbilities
{
	GENERATED_BODY()

public:
	virtual FString GetDescription(int32 Level) override;
	virtual FString GetNextLevelDescription(int32 Level) override;
	
};
