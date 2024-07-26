// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlueprintBase.h"
#include "MyBTService_FindNearisetPlayer.generated.h"

/**
 * 
 */
UCLASS()
class GAS_LEARNING_DEMO_API UMyBTService_FindNearisetPlayer : public UBTService_BlueprintBase
{
	GENERATED_BODY()
public:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FBlackboardKeySelector TargetToFollowSelector;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FBlackboardKeySelector DistanceToTargetSelector;
};
