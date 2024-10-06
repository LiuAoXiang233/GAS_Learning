// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/PlayerInterface.h"
#include "Interaction/SaveAndLoadGameInterface.h"
#include "AuraCharacter.generated.h"


class AInventory;
class UInventoryComponent;
class USpringArmComponent;
class UCameraComponent;
/**
 * 
 */
UCLASS()
class GAS_LEARNING_DEMO_API AAuraCharacter : public AAuraCharacterBase, public IPlayerInterface, public ISaveAndLoadGameInterface
{
	GENERATED_BODY()
public:
	AAuraCharacter();
	void LoadInventoryAsync();
	void LoadInventory();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	void LoadProgress();
	
	

	UFUNCTION(BlueprintCallable)
	AInventory* GetInventory() const;

	/*
	 *	PlayerInterface
	 */

	virtual void AddToXP_Implementation(int32 InXP) override;
	virtual void LevelUp_Implementation() override;
	virtual int32 GetXP_Implementation() const override;
	virtual int32 FindLevelForXP_Implementation(int32 InXP) const override;
	virtual int32 GetRewardAttributePoints_Implementation(int32 Level) const override;
	virtual int32 GetRewardSpellPoints_Implementation(int32 Level) const override;
	virtual void AddToAttributePoints_Implementation(int32 InAttributePoints) override;
	virtual void AddToPlayerLevel_Implementation(int32 InPlayerLevels) override;
	virtual void AddToSpellPoints_Implementation(int32 InSpellPoints) override;
	virtual int32 GetAttributePoints_Implementation() override;
	virtual int32 GetSpellPoints_Implementation() override;
	virtual void ShowMagicCircle_Implementation(UMaterialInstance* DecalMaterial = nullptr) override;
	virtual void HideMagicCircle_Implementation() override;
	/*
	 *	End PlayerInterface
	 */

	
	/*
	 *	CombatInterface
	 */
	virtual int32 GetCharacterLevel_Implementation() override;
	/*
	 *	End CombatInterface
	 */

	/*Save And Load Game Interface*/
	virtual void SaveProgress_Implementation() override;
	/*Save And Load Game Interface End*/
private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInventoryComponent> InventoryComponent;

	virtual  void InitAbilityActorInfo() override;

	
};
