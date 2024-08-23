// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AuraDamageGameplayAbilities.h"
#include "FireBlast.generated.h"

class AFireBall;
class AAuraProjectile;
class AExplosionBall;
/**
 * 
 */


UCLASS()
class GAS_LEARNING_DEMO_API UFireBlast : public UAuraDamageGameplayAbilities
{
	GENERATED_BODY()

public:
	virtual FString GetDescription(int32 Level) override;
	virtual FString GetNextLevelDescription(int32 Level) override;

	UFUNCTION()
	void SpawnExplosionBall(const FVector& SpawnLocation) const;

	UPROPERTY(EditDefaultsOnly)
	int32 NumExplosionBall = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AExplosionBall> ExplosionBallClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AFireBall> FireBallClass;

	UPROPERTY(EditDefaultsOnly, Category="UFireBlast")
	float HomingAccelerationMin = 1600.f;

	UPROPERTY(EditDefaultsOnly, Category="UFireBlast")
	float HomingAccelerationMax = 3200.f;

	UPROPERTY(EditDefaultsOnly, Category="UFireBlast")
	bool bLaunchHomingProjectile = true;

protected:

	UFUNCTION(BlueprintCallable)
	void SpawnProjectileAndBindActionToProjectile(const FVector& TargetLocation, const FGameplayTag& SocketTag, bool bOverridePitch,
	float PitchOverride, AActor* HomingTarget);
	
};
