// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/FireBall.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Actor/ExplosionBall.h"
#include "Components/SphereComponent.h"

void AFireBall::SpawnExplosionBall(const FVector& SpawnLocation, int32 NumExplosionBall, AActor* IgnoreActor, float InX_Override, float InY_Override, float InZ_Override) const
{
	
	FRotator Rotator = SpawnLocation.Rotation();
	Rotator.Pitch = 10.f;
	
	const FVector Forward = Rotator.Vector();
	
	TArray<FRotator> Rotators = UAuraAbilitySystemLibrary::EvenlySpacedRotators(Forward, FVector::UpVector, 360.f, NumExplosionBall);
	
	for (FRotator Rot : Rotators)
	{
		FTransform Transform;
		Transform.SetLocation(SpawnLocation + FVector(InX_Override, InY_Override, InZ_Override));
		Transform.SetRotation(Rot.Quaternion());

		AExplosionBall* ExplosionBall = GetWorld()->SpawnActorDeferred<AExplosionBall>(
			ExplosionBallClass,
			Transform,
			FireBallOwner,
			Cast<APawn>(FireBallOwner),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		
		ExplosionBall->DamageEffectParams = DamageEffectParams;
		ExplosionBall->FirstHitActorToIgnore = IgnoreActor;
		

		ExplosionBall->FinishSpawning(Transform);
		
	}
}

void AFireBall::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AFireBall::OnSphereOverlap);
}

void AFireBall::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	AActor* SourceActor = DamageEffectParams.SourceAbilitySystemComponent->GetAvatarActor();

	if (SourceActor == OtherActor) return;

	if (!bHit) OnHit();
	FirstHitActorToIgnore = OtherActor;

	SpawnExplosionBall(OtherActor->GetActorLocation(), NumOfExplosion, OtherActor, X_Override, Y_Override, Z_Override);
	
	if (HasAuthority())
	{
		if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
		{
			FVector DeathImpulse = GetActorForwardVector() * DamageEffectParams.DeathImpulseMagnitude;
			DamageEffectParams.DeathImpulse = DeathImpulse;
			
			const bool bIsKnockback = FMath::RandRange(0, 100) < DamageEffectParams.KnockbackChance;
			if (bIsKnockback)
			{
				FRotator Rotation = FRotator();
				Rotation.Pitch = 45.f;
				const FVector KnockbackDirection = Rotation.Vector();
				const FVector Knockback = KnockbackDirection * DamageEffectParams.KnockbackMagnitude;
				DamageEffectParams.KnockbackVector = Knockback;
			}
			DamageEffectParams.TargetAbilitySystemComponent = TargetASC;
			UAuraAbilitySystemLibrary::ApplyDamageEffect(DamageEffectParams);
		}

		
		
		
		Destroy();
	}
	else bHit = true;
	
}

void AFireBall::Destroyed()
{
	
	Super::Destroyed();
}


