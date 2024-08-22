// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/AuraBeamSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AuraGameplayTags.h"
#include "GameplayTagContainer.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "GameFramework/Character.h"
#include "Interaction/EnemyInterface.h"
#include "Kismet/KismetSystemLibrary.h"

FString UAuraBeamSpell::GetDescription(int32 Level)
{
	const float Cost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = FMath::Abs(GetCooldown(Level));
	
	float ScaledDamage = Damage.GetValueAtLevel(Level);
	
	if (Level == 1)
	{
		return FString::Printf(
			TEXT("<Title>闪电链</>\n\n"
		"<Default>等级 ： </>"
		"<Level>%d</>\n"
		"<Default>消耗法力值: </>"
		"<Cost>%f</>\n"
		"<Default>冷却时间: </>"
		"<CoolDown>%f</>\n"
		"<Default>给敌人造成  ：</>"
		"<Damage>%f</>"
		"<Default>  伤害</>\n\n"
		"<Default>在远古的时代，雷霆被视为神明的怒火，只有少数人能掌控这自然的力量。"
		"闪电链是一种极为罕见的奇迹，相传由雷神的忠实祭司所创造。这道闪电会在敌人之间迅速跳跃，仿佛带着神圣的审判，无一人能逃脱它的愤怒。然而，使用此奇迹的代价并不轻——传闻每施展一次，施法者的灵魂将逐渐被雷霆的愤怒所侵蚀。</>\n\n"
		
		),
		Level, Cost, Cooldown, ScaledDamage);
	}
	else
	{
		// 给不同等级的火焰箭不同的介绍
		return FString::Printf(
			TEXT("<Title>闪电链</>\n\n"
		"<Default>等级 ： </>"
		"<Level>%d</>\n"
		"<Default>消耗法力值: </>"
		"<Cost>%f</>\n"
		"<Default>冷却时间: </>"
		"<CoolDown>%f</>\n"
		"<Default>给敌人造成  ：</>"
		"<Damage>%f</>"
		"<Default>  伤害</>\n\n"
		"<Default>在远古的时代，雷霆被视为神明的怒火，只有少数人能掌控这自然的力量。"
		"闪电链是一种极为罕见的奇迹，相传由雷神的忠实祭司所创造。这道闪电会在敌人之间迅速跳跃，仿佛带着神圣的审判，无一人能逃脱它的愤怒。然而，使用此奇迹的代价并不轻——传闻每施展一次，施法者的灵魂将逐渐被雷霆的愤怒所侵蚀。</>\n\n"
		
		),
		Level, Cost, Cooldown, ScaledDamage);
	}
}

FString UAuraBeamSpell::GetNextLevelDescription(int32 Level)
{
	const float Cost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = FMath::Abs(GetCooldown(Level));

	float ScaledDamage = Damage.GetValueAtLevel(Level);
	
	if (Level > 5)
	{
		//最大等级是 5
		return FString::Printf(
		TEXT("<Title>闪电链</>\n\n"
		"<Default>以达到最大等级</>")
		);
	}
	else
	{
		return FString::Printf(
			TEXT("<Title>闪电链</>\n\n"
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

void UAuraBeamSpell::StoreMouseHitInfo(const FHitResult& HitResult)
{
	if (HitResult.bBlockingHit)
	{
		MouseHitLocation = HitResult.ImpactPoint;
		MouseHitActor = HitResult.GetActor();
	}
	else
	{
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
	}
}

void UAuraBeamSpell::StoreOwnerVariables()
{
	if (CurrentActorInfo)
	{
		OwnerPlayerController = CurrentActorInfo->PlayerController.Get();
		OwnerCharacter = Cast<ACharacter>(CurrentActorInfo->AvatarActor);
	}
}

void UAuraBeamSpell::TraceFirstTarget(const FVector& BeamTargetLocation)
{
	check(OwnerCharacter);
	if(OwnerCharacter->Implements<UCombatInterface>())
	{
		if (USkeletalMeshComponent* Weapon = ICombatInterface::Execute_GetWeapon(OwnerCharacter))
		{
			TArray<AActor*> IgnoreActors;
			IgnoreActors.AddUnique(OwnerCharacter);
			FHitResult HitResult;
			const FVector Start = Weapon->GetSocketLocation(FName("Tip Socket"));
			UKismetSystemLibrary::SphereTraceSingle(
				OwnerCharacter,
				Start,
				MouseHitLocation,
				45.f,
				TraceTypeQuery1,
				false,
				IgnoreActors,
				EDrawDebugTrace::None,
				HitResult,
				true
				);

			MouseHitLocation = HitResult.ImpactPoint;
			MouseHitActor = HitResult.GetActor();
		}
	}
	if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(MouseHitActor))
	{
		if (!CombatInterface->GetOnDeathDelegate().IsAlreadyBound(this, &UAuraBeamSpell::PrimaryTargetDied))
		{
			CombatInterface->GetOnDeathDelegate().AddDynamic(this, &UAuraBeamSpell::PrimaryTargetDied);
		}
	}
}

void UAuraBeamSpell::StoreAdditionalTarget(TArray<AActor*>& OutAdditionalTarget)
{
	TArray<AActor*> OverlappingActors;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetAvatarActorFromActorInfo());
	ActorsToIgnore.Add(MouseHitActor);
	UAuraAbilitySystemLibrary::GetLivePlayerWithinRadius(GetAvatarActorFromActorInfo(), OverlappingActors, ActorsToIgnore, 245.f, MouseHitLocation);

	const int32 BeamNum = FMath::Min(MaxNumOfBeam, GetAbilityLevel());
	
	UAuraAbilitySystemLibrary::GetClosestTarget(5/* BeamNum*/, OverlappingActors, OutAdditionalTarget, MouseHitLocation);

	for (AActor* Target : OutAdditionalTarget)
	{
		if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(Target))
		{
			if (!CombatInterface->GetOnDeathDelegate().IsAlreadyBound(this, &UAuraBeamSpell::AdditionalTargetDied))
			{
				CombatInterface->GetOnDeathDelegate().AddDynamic(this, &UAuraBeamSpell::AdditionalTargetDied);
			}
		}
	}
}

void UAuraBeamSpell::ApplySigleTargetDamage(AActor* Target)
{
	if (!Target->Implements<UCombatInterface>()) return;

	UAbilitySystemComponent* SelfASC = GetAbilitySystemComponentFromActorInfo();

	if (!IsValid(SelfASC)) return;
	
	FGameplayEffectContextHandle ContextHandle = SelfASC->MakeEffectContext();
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo()); 
	FGameplayEffectSpecHandle SpecHandle = SelfASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), ContextHandle);

	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, FAuraGameplayTags::Get().Damage_Electro, GetAbilityDamage());

	UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target)->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}
