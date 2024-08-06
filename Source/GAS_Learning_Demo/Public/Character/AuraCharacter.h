// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/PlayerInterface.h"
#include "AuraCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;
/**
 * 
 */
UCLASS()
class GAS_LEARNING_DEMO_API AAuraCharacter : public AAuraCharacterBase, public IPlayerInterface
{
	GENERATED_BODY()
public:
	AAuraCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	/*
	 *	PlayerInterface
	 */

	virtual void AddToXP_Implementation(int32 InXP) override;
	/*
	 *	End PlayerInterface
	 */

	
	/*
	 *	CombatInterface
	 */
	virtual int32 GetCharacterLevel() override;
	/*
	 *	End CombatInterface
	 */
private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UCameraComponent> Camera;

	virtual  void InitAbilityActorInfo() override;
};
