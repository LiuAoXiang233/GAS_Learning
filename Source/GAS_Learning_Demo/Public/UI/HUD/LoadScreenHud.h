// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "LoadScreenHud.generated.h"

class ULoadScreenMenuBase;
/**
 * 
 */
UCLASS()
class GAS_LEARNING_DEMO_API ALoadScreenHud : public AHUD
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> LoadScreenMenuWidgetClass;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<ULoadScreenMenuBase> LoadScreenMenuWidget;
	
protected:

	virtual void BeginPlay() override;
	
};
