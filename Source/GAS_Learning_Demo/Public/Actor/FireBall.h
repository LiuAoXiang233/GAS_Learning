// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/AuraProjectile.h"
#include "FireBall.generated.h"

class AExplosionBall;
class AFireBall;



/**
 * 
 */
UCLASS()
class GAS_LEARNING_DEMO_API AFireBall : public AAuraProjectile
{
	GENERATED_BODY()

public:
	

	UFUNCTION()
	void SpawnExplosionBall(const FVector& SpawnLocation, int32 NumExplosionBall, AActor* IgnoreActor, float InX_Override, float InY_Override, float InZ_Override) const;

	UPROPERTY()
	TObjectPtr<AActor> FireBallOwner = nullptr;

	UPROPERTY()
	TSubclassOf<AExplosionBall> ExplosionBallClass;

	UPROPERTY()
	int32 NumOfExplosion = 0;

	UPROPERTY()
	float X_Override = 0.f;
	UPROPERTY()
	float Y_Override = 0.f;
	UPROPERTY()
	float Z_Override = 0.f;
protected:

	virtual void BeginPlay() override;
	
	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void Destroyed() override;
private:
	
	
};
