// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "AbilitySystemComponent.h"
#include "AuraAbilityTypes.h"
#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"


struct AuraDamageStatics
{
public:
	
	
	/*
	 *	下面这个宏的意思是：
	 *	FGameplayEffectAttributeCaptureDefinition ArmorDef;

	 * 
	 */
	DECLARE_ATTRIBUTE_CAPTUREDEF(MagicResistance)				// 魔抗
	DECLARE_ATTRIBUTE_CAPTUREDEF(SpellDamagePenetration)		// 法穿
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitRate)				// 暴击率
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitResistance)			// 抗暴

	DECLARE_ATTRIBUTE_CAPTUREDEF(Resistance_Fire)			// 火抗
	DECLARE_ATTRIBUTE_CAPTUREDEF(Resistance_Water)			// 水抗
	DECLARE_ATTRIBUTE_CAPTUREDEF(Resistance_Cryo)			// 冰抗
	DECLARE_ATTRIBUTE_CAPTUREDEF(Resistance_Anemo)			// 风抗
	DECLARE_ATTRIBUTE_CAPTUREDEF(Resistance_Dendro)		    // 草抗
	DECLARE_ATTRIBUTE_CAPTUREDEF(Resistance_Geo)			// 岩抗
	DECLARE_ATTRIBUTE_CAPTUREDEF(Resistance_Electro)		// 雷抗
	DECLARE_ATTRIBUTE_CAPTUREDEF(Resistance_Physical)		// 物抗


	
	AuraDamageStatics()
	{
		/*
		 *
		 *	下面这个宏的意思是：
		 *	
		*	ArmorDef.AttributeToCapture = UAuraAttributeSet::GetArmorAttribute();
			ArmorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
			ArmorDef.bSnapshot = false;
		 *
		 * 
		 */
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, MagicResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, SpellDamagePenetration, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalHitRate, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalHitResistance, Target, false);
		
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Resistance_Fire, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Resistance_Water, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Resistance_Cryo, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Resistance_Anemo, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Resistance_Dendro, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Resistance_Geo, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Resistance_Electro, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Resistance_Physical, Target, false);


		

		

	}
	
};


static const AuraDamageStatics& DamageStatics()
{
	static AuraDamageStatics DStatics;
	return DStatics;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().MagicResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().SpellDamagePenetrationDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitRateDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitResistanceDef);

	RelevantAttributesToCapture.Add(DamageStatics().Resistance_AnemoDef);
	RelevantAttributesToCapture.Add(DamageStatics().Resistance_CryoDef);
	RelevantAttributesToCapture.Add(DamageStatics().Resistance_DendroDef);
	RelevantAttributesToCapture.Add(DamageStatics().Resistance_ElectroDef);
	RelevantAttributesToCapture.Add(DamageStatics().Resistance_FireDef);
	RelevantAttributesToCapture.Add(DamageStatics().Resistance_GeoDef);
	RelevantAttributesToCapture.Add(DamageStatics().Resistance_PhysicalDef);
	RelevantAttributesToCapture.Add(DamageStatics().Resistance_WaterDef);


}

void UExecCalc_Damage::DetermineDebuff(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
						 const FGameplayEffectSpec& EffectSpec,
						 FAggregatorEvaluateParameters EvaluateParameters,
						 const TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition>& TagsToCaptureDefs) const
{
	const FAuraGameplayTags Tags = FAuraGameplayTags::Get();
	for (const TTuple<FGameplayTag, FGameplayTag>& Pair : Tags.DamageTypesToDebuffs)
	{
		const FGameplayTag& DamageType = Pair.Key;
		const FGameplayTag& DebuffType = Pair.Value;
		const float TypeDamage = EffectSpec.GetSetByCallerMagnitude(DamageType, false, -1.f);

		if (TypeDamage > -0.5f)
		{
			// 如果造成了伤害，那么可能会对敌人挂上debuff效果


			// 获取获得Debuff的概率
			const float DebuffChance = EffectSpec.GetSetByCallerMagnitude(Tags.Debuff_Chance);

			// 获取伤害抗性
			// eg： Debuff是灼烧伤害， 应获取敌人的火焰抗性
			float TargetDebuffResistance = 0.f;
			const FGameplayTag& ResistanceTag = Tags.DamageTypesToResistance[DamageType];
			ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(TagsToCaptureDefs[ResistanceTag], EvaluateParameters, TargetDebuffResistance);
			TargetDebuffResistance = FMath::Max<float>(TargetDebuffResistance, 0.f);

			// 是否获得Debuff
			const bool bDebuff = FMath::RandRange(0, 1) < DebuffChance;

			if(bDebuff)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Debuff!!!");
				FGameplayEffectContextHandle EffectContextHandle = EffectSpec.GetEffectContext();
				UAuraAbilitySystemLibrary::SetIsSuccessfulDebuff(EffectContextHandle, bDebuff);
				UAuraAbilitySystemLibrary::SetDemageType(EffectContextHandle, DamageType);

				const float DebuffDemage = EffectSpec.GetSetByCallerMagnitude(Tags.Debuff_Damage);
				const float DebuffDuration = EffectSpec.GetSetByCallerMagnitude(Tags.Debuff_Duration);
				const float DebuffFrequency = EffectSpec.GetSetByCallerMagnitude(Tags.Debuff_Frequence);

				UAuraAbilitySystemLibrary::SetDebuffDemage(EffectContextHandle, DebuffDemage);
				UAuraAbilitySystemLibrary::SetDebuffDuration(EffectContextHandle, DebuffDuration);
				UAuraAbilitySystemLibrary::SetDebuffFrequency(EffectContextHandle, DebuffFrequency);

			}
		}
		
	}
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                              FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDefs;
	
	const FAuraGameplayTags Tags = FAuraGameplayTags::Get();
	TagsToCaptureDefs.Add(Tags.Attribute_Secondary_MagicResistance, DamageStatics().MagicResistanceDef);
	TagsToCaptureDefs.Add(Tags.Attribute_Secondary_SpellDamagePenetration, DamageStatics().SpellDamagePenetrationDef);
	TagsToCaptureDefs.Add(Tags.Attribute_Secondary_CriticalHitRate, DamageStatics().CriticalHitRateDef);
	TagsToCaptureDefs.Add(Tags.Attribute_Secondary_CriticalHitResistance, DamageStatics().CriticalHitResistanceDef);
		
	TagsToCaptureDefs.Add(Tags.Damage_Resistance_Fire, DamageStatics().Resistance_FireDef);
	TagsToCaptureDefs.Add(Tags.Damage_Resistance_Anemo, DamageStatics().Resistance_AnemoDef);
	TagsToCaptureDefs.Add(Tags.Damage_Resistance_Cryo, DamageStatics().Resistance_CryoDef);
	TagsToCaptureDefs.Add(Tags.Damage_Resistance_Dendro, DamageStatics().Resistance_DendroDef);
	TagsToCaptureDefs.Add(Tags.Damage_Resistance_Electro, DamageStatics().Resistance_ElectroDef);
	TagsToCaptureDefs.Add(Tags.Damage_Resistance_Geo, DamageStatics().Resistance_GeoDef);
	TagsToCaptureDefs.Add(Tags.Damage_Resistance_Water, DamageStatics().Resistance_WaterDef);
	TagsToCaptureDefs.Add(Tags.Damage_Resistance_Physical, DamageStatics().Resistance_PhysicalDef);
	
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();
 
	AActor* SourceActor = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	AActor* TargetActor = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	if (!TargetActor)
	{
		// 如果目标为空，那么返回。
		return;
	}
	
	// 获取玩家和敌人的等级
	int32 SourcePlayerLevel = 1;
	if (SourceActor->Implements<UCombatInterface>())
	{
		SourcePlayerLevel = ICombatInterface::Execute_GetCharacterLevel(SourceActor);
	}

	int32 TargetPlayerLevel = 1;
	if (TargetActor->Implements<UCombatInterface>())
	{
		TargetPlayerLevel = ICombatInterface::Execute_GetCharacterLevel(TargetActor);
	}
	
	

	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();
	const FGameplayTagContainer* SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();
	
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	// Debuff
	DetermineDebuff(ExecutionParams, EffectSpec, EvaluateParameters, TagsToCaptureDefs);


	// Damage
	float Damage = 0.f;
	for (const TTuple<FGameplayTag, FGameplayTag>& Pair : FAuraGameplayTags::Get().DamageTypesToResistance)
	{
		const FGameplayTag DamageTypeTag = Pair.Key;		// 伤害类型	eg： Damage.Fire
		const FGameplayTag ResistanceTag = Pair.Value;		// 抗性类型	eg:  Resistance.Fire

		checkf(TagsToCaptureDefs.Contains(ResistanceTag), TEXT("TagsToCaptureDefs 没有 [%s] 这个 tag"), *ResistanceTag.ToString());
		
		float DamageTypeValue = EffectSpec.GetSetByCallerMagnitude(DamageTypeTag);
		
		float Resitance = 0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(TagsToCaptureDefs[ResistanceTag], EvaluateParameters, Resitance);
		Resitance = FMath::Clamp(Resitance, 0.f, 100.f);
		
		DamageTypeValue *= (100.f - Resitance) / 100;
		Damage += DamageTypeValue;
	}
	
	UCharacterClassInfo* CharacterClassInfo = UAuraAbilitySystemLibrary::GetCharacterClassInfo(SourceActor);

	
	/*
	 *	SpellDamagePenetrationAmendment	    法穿修正		来自 施法者 即	SourceActor
	 *	MagicResistanceAmendment			魔抗修正		针对	 受击者	即	TargetActor
	 */
	FRealCurve* AmendmentCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("SpellDamagePenetration"), FString());
	

	float SpellDamagePenetrationAmendment = AmendmentCurve->Eval(SourcePlayerLevel);
	float MagicResistanceAmendment = AmendmentCurve->Eval(TargetPlayerLevel);

	// 
	//	捕获敌人的 抗暴 和 魔抗
	//  捕获是施法者的 暴击率 和 法强
	float MagicResistance = 0.f;
	float SpellDamagePenetration = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().MagicResistanceDef, EvaluateParameters, MagicResistance);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().SpellDamagePenetrationDef, EvaluateParameters, SpellDamagePenetration);

	// 暴击率  抗暴
	float CriticalHitRate = 0.f;
	float CriticalHitResistance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitRateDef, EvaluateParameters, CriticalHitRate);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitResistanceDef, EvaluateParameters, CriticalHitResistance);
	CriticalHitRate = FMath::Max(CriticalHitRate, 0.f);
	CriticalHitResistance = FMath::Max(CriticalHitResistance, 0.f);


	// 获取 context，并设置是否 暴击 或者 该次攻击是否被阻挡 eg：法术护盾 抵挡了一次技能
	
	FGameplayEffectContextHandle EffectContextHandle = EffectSpec.GetContext();
	// TODO: 未来可以在 Secondary Attributes 中添加一个 抵抗值， 用于抵抗敌人的技能
	UAuraAbilitySystemLibrary::SetBlockedHit( EffectContextHandle, false);
	
	

	// 开始计算	削减后的魔抗	=	魔抗 *=	（100 - 法穿) / 100
	// 最终造成的伤害	=	本可以打的伤害 *= (200 - 削减后的魔抗)/100
	// 若触发暴击，则（该伤害 * 2 ）* 抗暴
	float MagicResistanceTemp = (100 - SpellDamagePenetration * SpellDamagePenetrationAmendment) / 100;
	MagicResistance = MagicResistance *= (MagicResistanceTemp > 0 ? MagicResistanceTemp * MagicResistanceAmendment : 100.f);

	
	Damage = Damage *= ((100.f - MagicResistance) / 100.f);
	
	const bool bCriticalHit = FMath::RandRange(0, 100) <  CriticalHitRate * 100 ;
	UAuraAbilitySystemLibrary::SetCriticalHit( EffectContextHandle, bCriticalHit);
	if (bCriticalHit)
	{
		// 如果暴击率 大于 随机的暴击率	
		// 暴击了
		Damage *= 2;
		Damage *= (1 - CriticalHitResistance);
	}
	
	FGameplayModifierEvaluatedData EvaluatedData(UAuraAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
	
}
