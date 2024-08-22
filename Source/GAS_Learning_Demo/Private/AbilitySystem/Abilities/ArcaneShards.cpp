// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ArcaneShards.h"

FString UArcaneShards::GetDescription(int32 Level)
{
	const float Cost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = FMath::Abs(GetCooldown(Level));
	
	float ScaledDamage = Damage.GetValueAtLevel(Level);
	
	if (Level == 1)
	{
		return FString::Printf(
			TEXT("<Title>奥数结晶</>\n\n"
		"<Default>等级 ： </>"
		"<Level>%d</>\n"
		"<Default>消耗法力值: </>"
		"<Cost>%f</>\n"
		"<Default>冷却时间: </>"
		"<CoolDown>%f</>\n"
		"<Default>给敌人造成  ：</>"
		"<Damage>%f</>"
		"<Default>  伤害</>\n\n"
		"<Default>这是被遗忘于时光尘埃中的结晶，是足以撼动现实与虚空界限的力量。"
		"奥数结晶最初出现在禁忌之人的梦境，是现实不可接受之物。。</>\n\n"
		
		),
		Level, Cost, Cooldown, ScaledDamage);
	}
	else
	{
		// 给不同等级的火焰箭不同的介绍
		return FString::Printf(
			TEXT("<Title>奥数结晶</>\n\n"
		"<Default>等级 ： </>"
		"<Level>%d</>\n"
		"<Default>消耗法力值: </>"
		"<Cost>%f</>\n"
		"<Default>冷却时间: </>"
		"<CoolDown>%f</>\n"
		"<Default>给敌人造成  ：</>"
		"<Damage>%f</>"
		"<Default>  伤害</>\n\n"
		"<Default>这是被遗忘于时光尘埃中的结晶，是足以撼动现实与虚空界限的力量。"
		"奥数结晶最初出现在禁忌之人的梦境，是现实不可接受之物。。</>\n\n"
		
		),
		Level, Cost, Cooldown, ScaledDamage);
	}
}

FString UArcaneShards::GetNextLevelDescription(int32 Level)
{
	const float Cost = FMath::Abs(GetManaCost(Level));
	const float Cooldown = FMath::Abs(GetCooldown(Level));

	float ScaledDamage = Damage.GetValueAtLevel(Level);
	
	if (Level > 5)
	{
		//最大等级是 5
		return FString::Printf(
		TEXT("<Title>奥数结晶</>\n\n"
		"<Default>以达到最大等级</>")
		);
	}
	else
	{
		return FString::Printf(
			TEXT("<Title>奥数结晶</>\n\n"
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
