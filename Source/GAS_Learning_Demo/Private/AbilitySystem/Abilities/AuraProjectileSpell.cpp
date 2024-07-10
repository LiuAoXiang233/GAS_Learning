// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"

#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);


	const bool bInServer = HasAuthority(&ActivationInfo);

	if ( !bInServer ) return;

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if ( CombatInterface )
	{
		FVector WeaponLocation = CombatInterface->GetCombatSocketLocation();

		// TODO: 设置 位置 和 旋转
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(WeaponLocation);
		
	
		AAuraProjectile* Projectile =  GetWorld()->SpawnActorDeferred<AAuraProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		// TODO: 在这里，即火焰弹还没有生成完毕的时候， 给这个火焰弹添加 造成伤害的 GameplayEffect
		
		Projectile->FinishSpawning(SpawnTransform);
	}
	
	
	
}
