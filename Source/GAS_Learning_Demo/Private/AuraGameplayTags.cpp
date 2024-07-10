// Fill out your copyright notice in the Description page of Project Settings.


#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

FAuraGameplayTags FAuraGameplayTags::GameplayTags;

void FAuraGameplayTags::InitialNativeGameplayTags()
{

	/*
	 *	Primary Attributes
	 * 
	 */
	
	
	GameplayTags.Attribute_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attribute.Primary.Strength"),
		FString("力量"));

	GameplayTags.Attribute_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attribute.Primary.Intelligence"),
		FString("智力"));

	GameplayTags.Attribute_Primary_Resilience = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attribute.Primary.Resilience"),
		FString("韧性，适应力"));

	GameplayTags.Attribute_Primary_Viger = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attribute.Primary.Viger"),
		FString("生命力"));

	
	/*
	 *	Secondary Attributes
	 * 
	 */
	
	GameplayTags.Attribute_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attribute.Secondary.Armor"),
		FString("护甲，降低收到的伤害，提高格挡几率。"));

	GameplayTags.Attribute_Secondary_PhysicalDamagePenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attribute.Secondary.PhysicalDamagePenetration"),
		FString("物理伤害穿透。"));

	GameplayTags.Attribute_Secondary_SpellDamagePenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attribute.Secondary.SpellDamagePenetration"),
		FString("法术伤害穿透。"));

	GameplayTags.Attribute_Secondary_MagicResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attribute.Secondary.MagicResistance"),
		FString("魔抗，降低收到的魔法伤害。"));

	GameplayTags.Attribute_Secondary_SpellStrength = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attribute.Secondary.SpellStrength"),
		FString("法术强度，增加法术攻击伤害。"));

	GameplayTags.Attribute_Secondary_AttackPower = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attribute.Secondary.AttackPower"),
		FString("物理攻击力，增加物理伤害。"));

	GameplayTags.Attribute_Secondary_MaxHP = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attribute.Secondary.MaxHP"),
		FString("最大生命值。"));

	GameplayTags.Attribute_Secondary_MaxMP = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attribute.Secondary.MaxMP"),
		FString("最大法力值。"));

	GameplayTags.Attribute_Secondary_Speed = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attribute.Secondary.Speed"),
		FString("速度，移动速度。"));

	/*
	 *
	 *	Input Tags
	 * 
	 */

	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.LMB"),
		FString("左键")
	);
	
	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.RMB"),
		FString("右键")
	);

	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.1"),
		FString("1键")
	);

	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.2"),
		FString("2键")
	);

	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.3"),
		FString("3键")
	);

	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.4"),
		FString("4键")
	);
	
}
