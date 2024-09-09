// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/MVVM/MVVM_ViewModelBase.h"
#include "MVVM_LoadMenuSoltModel.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSetWidgetSwitcherIndex, int32, SwitcherIndex);
UCLASS()
class GAS_LEARNING_DEMO_API UMVVM_LoadMenuSoltModel : public UMVVM_ViewModelBase
{
	GENERATED_BODY()

public:

	/*
	 * Setter and Getter
	 */

	void SetPlayerName(FString InPlayerName);
	FString GetPlayerName() const {return PlayerName;}; 
	/*
	 * Setter and Getter End
	 */

	UPROPERTY(BlueprintAssignable)
	FSetWidgetSwitcherIndex SetWidgetSwitcherIndex;

	void InitializaSlot();

	

	UPROPERTY()
	FString LoadSlotName;

	UPROPERTY()
	int32 SlotIndex;


private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Setter, Getter, meta=(AllowPrivateAccess = true))
	FString PlayerName;

	
};
