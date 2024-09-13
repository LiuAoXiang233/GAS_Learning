// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "PlayerClassDataAsset.generated.h"


USTRUCT(BlueprintType)
struct FPlayerClassData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag PlayerClassTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Strength = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Intelligence = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Resilience = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Viger = 0;
};

/**
 * 
 */
UCLASS()
class GAS_LEARNING_DEMO_API UPlayerClassDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Class")
	TArray<FPlayerClassData> PlayerClassDatas;

	FPlayerClassData FindPlayerClassDataForTag(const FGameplayTag& PlayerClassTag, bool bLogNotFound = false) const;
};
