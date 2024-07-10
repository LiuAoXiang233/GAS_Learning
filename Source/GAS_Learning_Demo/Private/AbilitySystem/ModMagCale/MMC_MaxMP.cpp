// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ModMagCale/MMC_MaxMP.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxMP::UMMC_MaxMP()
{
	IntelligenceDef.AttributeToCapture = UAuraAttributeSet::GetIntelligenceAttribute();
	IntelligenceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	IntelligenceDef.bSnapshot = false;

	ResilienceDef.AttributeToCapture = UAuraAttributeSet::GetResilienceAttribute();
	ResilienceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	ResilienceDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(IntelligenceDef);
	RelevantAttributesToCapture.Add(ResilienceDef);
	
}

float UMMC_MaxMP::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	float Intelligence = 0.f;
	float Resilience = 0.f;

	Intelligence = FMath::Max<float>(Intelligence, 0.f);
	Resilience = FMath::Max<float>(Resilience, 0.f);
	
	GetCapturedAttributeMagnitude(IntelligenceDef, Spec, EvaluateParameters, Intelligence);
	GetCapturedAttributeMagnitude(IntelligenceDef, Spec, EvaluateParameters, Resilience);

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	float PlayerLevel = CombatInterface->GetCharacterLevel();

	/*
	 *	计算最大MP：{（智力 + 1） * 5 + 3} + 适应力 * 1.5 + 300 + 20 * Level 
	 *		Intelligence	： 智力
	 *		Resilience		: 适应力
	 *
	 *		Eg:		Intelligence = 10	Resilience = 10		Level = 1
	 *				((10 + 1) * 5 + 3) + 10 * 1.5 + 300 + 20 * 1
	 *
	 *				=	393
	 */
	return ((Intelligence + 1.f) * 5.f + 3.f) + Resilience * 1.5f + 300.f + 20.f * PlayerLevel;
}
