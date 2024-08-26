// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/AuraProjectile.h"
#include "ExplosionBall.generated.h"

class AAuraCharacterBase;
/**
 * 
 */



UCLASS()
class GAS_LEARNING_DEMO_API AExplosionBall : public AAuraProjectile
{
	GENERATED_BODY()
	
public:
	

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	

private:
	
};
