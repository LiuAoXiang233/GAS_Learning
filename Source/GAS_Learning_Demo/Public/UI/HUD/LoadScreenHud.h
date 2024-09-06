// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "LoadScreenHud.generated.h"

class UMainMenuWidget;
class UMyMVVM_MainMenuModel;
class UMVVM_ViewModelBase;
class UMVVM_LoadScreenModel;
class ULoadScreenMenuBase;
/**
 * 
 */
UCLASS()
class GAS_LEARNING_DEMO_API ALoadScreenHud : public AHUD
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UUserWidget> MenuWidgetClass;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UUserWidget> MenuWidget;

	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UMVVM_ViewModelBase> MVVM_MenuViewModelClass;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UMVVM_ViewModelBase> MVVM_MenuViewModel;
	
protected:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void SetMenuWidgetViewModel();

	UPROPERTY(EditDefaultsOnly)
	bool bIsMainMenu = true;
	
};
