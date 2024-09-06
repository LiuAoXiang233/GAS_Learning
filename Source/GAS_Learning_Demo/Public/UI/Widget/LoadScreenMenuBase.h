// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoadScreenMenuBase.generated.h"

class UMVVM_ViewModelBase;
/**
 * 
 */
UCLASS()
class GAS_LEARNING_DEMO_API ULoadScreenMenuBase : public UUserWidget
{
	GENERATED_BODY()

public:
	
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void BlueprintInitializeWidget();

	
	
	
};
