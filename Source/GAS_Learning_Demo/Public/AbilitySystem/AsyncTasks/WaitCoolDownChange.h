// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "ActiveGameplayEffectHandle.h"
#include "WaitCoolDownChange.generated.h"


struct FGameplayEffectSpec;
class UAbilitySystemComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCoolDownChangeSignature, float, TimeRemaining);

/**
 * 
 */
UCLASS(BlueprintType, meta=(ExposedAsyncProxy = "AsyncTask"))
class GAS_LEARNING_DEMO_API UWaitCoolDownChange : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FCoolDownChangeSignature CoolDownStart;

	UPROPERTY(BlueprintAssignable)
	FCoolDownChangeSignature CoolDownEnd;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true"))
	static UWaitCoolDownChange* WaitForCoolDownChange(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayTag& InGameplayTag);

	UFUNCTION(BlueprintCallable)
	void EndTask();

protected:

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> ASC;

	FGameplayTag CoolDownTag;

	void CoolDownTagChanged(const FGameplayTag InGameplayTag, int32 NewCount);

	void OnActiveEffectAdded(UAbilitySystemComponent* TargetAsc, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle);
};
