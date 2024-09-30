// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/InventoryActor/HealthPotion_CanTake_Actor.h"

FString AHealthPotion_CanTake_Actor::GetDescription()
{
	return FString::Printf(
			TEXT("\n<Title>小瓶恢复药水</>\n\n"
		"<Default>直接给使用者恢复少量体力  ：</>"
		"\n\n"
		"<Default>在远古的时代，巫师们收集巨人的血液经由神明的赐福酿造而成。"
		"恢复药水是一种常见的药水，冒险家的背包中可以没有武器，但唯独不能缺少药水。</>\n\n"
		
		));
		
}
