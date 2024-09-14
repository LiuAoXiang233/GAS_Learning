// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/MVVM/MVVM_ViewModelBase.h"
#include "MVVM_CharacterSettingViewModel.generated.h"

class UPlayerClassDataAsset;
/**
 * 
 */
UCLASS()
class GAS_LEARNING_DEMO_API UMVVM_CharacterSettingViewModel : public UMVVM_ViewModelBase
{
	GENERATED_BODY()

public:
	/*Setter and Getter*/
	void SetCharacterClass(FString InCharacterClass);
	FString GetCharacterClass() const {return CharacterClass;}

	void SetCharacterName(FString InCharacterName);
	FString GetCharacterName() const {return CharacterName;}
	/*Setter and Getter End*/

	UPROPERTY(EditDefaultsOnly, Category="Player Class Data")
	TObjectPtr<UPlayerClassDataAsset> PlayerClassDataAsset;
private:

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Setter, Getter, FieldNotify, meta=(AllowPrivateAccess="true"))
	FString CharacterClass;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Setter, Getter, FieldNotify, meta=(AllowPrivateAccess="true"))
	FString CharacterName;
};
