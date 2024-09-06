// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVM_ViewModelBase.h"
#include "MVVM_LoadScreenModel.generated.h"

/**
 * 
 */
UCLASS()
class GAS_LEARNING_DEMO_API UMVVM_LoadScreenModel : public UMVVM_ViewModelBase
{
	GENERATED_BODY()
public:
	/*
	 *	Setter
	 */
	void SetWidgetName(FString InWidgetName);

	/*
	 *	Setter End
	 */

	/*
	 *	Getter
	 */
	FString GetWidgetName() const {return WidgetName;}

	/*
	 *	Getter End
	 */

private:
	UPROPERTY(EditAnywhere ,BlueprintReadWrite, FieldNotify, Setter,Getter,meta=(AllowPrivateAccess = "true"))
	FString WidgetName;

	
};
