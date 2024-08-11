// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/AuraFireBolt.h"

#include "AuraGameplayTags.h"

FString UAuraFireBolt::GetDescription(int32 Level)
{
	const float Cost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = FMath::Abs(GetCooldown(Level));
	
	float ScaledDamage = GetDamageByDamageType(Level, FAuraGameplayTags::Get().Damage_Fire);
	
	if (Level == 1)
	{
		return FString::Printf(
			TEXT("<Title>火焰箭</>\n\n"
		"<Default>等级 ： </>"
		"<Level>%d</>\n"
		"<Default>消耗法力值: </>"
		"<Cost>%f</>\n"
		"<Default>冷却时间: </>"
		"<CoolDown>%f</>\n"
		"<Default>给敌人造成  ：</>"
		"<Damage>%f</>"
		"<Default>  伤害</>\n\n"
		"<Default>一支被赋予烈焰之力的箭矢。箭身燃烧着不熄的火焰，穿透空气时发出嘶嘶的灼烧声。"
		"传说，这种箭矢由曾经统治火焰的古代巫师所锻造。它不仅能撕裂敌人的肉体，还能点燃他们的灵魂，留下难以愈合的灼伤。</>\n\n"
		
		),
		Level, Cost, Cooldown, ScaledDamage);
	}
	else
	{
		// 给不同等级的火焰箭不同的介绍
		return FString::Printf(
			TEXT("<Title>火焰箭</>\n\n"
		"<Default>等级 ： </>"
		"<Level>%d</>\n"
		"<Default>消耗法力值: </>"
		"<Cost>%f</>\n"
		"<Default>冷却时间: </>"
		"<CoolDown>%f</>\n"
		"<Default>给敌人造成  ：</>"
		"<Damage>%f</>"
		"<Default>  伤害</>\n\n"
		"<Default>一支被赋予烈焰之力的箭矢。箭身燃烧着不熄的火焰，穿透空气时发出嘶嘶的灼烧声。"
		"传说，这种箭矢由曾经统治火焰的古代巫师所锻造。它不仅能撕裂敌人的肉体，还能点燃他们的灵魂，留下难以愈合的灼伤。</>\n\n"
		
		),
		Level, Cost, Cooldown, ScaledDamage);
	}
}

FString UAuraFireBolt::GetNextLevelDescription(int32 Level)
{
	const float Cost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = FMath::Abs(GetCooldown(Level));

	float ScaledDamage = GetDamageByDamageType(Level, FAuraGameplayTags::Get().Damage_Fire);
	
	if (Level > 5)
	{
		//最大等级是 5
		return FString::Printf(
		TEXT("<Title>火焰箭</>\n\n"
		"<Default>以达到最大等级</>")
		);
	}
	else
	{
		return FString::Printf(
			TEXT("<Title>火焰箭</>\n\n"
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
