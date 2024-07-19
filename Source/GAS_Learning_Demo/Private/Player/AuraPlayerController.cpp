// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerController.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AuraGameplayTags.h"
#include "EnhancedInputSubsystems.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Character/EnemyCharacter.h"
#include "Components/SplineComponent.h"
#include "Input/AuraInputComponent.h"
#include "UI/Widget/DamageTextComponent.h"


AAuraPlayerController::AAuraPlayerController()
{
	/*
	 *bReplicates是与网络复制相关的变量，它用于指示某个对象或组件是否应该通过网络进行复制。
	 *如果bReplicates设置为true，则引擎会将该对象或组件的状态发送到其他客户端，以确保它们具有相同的状态。
	 *如果设置为false，则不会进行此类复制。
	 *
	 *
	 * 如果一个实体在服务端上发生变化的时候，服务器会同步给其他客户端
	 */
	bReplicates = true;

	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
	
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
	AutoRun();
	
}

void AAuraPlayerController::ShowDamageNumber_Implementation(float DamagePower, ACharacter* TargetCharacter)
{
	if ( IsValid(TargetCharacter) && DamageTextComponentClass )
	{
		UDamageTextComponent* DamageText = NewObject<UDamageTextComponent>(TargetCharacter, DamageTextComponentClass);
		DamageText->RegisterComponent();
		DamageText->AttachToComponent(TargetCharacter->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		DamageText->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		DamageText->SetDamageText(DamagePower);
	}
}

void AAuraPlayerController::CursorTrace()
{
	
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = Cast<AEnemyCharacter>(CursorHit.GetActor());
	/**
	 *	A. 两者都为NULL
	 *		-也就是说明鼠标点在了墙壁上或者其他物体上
	 *		-什么都不做
	 *	B. LastActor == null && ThisActor == Enemy
	 *		-让ThisActor高亮
	 *	C. LastActor == Enemy && ThisActor == null
	 *		-让LastActor不高亮
	 *	D. both all == Enemy && lastActor == ThisActor
	 *		-什么都不做
	 *	E. both all == Enemy && lastActor != ThisActor
	 *		-让lastActor 不高亮
	 *		-让ThisActor 高亮
	 */
	if (LastActor == nullptr)
	{
		if (ThisActor != nullptr)
		{
			// case B:	LastActor == null && ThisActor == Enemy
			ThisActor->HighLightActor();
		}
		else
		{
			// case A:	两者都为NULL
			// Do nothing
		}
	}
	else     // LastActor != nullptr
	{
		if(ThisActor == nullptr)
		{
			// case C
			LastActor->UnHighLightActor();
		}
		else
		{
			if(LastActor == ThisActor)
			{
				// case D:
				// Do nothing
			}
			else
			{
				// case E：
				LastActor->UnHighLightActor();
				ThisActor->HighLightActor();
			}
		}
	}
}

UAuraAbilitySystemComponent* AAuraPlayerController::GetASC()
{
	if (AuraAbilitySystemComponent == nullptr)
	{
		AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn()));
	}
	return AuraAbilitySystemComponent;
}

void AAuraPlayerController::AutoRun()
{
	if ( !bAutoRunning ) return;
	
	if (APawn* ControlPawn = GetPawn())
	{
		FVector Location =  Spline->FindLocationClosestToWorldLocation(ControlPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		FVector Direction = Spline->FindDirectionClosestToWorldLocation(Location, ESplineCoordinateSpace::World);

		ControlPawn->AddMovementInput(Direction);

		const float DistanceToDestination = ( Location - CachedDestination ).Length();
		// GEngine->AddOnScreenDebugMessage(1, 2.f, FColor::Green, FString::Printf(TEXT("Distance To End : [%.2f]"), DistanceToDestination));
		if (DistanceToDestination <= ShortPressThreshold)
		{
			bAutoRunning = false;
		}
	}
	
}


void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if(Subsystem)
	{
		// 添加输入映射
		Subsystem->AddMappingContext(AuraContext, 0);
	}
	

	// 唤出鼠标，并且鼠标的样式为默认
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
	
	
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UAuraInputComponent* AuraEnhancedInputComponent = CastChecked<UAuraInputComponent>(InputComponent);
	AuraEnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
	AuraEnhancedInputComponent->BindAbilityFunc(InputConfig, this, &AAuraPlayerController::AbilityInputTagPressed, &AAuraPlayerController::AbilityInputTagReleased, &AAuraPlayerController::AbilityInputTagHeld);

}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	// return Axis2D(Value.X, Value.Y)
	const FVector2d InputAxisVector = InputActionValue.Get<FVector2d>();
	/*
	 * 获取控件旋转。这是完全对焦旋转，可能与相机方向不同（例如在第三人称视角中），
	 * 并且可能与受控角色的旋转不同（例如，它可以选择不目视俯仰或滚动）。
	 */
	const FRotator Rotation = GetControlRotation();
	
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if(APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AAuraPlayerController::AbilityInputTagPressed(const FGameplayTag InputTag)
{
	if (InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_RMB))
	{
		bTargeting = ThisActor ? true : false;
		bAutoRunning = false;
	}
	
}

void AAuraPlayerController::AbilityInputTagReleased(const FGameplayTag InputTag)
{
	if ( !InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_RMB))
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagReleased(InputTag);
		}
		return;
	}
	if ( bTargeting )
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagReleased(InputTag);
		}
	}
	else
	{
		APawn* ControllPawn = GetPawn();
		if (FollowTime <= ShortPressThreshold && ControllPawn)
		{
			if ( UNavigationPath* Path =  UNavigationSystemV1::FindPathToLocationSynchronously(this, ControllPawn->GetActorLocation(), CachedDestination) )
			{
				Spline->ClearSplinePoints();
				for (const FVector& Point : Path->PathPoints)
				{
					Spline->AddSplinePoint(Point, ESplineCoordinateSpace::World);
					// DrawDebugSphere(GetWorld(), Point, 30.f, 8, FColor::Red, false, 5.f);
					
				}
				CachedDestination = Path->PathPoints[Path->PathPoints.Num() - 1];
				bAutoRunning = true;
			}
		}
		bTargeting = false;
		FollowTime = 0.f;
	}
	
}

void AAuraPlayerController::AbilityInputTagHeld(const FGameplayTag InputTag)
{
	if ( !InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_RMB))
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagHeld(InputTag);
		}
		return;
	}

	if ( bTargeting )
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagHeld(InputTag);
		}
	}
	else
	{
		FollowTime += GetWorld()->GetDeltaSeconds();
		CachedDestination = CursorHit.ImpactPoint;
		
		if (APawn* ControllPawn = GetPawn())
		{
			const FVector WorldDirection = (CachedDestination - ControllPawn->GetActorLocation()).GetSafeNormal();
			ControllPawn->AddMovementInput(WorldDirection);
		}
	}
	
}
