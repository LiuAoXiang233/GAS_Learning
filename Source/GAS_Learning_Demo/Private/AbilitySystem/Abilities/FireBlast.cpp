// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/FireBlast.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Actor/AuraProjectile.h"
#include "Actor/ExplosionBall.h"
#include "Actor/FireBall.h"
#include "Character/AuraCharacterBase.h"
#include "GameFramework/ProjectileMovementComponent.h"

FString UFireBlast::GetDescription(int32 Level)
{
	const float Cost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = FMath::Abs(GetCooldown(Level));
	
	float ScaledDamage = Damage.GetValueAtLevel(Level);
	
	if (Level == 1)
	{
		return FString::Printf(
			TEXT("<Title>火焰炸弹</>\n\n"
		"<Default>等级 ： </>"
		"<Level>%d</>\n"
		"<Default>消耗法力值: </>"
		"<Cost>%f</>\n"
		"<Default>冷却时间: </>"
		"<CoolDown>%f</>\n"
		"<Default>给敌人造成  ：</>"
		"<Damage>%f</>"
		"<Default>  伤害</>\n\n"
		"<Default>燃烧绝望的爆弹，唯有绝望之人方可展现的燃烧灵魂之黑焰。"
		"发射火焰弹，命中后爆炸出剧烈火花。</>\n\n"
		
		),
		Level, Cost, Cooldown, ScaledDamage);
	}
	else
	{
		// 给不同等级的火焰箭不同的介绍
		return FString::Printf(
			TEXT("<Title>火焰炸弹</>\n\n"
		"<Default>等级 ： </>"
		"<Level>%d</>\n"
		"<Default>消耗法力值: </>"
		"<Cost>%f</>\n"
		"<Default>冷却时间: </>"
		"<CoolDown>%f</>\n"
		"<Default>给敌人造成  ：</>"
		"<Damage>%f</>"
		"<Default>  伤害</>\n\n"
		"<Default>燃烧绝望的爆弹，唯有绝望之人方可展现的燃烧灵魂之黑焰。"
		"发射火焰弹，命中后爆炸出剧烈火花。</>\n\n"
		
		),
		Level, Cost, Cooldown, ScaledDamage);
		
		
	}
}

FString UFireBlast::GetNextLevelDescription(int32 Level)
{
	const float Cost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = FMath::Abs(GetCooldown(Level));

	float ScaledDamage = Damage.GetValueAtLevel(Level);
	
	if (Level > 5)
	{
		//最大等级是 5
		return FString::Printf(
		TEXT("<Title>火焰箭</>\n\n"
		"<Default>以达到最大等级</>")
		);
	}
	else
	{
		return FString::Printf(
			TEXT("<Title>火焰箭</>\n\n"
		"<Default>等级 ： </>"
		"<Level>%d</>\n\n"
		"<Default>给敌人造成  ：</>"
		"<Damage>%f</>"
		"<Default>  伤害</>\n"
		"<Default>消耗法力值: </>"
		"<Cost>%f</>\n"
		"<Default>冷却时间: </>"
		"<CoolDown>%f</>\n\n"
		),
		Level, ScaledDamage, Cost, Cooldown);
	}
}

void UFireBlast::SpawnExplosionBall(const FVector& SpawnLocation) const
{
	
	FRotator Rotator = SpawnLocation.Rotation();
	Rotator.Pitch = 10.f;
	
	const FVector Forward = Rotator.Vector();
	
	TArray<FRotator> Rotators = UAuraAbilitySystemLibrary::EvenlySpacedRotators(Forward, FVector::UpVector, 360.f, NumExplosionBall);
	
	for (FRotator Rot : Rotators)
	{
		FTransform Transform;
		Transform.SetLocation(SpawnLocation + FVector(0, 0, 100.f));
		Transform.SetRotation(Rot.Quaternion());

		AExplosionBall* ExplosionBall = GetWorld()->SpawnActorDeferred<AExplosionBall>(
			ExplosionBallClass,
			Transform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		
		ExplosionBall->DamageEffectParams = MakeDamageEffectParamsFromClassDefault();

		ExplosionBall->FinishSpawning(Transform);
	}
	
}

void UFireBlast::SpawnProjectileAndBindActionToProjectile(const FVector& TargetLocation, const FGameplayTag& SocketTag, bool bOverridePitch,
	float PitchOverride, AActor* HomingTarget)
{
	const bool bInServer = GetAvatarActorFromActorInfo()->HasAuthority();

	if ( !bInServer ) return;
	UE_LOG(LogTemp, Log, TEXT("Multicast_SpawnSkillEffect called on: %s"), *GetName());
	FVector WeaponLocation = ICombatInterface::Execute_GetCombatSocketLocation(
		GetAvatarActorFromActorInfo(),
		FAuraGameplayTags::Get().Montage_Attack_Weapon);
	FRotator Rotator = ( TargetLocation - WeaponLocation ).Rotation();
	
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(WeaponLocation);
	SpawnTransform.SetRotation(Rotator.Quaternion());
	
	AFireBall* Projectile =  GetWorld()->SpawnActorDeferred<AFireBall>(
		FireBallClass,
		SpawnTransform,
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetOwningActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	
	Projectile->DamageEffectParams = MakeDamageEffectParamsFromClassDefault();
	if (HomingTarget && Projectile->Implements<UCombatInterface>())
	{
		Projectile->ProjectileMovementComponent->HomingTargetComponent = HomingTarget->GetRootComponent();
	}
	else
	{
		Projectile->HomingTargetSceneComponent = NewObject<USceneComponent>(USceneComponent::StaticClass());
		Projectile->HomingTargetSceneComponent->SetWorldLocation(TargetLocation);
		Projectile->ProjectileMovementComponent->HomingTargetComponent = Projectile->HomingTargetSceneComponent;
	}

	Projectile->ProjectileMovementComponent->HomingAccelerationMagnitude = FMath::FRandRange(HomingAccelerationMin, HomingAccelerationMax);
	Projectile->ProjectileMovementComponent->bIsHomingProjectile = bLaunchHomingProjectile;
	Projectile->OnExplosionDelegate.AddUObject(this, &UFireBlast::SpawnExplosionBall);
		
	Projectile->FinishSpawning(SpawnTransform);
}


