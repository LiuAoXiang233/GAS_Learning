// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/AuraFireBolt.h"

#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Actor/AuraProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"


FString UAuraFireBolt::GetDescription(int32 Level)
{
	const float Cost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = FMath::Abs(GetCooldown(Level));
	
	float ScaledDamage = Damage.GetValueAtLevel(Level);
	
	if (Level == 1)
	{
		return FString::Printf(
			TEXT("<Title>火焰箭</>\n\n"
		"<Default>等级 ： </>"
		"<Level>%d</>\n"
		"<Default>消耗法力值: </>"
		"<Cost>%f</>\n"
		"<Default>冷却时间: </>"
		"<CoolDown>%f</>\n"
		"<Default>给敌人造成  ：</>"
		"<Damage>%f</>"
		"<Default>  伤害</>\n\n"
		"<Default>一支被赋予烈焰之力的箭矢。箭身燃烧着不熄的火焰，穿透空气时发出嘶嘶的灼烧声。"
		"传说，这种箭矢由曾经统治火焰的古代巫师所锻造。它不仅能撕裂敌人的肉体，还能点燃他们的灵魂，留下难以愈合的灼伤。</>\n\n"
		
		),
		Level, Cost, Cooldown, ScaledDamage);
	}
	else
	{
		// 给不同等级的火焰箭不同的介绍
		return FString::Printf(
			TEXT("<Title>火焰箭</>\n\n"
		"<Default>等级 ： </>"
		"<Level>%d</>\n"
		"<Default>消耗法力值: </>"
		"<Cost>%f</>\n"
		"<Default>冷却时间: </>"
		"<CoolDown>%f</>\n"
		"<Default>给敌人造成  ：</>"
		"<Damage>%f</>"
		"<Default>  伤害</>\n\n"
		"<Default>一支被赋予烈焰之力的箭矢。箭身燃烧着不熄的火焰，穿透空气时发出嘶嘶的灼烧声。"
		"传说，这种箭矢由曾经统治火焰的古代巫师所锻造。它不仅能撕裂敌人的肉体，还能点燃他们的灵魂，留下难以愈合的灼伤。</>\n\n"
		
		),
		Level, Cost, Cooldown, ScaledDamage);
	}
}

FString UAuraFireBolt::GetNextLevelDescription(int32 Level)
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

void UAuraFireBolt::SpawnProjectiles(const FVector& TargetLocation, const FGameplayTag& SocketTag, bool bOverridePitch,
	float PitchOverride, AActor* HomingTarget)
{
	const bool bInServer = GetAvatarActorFromActorInfo()->HasAuthority();

	if ( !bInServer ) return;
	UE_LOG(LogTemp, Log, TEXT("Multicast_SpawnSkillEffect called on: %s"), *GetName());
	FVector WeaponLocation = ICombatInterface::Execute_GetCombatSocketLocation(
		GetAvatarActorFromActorInfo(),
		SocketTag);
	FRotator Rotator = ( TargetLocation - WeaponLocation ).Rotation();
	if (bOverridePitch)
	{
		Rotator.Pitch = PitchOverride;
	}

	const FVector Forward = Rotator.Vector();
	const int32 NumProjectiles = FMath::Min(MaxNumProjectiles, GetAbilityLevel());
	
	TArray<FRotator> Rots = UAuraAbilitySystemLibrary::EvenlySpacedRotators(Forward, FVector::UpVector, ProjectileSpread, NumProjectiles);

	for (FRotator Rot : Rots)
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(WeaponLocation);
		SpawnTransform.SetRotation(Rot.Quaternion());
	
		AAuraProjectile* Projectile =  GetWorld()->SpawnActorDeferred<AAuraProjectile>(
			ProjectileClass,
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

		
		Projectile->FinishSpawning(SpawnTransform);
	}
	
	
}
