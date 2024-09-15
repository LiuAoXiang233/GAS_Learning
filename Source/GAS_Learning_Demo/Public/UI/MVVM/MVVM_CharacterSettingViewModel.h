// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UI/MVVM/MVVM_ViewModelBase.h"
#include "MVVM_CharacterSettingViewModel.generated.h"

class UPlayerClassDataAsset;
/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCharacterClassSelectSignature, FGameplayTag, TheCharacterClass);
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

	UFUNCTION(BlueprintCallable)
	void ShowAttribute(const FGameplayTag CharacterClassTag, FString& Strength, FString& Intelligence, FString& Resilience, FString& Viger);
	
	UFUNCTION(BlueprintCallable)
	void EnterNameAndChooseClass(const FString InCharacterName, const FString InCharacterClass, const FGameplayTag InCharacterClassTag);

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnCharacterClassSelectSignature OnCharacterClassSelectDelegate;
	
private:

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Setter, Getter, FieldNotify, meta=(AllowPrivateAccess="true"))
	FString CharacterClass;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Setter, Getter, FieldNotify, meta=(AllowPrivateAccess="true"))
	FString CharacterName;
};
