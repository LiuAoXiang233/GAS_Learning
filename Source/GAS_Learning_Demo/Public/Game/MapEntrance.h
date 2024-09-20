// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/PlayerStart.h"
#include "MapEntrance.generated.h"

/**
 * 
 */
UCLASS()
class GAS_LEARNING_DEMO_API AMapEntrance : public APlayerStart
{
	GENERATED_BODY()

	// 这是一个传送拱心石， 靠近后可以传送到另一张地图上
public:

	AMapEntrance(const FObjectInitializer& ObjectInitializer);
	
	


protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);


private:
	UPROPERTY(VisibleAnywhere, Category="传送石属性")
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(VisibleAnywhere, Category="传送石属性")
	TObjectPtr<USphereComponent> Sphere;

	
	
};
