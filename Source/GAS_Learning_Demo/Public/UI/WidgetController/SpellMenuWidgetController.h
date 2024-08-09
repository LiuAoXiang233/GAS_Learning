// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "SpellMenuWidgetController.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSpellPointsChanged, int32, SpellPoints);

UCLASS(BlueprintType, Blueprintable)
class GAS_LEARNING_DEMO_API USpellMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable, Category = "GAS|Spell")
	FOnSpellPointsChanged OnSpellPointsChangedDelegate;
	
	virtual void BroadcastInitalValues() override;
	virtual void BindCallBackToDependencies() override;
	
};
