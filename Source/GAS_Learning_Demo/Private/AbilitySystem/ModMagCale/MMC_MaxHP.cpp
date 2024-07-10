// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ModMagCale/MMC_MaxHP.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxHP::UMMC_MaxHP()
{
	VigerDef.AttributeToCapture = UAuraAttributeSet::GetVigerAttribute();
	VigerDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	VigerDef.bSnapshot = false;

	ResilienceDef.AttributeToCapture = UAuraAttributeSet::GetResilienceAttribute();
	ResilienceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	ResilienceDef.bSnapshot = false;
	
	// 捕获与计算有关的值
	RelevantAttributesToCapture.Add(VigerDef);
	RelevantAttributesToCapture.Add(ResilienceDef);
}

float UMMC_MaxHP::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// 获取来自 Source 和 Target 的Tags
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();


	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	float Viger = 0.f;
	float Resilience = 0.f;
	
	GetCapturedAttributeMagnitude(VigerDef, Spec, EvaluateParameters, Viger);
	GetCapturedAttributeMagnitude(ResilienceDef, Spec, EvaluateParameters, Resilience);

	Viger = FMath::Max<float>(Viger, 0.f);
	Resilience = FMath::Max<float>(Resilience, 0.f);

	ICombatInterface* CombatInterface =  Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetCharacterLevel();


	/*
	 *	最大生命值 = {（生命力 + 2） * 12 + 7} + 适应力 * 3  + 566 + 11 * Level
	 *
	 *	566 为 基础生命值
	 *	每级提高 11 点生命值
	 *	生命力/活力 Viger
	 *	适应力	  Resilience
	 *
	 *
	 *	Eg :	当生命力/活力 = 10
	 *			适应力		= 10
	 *			等级			= 1
	 *
	 *			此时最大生命值	=	566 + 11 * 1 + （（10 + 2） * 12 + 7） + 10 * 3
	 *							=	758
	 */
	
	return 566.f + 11.f * PlayerLevel + ( (Viger + 2.f) * 12.f + 7.f ) + Resilience * 3.f;
}
