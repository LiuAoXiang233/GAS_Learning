// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"
#include "AuraGameplayTags.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
}

void UAuraProjectileSpell::SpawnProjectile(const FVector& TargetLocation)
{
	
	const bool bInServer = GetAvatarActorFromActorInfo()->HasAuthority();

	if ( !bInServer ) return;
	UE_LOG(LogTemp, Log, TEXT("Multicast_SpawnSkillEffect called on: %s"), *GetName());
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if ( CombatInterface )
	{
		FVector WeaponLocation = CombatInterface->GetCombatSocketLocation();
		FRotator Rotator = ( TargetLocation - WeaponLocation ).Rotation();
		

		// TODO: 设置 位置 和 旋转
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(WeaponLocation);
		SpawnTransform.SetRotation(Rotator.Quaternion());
	
		AAuraProjectile* Projectile =  GetWorld()->SpawnActorDeferred<AAuraProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		// TODO: 在这里，即火焰弹还没有生成完毕的时候， 给这个火焰弹添加 造成伤害的 GameplayEffect
		const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
		
		FGameplayEffectContextHandle EffectContextHandle = SourceASC->MakeEffectContext();
		EffectContextHandle.SetAbility(this);
		EffectContextHandle.AddSourceObject(Projectile);
		TArray<TWeakObjectPtr<AActor>> Actors;
		Actors.Add(Projectile);
		EffectContextHandle.AddActors(Actors);
		FHitResult HitResult;
		HitResult.Location = TargetLocation;
		EffectContextHandle.AddHitResult(HitResult);

		
		const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), EffectContextHandle);

		FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();

		for (auto Pair : DamageTypes)
		{
			const float ScaledDamage = Pair.Value.GetValueAtLevel(AbilityLevel);
			UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, Pair.Key, ScaledDamage);

		}
		
		Projectile->DamageEffectSpecHandle = SpecHandle;
		
		Projectile->FinishSpawning(SpawnTransform);
		
	}

	
	
}
