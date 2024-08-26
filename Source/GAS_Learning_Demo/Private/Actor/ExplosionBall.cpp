// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/ExplosionBall.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Actor/FireBolt.h"
#include "Components/SphereComponent.h"

void AExplosionBall::BeginPlay()
{
	Super::BeginPlay();
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AExplosionBall::OnSphereOverlap);
	
}

void AExplosionBall::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AActor* SourceActor = DamageEffectParams.SourceAbilitySystemComponent->GetAvatarActor();
	if (SourceActor == OtherActor) return;
	
	if (FirstHitActorToIgnore == OtherActor) return;
	
	if (!bHit) OnHit();

	// FirstHitActorToIgnore = OtherActor;

	// 命中后产生剧烈的爆炸
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
