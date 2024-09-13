// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/MVVM/MVVM_ViewModelBase.h"
#include "MyMVVM_MainMenuModel.generated.h"

class ULoadMenuWidget;
/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOpenLoadMenuSignature);

UCLASS()
class GAS_LEARNING_DEMO_API UMyMVVM_MainMenuModel : public UMVVM_ViewModelBase
{
	GENERATED_BODY()
public:

	
	/*
	 *	Delegate
	 */

	FOpenLoadMenuSignature OpenLoadMenuDelegate;
	/*
	 * Delegate End
	 */
	
	UFUNCTION(BlueprintCallable)
	void StartButtonPressed();

	UFUNCTION(BlueprintCallable)
	void ContinueButtonPressed();

	UFUNCTION(BlueprintCallable)
	void ExitButtonPressed();

	UFUNCTION(BlueprintCallable)
	void EnterNameButtonPressed(FText InName);

	

	
};
