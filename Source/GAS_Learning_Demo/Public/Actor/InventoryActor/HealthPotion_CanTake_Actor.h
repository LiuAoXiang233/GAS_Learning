// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/CanTakeActor.h"
#include "HealthPotion_CanTake_Actor.generated.h"

/**
 * 
 */
UCLASS()
class GAS_LEARNING_DEMO_API AHealthPotion_CanTake_Actor : public ACanTakeActor
{
	GENERATED_BODY()

public:
	virtual FString GetDescription() override;
	
};
