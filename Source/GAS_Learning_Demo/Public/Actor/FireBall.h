// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/AuraProjectile.h"
#include "FireBall.generated.h"

class AExplosionBall;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnExplosionSignature, const FVector&/*Spawn Location*/);


/**
 * 
 */
UCLASS()
class GAS_LEARNING_DEMO_API AFireBall : public AAuraProjectile
{
	GENERATED_BODY()

public:

	FOnExplosionSignature OnExplosionDelegate;

protected:

	virtual void BeginPlay() override;
	
	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void Destroyed() override;
private:
	
	
};
