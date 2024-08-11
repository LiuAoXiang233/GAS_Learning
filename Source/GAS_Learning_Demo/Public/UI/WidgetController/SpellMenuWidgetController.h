// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuraGameplayTags.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "SpellMenuWidgetController.generated.h"

/**
 * 
 */

struct FAuraGameplayTags;

struct FCurrentSpellGlobeData
{
	FGameplayTag AbilityTag;
	FGameplayTag AbilityStatusTag;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSpellPointsChanged, int32, SpellPoints);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnSpellGlobeSelectedSignature, bool, SpendPointsButton, bool, EquippedButton, FString, Description, FString, NextLevelDescription);


UCLASS(BlueprintType, Blueprintable)
class GAS_LEARNING_DEMO_API USpellMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, Category = "GAS|Spell")
	FOnSpellPointsChanged OnSpellPointsChangedDelegate;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Spell")
	FOnSpellGlobeSelectedSignature SpellGlobeSelectedDelegate;

	UFUNCTION(BlueprintCallable)
	void SpellGlobeSelected(const FGameplayTag& AbilityTag);

	UFUNCTION(BlueprintCallable)
	void SpendPointButtonPressed();
	
	virtual void BroadcastInitalValues() override;
	virtual void BindCallBackToDependencies() override;

	

private:
	void ShouldEnableButtons(const FGameplayTag& AbilityStatusTag, int32 SpellPoints, bool& bSpendPointsButton, bool& bEquippedButton);

	FCurrentSpellGlobeData ClickedGlobeData {FAuraGameplayTags::Get().Abilities_None, FAuraGameplayTags::Get().Abilities_Status_Locked};
	int32 CurrentSpellPoints = 0;
};
