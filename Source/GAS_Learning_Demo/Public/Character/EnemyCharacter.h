// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/BeSavedInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "Interaction/EnemyInterface.h"
#include "EnemyCharacter.generated.h"

class UWidgetComponent;
class UBehaviorTree;
class AAuraAIController;
/**
 * 
 */
UCLASS()
class GAS_LEARNING_DEMO_API AEnemyCharacter : public AAuraCharacterBase, public IEnemyInterface, public IBeSavedInterface
{
	GENERATED_BODY()
public:
	AEnemyCharacter();
	
	UPROPERTY(BlueprintAssignable)
	FOnAttributesChangedSignature OnEnemyHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributesChangedSignature OnEnemyMaxHealthChanged;
	
	UPROPERTY(BlueprintReadOnly, Category="Combet")
	bool bHitRecating = false;

	UPROPERTY(SaveGame)
	bool bDie = false;
	

	virtual void BindEventOnDebuffTagChanged() override;
	virtual void StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount) override;
	
	void HitReactTagChanged(const FGameplayTag Tag, int32 NewCount);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Combet")
	float LifeSpan = 4.f;

	virtual void PossessedBy(AController* NewController) override;

	UPROPERTY(BlueprintReadWrite, Category="Combat")
	TObjectPtr<AActor> CombatTarget; 
	/*
	 *	EnemyInterface
	 */
	virtual void HighLightActor() override;
	virtual void UnHighLightActor() override;

	virtual void SetCombatTarget_Implementation(AActor* InTarget) override;
	virtual AActor* GetCombatTarget_Implementation() const override;
	/*
	 *	End EnemyInterface
	 */

	/*
	 *  BeSavedInterface
	 */
	virtual void BeLoaded_Implementation() override;
	virtual bool IsDestroy_Implementation() override;
	/*
	 *  End BeSaveInterface
	 */

	/*
	 *	CombatInterface
	 */
	virtual int32 GetCharacterLevel_Implementation() override;
	virtual void Die(const FVector& DeathImpulse) override;
	/*
	 *	End CombatInterface
	 */
protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;
	virtual void InitializeDefaultAttributes() const override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults", meta = (AllowPrivateAccess = "true"))
	int32 Level = 1;

	

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWidgetComponent> ProgressBar;
	
	
protected:

	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<AAuraAIController> AIController;
	
	
};
