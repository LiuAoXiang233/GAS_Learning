// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/AuraBeamSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AuraGameplayTags.h"
#include "GameplayTagContainer.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "GameFramework/Character.h"
#include "Interaction/EnemyInterface.h"
#include "Kismet/KismetSystemLibrary.h"

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
