// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/LoadScreenMenuBase.h"
#include "LoadMenuWidget.generated.h"

class UMVVM_LoadMenuSoltModel;
/**
 * 
 */
UCLASS()
class GAS_LEARNING_DEMO_API ULoadMenuWidget : public ULoadScreenMenuBase
{
	GENERATED_BODY()

public:
	void InitializeSlotWidgetViewModel();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMVVM_ViewModelBase> SlotWidgetMenuViewModelClass;

private:

	UPROPERTY()
	TMap<int32, UMVVM_LoadMenuSoltModel*> LoadSlots;
	
	UPROPERTY()
	TObjectPtr<UMVVM_LoadMenuSoltModel> LoadMenuSoltModel_Default;

	UPROPERTY()
	TObjectPtr<UMVVM_LoadMenuSoltModel> LoadMenuSoltModel_0;

	UPROPERTY()
	TObjectPtr<UMVVM_LoadMenuSoltModel> LoadMenuSoltModel_1;

	UPROPERTY()
	TObjectPtr<UMVVM_LoadMenuSoltModel> LoadMenuSoltModel_2;

	UPROPERTY()
	TObjectPtr<UMVVM_LoadMenuSoltModel> LoadMenuSoltModel_3;
};
