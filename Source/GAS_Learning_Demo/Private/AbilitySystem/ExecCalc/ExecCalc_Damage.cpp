// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "AbilitySystemComponent.h"
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
	
	//	削减后的魔抗	=	魔抗 *=	（100 - 法穿) / 100
	// 最终造成的伤害	=	本可以打的伤害 *= (200 - 削减后的魔抗)/100
	float MagicResistance = 0.f;
	float SpellDamagePenetration = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().MagicResistanceDef, EvaluateParameters, MagicResistance);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().SpellDamagePenetrationDef, EvaluateParameters, SpellDamagePenetration);

	float MagicResistanceTemp = (100 - SpellDamagePenetration * SpellDamagePenetrationAmendment) / 100;
	MagicResistance = MagicResistance *= (MagicResistanceTemp > 0 ? MagicResistanceTemp * MagicResistanceAmendment : 100.f);

	Damage = Damage *= ((100.f - MagicResistance) / 100.f);

	
	
	FGameplayModifierEvaluatedData EvaluatedData(UAuraAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
