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
	/*
	 *	下面这个宏的意思是：
	 *	FGameplayEffectAttributeCaptureDefinition ArmorDef;

	 * 
	 */
	DECLARE_ATTRIBUTE_CAPTUREDEF(MagicResistance)				// 魔抗
	DECLARE_ATTRIBUTE_CAPTUREDEF(SpellDamagePenetration)		// 法穿
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitRate)				// 暴击率
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitResistance)			// 抗暴

	
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

}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();
 
	AActor* SourceActor = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	AActor* TargetActor = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	ICombatInterface* SourceCombatInterface = Cast<ICombatInterface>(SourceActor);
	ICombatInterface* TargetCombatInterface = Cast<ICombatInterface>(TargetActor);

	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();
	const FGameplayTagContainer* SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();
	
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	float Damage = EffectSpec.GetSetByCallerMagnitude(FAuraGameplayTags::Get().Damage);
	
	UCharacterClassInfo* CharacterClassInfo = UAuraAbilitySystemLibrary::GetCharacterClassInfo(SourceActor);

	
	/*
	 *	SpellDamagePenetrationAmendment	    法穿修正		来自 施法者 即	SourceActor
	 *	MagicResistanceAmendment			魔抗修正		针对	 受击者	即	TargetActor
	 */
	FRealCurve* AmendmentCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("SpellDamagePenetration"), FString());
	

	float SpellDamagePenetrationAmendment = AmendmentCurve->Eval(SourceCombatInterface->GetCharacterLevel());
	float MagicResistanceAmendment = AmendmentCurve->Eval(TargetCombatInterface->GetCharacterLevel());

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
