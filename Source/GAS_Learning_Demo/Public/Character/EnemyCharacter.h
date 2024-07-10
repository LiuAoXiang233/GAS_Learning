// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class GAS_LEARNING_DEMO_API AEnemyCharacter : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
public:
	AEnemyCharacter();

	/*
	 *	EnemyInterface
	 */
	virtual void HighLightActor() override;
	virtual void UnHighLightActor() override;
	/*
	 *	End EnemyInterface
	 */


	/*
	 *	CombatInterface
	 */
	virtual int32 GetCharacterLevel() override;
	/*
	 *	End CombatInterface
	 */
protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults", meta = (AllowPrivateAccess = "true"))
	int32 Level = 1;
	
};
