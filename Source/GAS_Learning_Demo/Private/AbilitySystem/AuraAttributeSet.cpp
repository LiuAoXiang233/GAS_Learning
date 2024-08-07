// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AuraAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AuraGameplayTags.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "Interaction/PlayerInterface.h"
#include "Net/UnrealNetwork.h"
#include "Player/AuraPlayerController.h"

UAuraAttributeSet::UAuraAttributeSet()
{
	const FAuraGameplayTags GameplayTags = FAuraGameplayTags::Get();

	/*
	 *	Primary Attributes
	 * 
	 */
	TagsToAttributes.Add(GameplayTags.Attribute_Primary_Strength, GetStrengthAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Primary_Intelligence, GetIntelligenceAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Primary_Resilience, GetResilienceAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Primary_Viger, GetVigerAttribute);
	

	/*
	 *	Secondary Attributes
	 * 
	 */
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_CriticalHitRate, GetCriticalHitRateAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_CriticalHitResistance, GetCriticalHitResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_Armor, GetArmorAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_Speed, GetSpeedAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_AttackPower, GetAttackPowerAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_MagicResistance, GetMagicResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_SpellStrength, GetSpellStrengthAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_MaxHP, GetMaxHPAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_MaxMP, GetMaxMPAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_PhysicalDamagePenetration, GetPhysicalDamagePenetrationAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_SpellDamagePenetration, GetSpellDamagePenetrationAttribute);
	TagsToAttributes.Add(GameplayTags.Attribute_Secondary_Armor, GetArmorAttribute);
	
	TagsToAttributes.Add(GameplayTags.Damage_Resistance_Anemo, GetResistance_AnemoAttribute);
	TagsToAttributes.Add(GameplayTags.Damage_Resistance_Cryo, GetResistance_CryoAttribute);
	TagsToAttributes.Add(GameplayTags.Damage_Resistance_Fire, GetResistance_FireAttribute);
	TagsToAttributes.Add(GameplayTags.Damage_Resistance_Water, GetResistance_WaterAttribute);
	TagsToAttributes.Add(GameplayTags.Damage_Resistance_Dendro, GetResistance_DendroAttribute);
	TagsToAttributes.Add(GameplayTags.Damage_Resistance_Geo, GetResistance_GeoAttribute);
	TagsToAttributes.Add(GameplayTags.Damage_Resistance_Electro, GetResistance_ElectroAttribute);
	TagsToAttributes.Add(GameplayTags.Damage_Resistance_Physical, GetResistance_PhysicalAttribute);
	


	

}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	/*
	 *
	 *	PrimaryAttribute
	 * 
	 */
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resilience, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Viger, COND_None, REPNOTIFY_Always);

	/*
	 *
	 *	SecondaryAttribute
	 * 
	 */
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, PhysicalDamagePenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, SpellDamagePenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MagicResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, SpellStrength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, AttackPower, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHP, COND_None, REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resistance_Anemo, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resistance_Cryo, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resistance_Dendro, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resistance_Electro, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resistance_Fire, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resistance_Geo, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resistance_Physical, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resistance_Water, COND_None, REPNOTIFY_Always);
	


	
	/*
	 *
	 *	VitalAttribute
	 * 
	 */
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	
}

void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	// 只适用于Clamp，并没有对属性更改做出任何逻辑相应而设计 
	
	Super::PreAttributeChange(Attribute, NewValue);

	if(Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHP());
	}
	
	if(Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMP());
	}
	
}

void UAuraAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceASC = Props.EffectContextHandle.GetInstigatorAbilitySystemComponent();

	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
		if(Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		if (Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetCharacter());
		}
	}

	if(Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		/*
		 *	ttt = 0x000008fcb9c08c00 (Label=L"BP_AuraCharacter0",Name="BP_AuraCharacter_C"_0)
		 *  TargetAcatarActor = 0x000008fcb9c08c00 (Label=L"BP_AuraCharacter0",Name="BP_AuraCharacter_C"_0)
		 *
		 *  所以说可以直接通过Data.Target.GetAvatarActor()获取目标
		 *  教程版本问题
		 */
		
		//   AActor* ttt = Data.Target.GetAvatarActor();
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
	
	
}

void UAuraAttributeSet::ShowDamageText(const FEffectProperties& Props, float Damage, bool bBlockedHit, bool bCriticalHit)
{
	if ( Props.SourceCharacter != Props.TargetCharacter )
	{
		if ( AAuraPlayerController* PC = Cast<AAuraPlayerController>(Props.SourceCharacter->Controller))
		{
			PC->ShowDamageNumber(Damage, Props.TargetCharacter, bBlockedHit, bCriticalHit);
			return;
		}
		if (AAuraPlayerController* PC = Cast<AAuraPlayerController>(Props.TargetCharacter->Controller))
		{
			PC->ShowDamageNumber(Damage, Props.TargetCharacter, bBlockedHit, bCriticalHit);

		}
	}
}

void UAuraAttributeSet::SendXPEvent(const FEffectProperties& Props)
{

	if (Props.TargetCharacter->Implements<UCombatInterface>())
	{
		const int32 Level = ICombatInterface::Execute_GetCharacterLevel(Props.TargetCharacter);
		const ECharacterClass CharacterClass = ICombatInterface::Execute_GetCharacterClass(Props.TargetCharacter);
		const int32 XPReward = UAuraAbilitySystemLibrary::GetXPRewardForClassLevel(Props.TargetCharacter, CharacterClass, Level);

		const FAuraGameplayTags& AuraGameplayTags = FAuraGameplayTags::Get();

		FGameplayEventData Payload;
		Payload.EventTag = AuraGameplayTags.Attribute_Meta_IncomingXP;
		Payload.EventMagnitude = XPReward;
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Props.SourceCharacter, AuraGameplayTags.Attribute_Meta_IncomingXP, Payload);
		
	}
}


void UAuraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	// 保存信息，利于回滚
	FEffectProperties Props;
	SetEffectProperties(Data, Props);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHP()));
		//UE_LOG(LogTemp, Warning, TEXT("Changed on %s , Health is : %F"), *Props.TargetAvatarActor->GetName(), GetHealth());
	}
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMP()));
	}

	
	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{

		// GetIncomingDamage 在蓝图中设置的时候一定 设置为 正数
		const float LocalIncomingDamage = GetIncomingDamage();
		SetIncomingDamage(0.f);
		if (LocalIncomingDamage > 0.f)
		{
			const float NewHealth = GetHealth() - LocalIncomingDamage;
			SetHealth(FMath::Clamp(NewHealth, 0.f, GetMaxHP()));
			const bool bFatal = NewHealth <= 0.f;

			
			if (bFatal)
			{

				// 如果敌人收到伤害死亡
				ICombatInterface* CombatInterface = Cast<ICombatInterface>(Props.TargetAvatarActor);
				if(CombatInterface)
				{
					CombatInterface->Die();
				}

				SendXPEvent(Props);
				
			}
			else
			{
				// 如果收到伤害没有死亡
				FGameplayTagContainer TagContainer;
				TagContainer.AddTag(FAuraGameplayTags::Get().Effect_HitReact);
                				
				Props.TargetASC->TryActivateAbilitiesByTag(TagContainer);
				
			}

			const bool bIsBolckedHit =UAuraAbilitySystemLibrary::IsBolckedHit(Props.EffectContextHandle);
			const bool bIsCriticalHit = UAuraAbilitySystemLibrary::IsCriticalHit(Props.EffectContextHandle);
			ShowDamageText(Props, LocalIncomingDamage, bIsBolckedHit, bIsCriticalHit);
		}
	}


	if (Data.EvaluatedData.Attribute == GetIncomingXPAttribute())
	{
		// 不知道为什么 GetIncomingXP 获取不到玩家的XP，
		const float LocalIncomingXP = Data.EffectSpec.GetSetByCallerMagnitude(FAuraGameplayTags::Get().Attribute_Meta_IncomingXP);
;
		SetIncomingXP(0.f);
		//UE_LOG(LogTemp, Warning, TEXT("Get XP [%f]"), LocalIncomingXP);

		if (Props.SourceCharacter->Implements<UPlayerInterface>() && Props.SourceCharacter->Implements<UCombatInterface>())
		{
			const int32 CurrentXP = IPlayerInterface::Execute_GetXP(Props.SourceCharacter);
			const int32 CurrentLevel = IPlayerInterface::Execute_FindLevelForXP(Props.SourceCharacter, CurrentXP);

			const int32 NewLevel = IPlayerInterface::Execute_FindLevelForXP(Props.SourceCharacter, CurrentXP + LocalIncomingXP);

			const int32 NumOfLevel = NewLevel - CurrentLevel;

			if (NumOfLevel > 0)
			{
				// 如果升级了
				// TODO: 获取属性点 和 技能点， 并且回复自身血量和蓝量
				const int32 AttributePoints = IPlayerInterface::Execute_GetRewardAttributePoints(Props.SourceCharacter, CurrentLevel);
				const int32 SpellPoints = IPlayerInterface::Execute_GetRewardSpellPoints(Props.SourceCharacter, CurrentLevel);

				IPlayerInterface::Execute_AddToPlayerLevel(Props.SourceCharacter, NumOfLevel);
				IPlayerInterface::Execute_AddToSpellPoints(Props.SourceCharacter, SpellPoints);
				IPlayerInterface::Execute_AddToAttributePoints(Props.SourceCharacter, AttributePoints);

				// 升级后恢复血量和蓝量
				bTopOffHP = true;
				bTopOffMP = true;
				
				
				IPlayerInterface::Execute_LevelUp(Props.SourceCharacter);

			}
			
			
			IPlayerInterface::Execute_AddToXP(Props.SourceCharacter, LocalIncomingXP);
		}
	}

	
}

void UAuraAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	if (Attribute == GetMaxHPAttribute() && bTopOffHP == true)
	{
		SetHealth(GetMaxHP());
		bTopOffHP = false;
	}

	if (Attribute == GetMaxMPAttribute() && bTopOffMP == true)
	{
		SetHealth(GetMaxMP());
		bTopOffMP = false;
	}
}


void UAuraAttributeSet::OnRep_CriticalHitRate(const FGameplayAttributeData& OldCriticalHitRate) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitRate, OldCriticalHitRate);
}

void UAuraAttributeSet::OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitResistance, OldCriticalHitResistance);
}

void UAuraAttributeSet::OnRep_PhysicalDamagePenetration(
	const FGameplayAttributeData& OldPhysicalDamagePenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, PhysicalDamagePenetration, OldPhysicalDamagePenetration);
}

void UAuraAttributeSet::OnRep_SpellDamagePenetration(const FGameplayAttributeData& OldSpellDamagePenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, SpellDamagePenetration, OldSpellDamagePenetration);
}

void UAuraAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Armor, OldArmor);

}

void UAuraAttributeSet::OnRep_MagicResistance(const FGameplayAttributeData& OldMagicResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MagicResistance, OldMagicResistance);

}

void UAuraAttributeSet::OnRep_Resistance_Fire(const FGameplayAttributeData& OldResistance_Fire) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resistance_Fire, OldResistance_Fire);

}

void UAuraAttributeSet::OnRep_Resistance_Water(const FGameplayAttributeData& OldResistance_Water) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resistance_Water, OldResistance_Water);

}

void UAuraAttributeSet::OnRep_Resistance_Cryo(const FGameplayAttributeData& OldResistance_Cryo) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resistance_Cryo, OldResistance_Cryo);

}

void UAuraAttributeSet::OnRep_Resistance_Anemo(const FGameplayAttributeData& OldResistance_Anemo) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resistance_Anemo, OldResistance_Anemo);

}

void UAuraAttributeSet::OnRep_Resistance_Dendro(const FGameplayAttributeData& OldResistance_Dendro) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resistance_Dendro, OldResistance_Dendro);

}

void UAuraAttributeSet::OnRep_Resistance_Geo(const FGameplayAttributeData& OldResistance_Geo) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resistance_Geo, OldResistance_Geo);

}

void UAuraAttributeSet::OnRep_Resistance_Electro(const FGameplayAttributeData& OldResistance_Electro) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resistance_Electro, OldResistance_Electro);

}

void UAuraAttributeSet::OnRep_Resistance_Physical(const FGameplayAttributeData& OldResistance_Physical) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resistance_Physical, OldResistance_Physical);

}

void UAuraAttributeSet::OnRep_SpellStrength(const FGameplayAttributeData& OldSpellStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, SpellStrength, OldSpellStrength);
}

void UAuraAttributeSet::OnRep_AttackPower(const FGameplayAttributeData& OldAttackPower) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, AttackPower, OldAttackPower);
}

void UAuraAttributeSet::OnRep_MaxHP(const FGameplayAttributeData& OldMaxHP) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHP, OldMaxHP);
}

void UAuraAttributeSet::OnRep_MaxMP(const FGameplayAttributeData& OldMaxMP) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxMP, OldMaxMP);
}

void UAuraAttributeSet::OnRep_Speed(const FGameplayAttributeData& OldSpeed) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Speed, OldSpeed)
}

void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth);
}



void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, OldMana);
}


void UAuraAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Strength, OldStrength);
}

void UAuraAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Intelligence, OldIntelligence);
}

void UAuraAttributeSet::OnRep_Resilience(const FGameplayAttributeData& OldResilence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Intelligence, OldResilence);
}

void UAuraAttributeSet::OnRep_Viger(const FGameplayAttributeData& OldViger) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Viger, OldViger);

}


