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
	
	GameplayTags.Attribute_Secondary_CriticalHitRate = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attribute.Secondary.CriticalHitRate"),
		FString("暴击率。"));
	GameplayTags.Attribute_Secondary_CriticalHitResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attribute.Secondary.CriticalHitResistance"),
			FString("暴击抵抗。"));
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

	/*
	 *
	 *	Damage Types
	 */

	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage"),
		FString("伤害")
	);

	GameplayTags.Damage_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects.Damage.Fire"),
		FString("火焰伤害")
	);

	GameplayTags.Damage_Water = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects.Damage.Water"),
		FString("水属性伤害")
	);

	GameplayTags.Damage_Cryo = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects.Damage.Cryo"),
		FString("冰元素伤害")
	);

	GameplayTags.Damage_Anemo = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects.Damage.Anemo"),
		FString("风元素伤害")
	);

	GameplayTags.Damage_Dendro = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects.Damage.Dendro"),
		FString("草元素伤害")
	);

	GameplayTags.Damage_Geo = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects.Damage.Geo"),
		FString("岩元素伤害")
	);

	GameplayTags.Damage_Electro = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects.Damage.Electro"),
		FString("雷元素伤害")
	);

	GameplayTags.Damage_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects.Damage.Physical"),
		FString("物理伤害")
	);



	/*
	 *
	 *	元素伤害抗性
	 * 
	 */
	GameplayTags.Damage_Resistance_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects.Resistance.Fire"),
		FString("火抗")
	);
	
	GameplayTags.Damage_Resistance_Water = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects.Resistance.Water"),
		FString("水抗")
	);
	
	GameplayTags.Damage_Resistance_Cryo = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects.Resistance.Cryo"),
		FString("冰抗")
	);
	
	GameplayTags.Damage_Resistance_Anemo = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects.Resistance.Anemo"),
		FString("风抗")
	);
	
	GameplayTags.Damage_Resistance_Dendro = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects.Resistance.Dendro"),
		FString("草抗")
	);
	
	GameplayTags.Damage_Resistance_Geo = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects.Resistance.Geo"),
		FString("岩抗")
	);
	
	GameplayTags.Damage_Resistance_Electro = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects.Resistance.Electro"),
		FString("雷抗")
	);
	
	GameplayTags.Damage_Resistance_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects.Resistance.Physical"),
		FString("物抗")
	);


/*
 *	Map of Damage Types To Resistance
 * 
 */
	GameplayTags.DamageTypesToResistance.Add(GameplayTags.Damage_Fire, GameplayTags.Damage_Resistance_Fire);
	GameplayTags.DamageTypesToResistance.Add(GameplayTags.Damage_Cryo, GameplayTags.Damage_Resistance_Cryo);
	GameplayTags.DamageTypesToResistance.Add(GameplayTags.Damage_Water, GameplayTags.Damage_Resistance_Water);
	GameplayTags.DamageTypesToResistance.Add(GameplayTags.Damage_Anemo, GameplayTags.Damage_Resistance_Anemo);
	GameplayTags.DamageTypesToResistance.Add(GameplayTags.Damage_Geo, GameplayTags.Damage_Resistance_Geo);
	GameplayTags.DamageTypesToResistance.Add(GameplayTags.Damage_Dendro, GameplayTags.Damage_Resistance_Dendro);
	GameplayTags.DamageTypesToResistance.Add(GameplayTags.Damage_Electro, GameplayTags.Damage_Resistance_Electro);
	GameplayTags.DamageTypesToResistance.Add(GameplayTags.Damage_Physical, GameplayTags.Damage_Resistance_Physical);


	/*
	 *
	 *	Effects
	 */
	
	GameplayTags.Effect_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects.HitReact"),
		FString("受击时，赋予此tag")
	);

	GameplayTags.Abilities_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Attack"),
		FString("Attack Ability Tag")
	);
}
