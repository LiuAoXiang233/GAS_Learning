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
	 *	Meta Attributes
	 * 
	 */

	GameplayTags.Attribute_Meta_IncomingXP = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attribute.Meta.IncomingXP"),
		FString("Meta 属性 IncomingXP"));

	
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

	GameplayTags.InputTag_Passive_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.Passive.1"),
		FString("被动技能1")
	);

	GameplayTags.InputTag_Passive_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.Passive.2"),
		FString("被动技能2")
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

	


	/*
	 *	Montage Gameplay Tags
	 * 
	 */

	GameplayTags.Montage_Attack_Weapon = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.Weapon"),
		FString("使用武器的攻击动画")
	);
	GameplayTags.Montage_Attack_RightHand = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Montage.Attack.RightHand"),
			FString("使用右手徒手攻击动画")
		);
	GameplayTags.Montage_Attack_LeftHand = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Montage.Attack.LeftHand"),
		FString("使用左手徒手攻击动画")
	);


	/*
	 *	Ability Tags
	 * 
	 */

	GameplayTags.Abilities_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Attack"),
		FString("Attack Ability Tag")
	);

	GameplayTags.Abilities_None = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.None"),
		FString("None Ability")
	);

	/*
	 *	Offensive Ability Tag
	 */
	GameplayTags.Abilities_Fire_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Fire.FireBolt"),
		FString("火焰箭")
	);

	GameplayTags.CoolDown_Fire_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("CoolDown.Fire.FireBolt"),
			FString("火焰箭冷却")
		);

	GameplayTags.Abilities_Fire_FireBlast = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Fire.FireBlast"),
		FString("火焰炸弹")
	);

	GameplayTags.CoolDown_Fire_FireBlast = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("CoolDown.Fire.FireBlast"),
			FString("火焰炸弹冷却")
		);

	GameplayTags.Abilities_Electro_ElectroBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Electro.ElectroBolt"),
		FString("闪电箭")
	);

	GameplayTags.CoolDown_Electro_ElectroBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("CoolDown.Electro.ElectroBolt"),
			FString("闪电箭冷却")
		);

	GameplayTags.Abilities_Arcane_ArcaneSharders = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Arcane.ArcaneSharders"),
		FString("奥数法阵")
	);

	GameplayTags.CoolDown_Arcane_ArcaneSharders = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("CoolDown.Arcane.ArcaneSharders"),
			FString("奥数法阵冷却")
		);
	
	GameplayTags.Abilities_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.HitReact"),
		FString("受到攻击技能。")
	);

	/*
	 *	Ability Status
	 */
	GameplayTags.Abilities_Status_Eligible = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Status.Eligible"),
		FString("Eligible Status")
	);

	GameplayTags.Abilities_Status_Equipped = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Status.Equipped"),
		FString("Equipped Status")
	);

	GameplayTags.Abilities_Status_Locked = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Status.Locked"),
		FString("Locked Status")
	);

	GameplayTags.Abilities_Status_Unlocked = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Status.Unlocked"),
		FString("Unlocked Status")
	);

	/*
	 *	Ability Type
	 * 
	 */
	GameplayTags.Abilities_Type_Other = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Type.Other"),
		FString("Other Abilities type")
	);

	GameplayTags.Abilities_Type_Offensive = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Type.Offensive"),
		FString("Offensive Abilities type")
	);

	GameplayTags.Abilities_Type_Passive = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Abilities.Type.Passive"),
		FString("Passive Abilities type")
	);

	/*
	 *	Passive Abilities
	 * 
	 */
	GameplayTags.Abilities_Passive_LifeSiphon = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Abilities.Passive.LifeSiphon"),
			FString("Passive Abilitiy LifeSiphon")
		);
	GameplayTags.Abilities_Passive_ManaSiphon = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Abilities.Passive.ManaSiphon"),
			FString("Passive Abilitiy ManaSiphon")
		);
	GameplayTags.Abilities_Passive_HaloOfProtection = UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Abilities.Passive.HaloOfPretection"),
			FString("Passive Abilitiy HaloOfProtection")
		);
	/*
	 *	Debuff Tags
	 * 
	 */
	GameplayTags.Debuff_Burn = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Burn"),
		FString("燃烧效果，给敌人造成持续伤害"));

	GameplayTags.Debuff_Stun = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Stun"),
		FString("眩晕效果，敌人无法行动"));
	
	GameplayTags.Debuff_Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Damage"),
		FString("Debuff造成的伤害"));
	
	GameplayTags.Debuff_Duration = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Duration"),
		FString("Debuff的持续时间"));
	
	GameplayTags.Debuff_Frequence = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Frequence"),
		FString("Debuff的触发频率"));

	GameplayTags.Debuff_Chance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Debuff.Chance"),
		FString("Debuff的触发概率"));

	GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Damage_Fire, GameplayTags.Debuff_Burn);
	GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Damage_Electro, GameplayTags.Debuff_Stun);

	/*
	 *	Player Tags
	 * 
	 */
	GameplayTags.Player_Block_CurseTrace = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Player.Block.CurseTrace"),
		FString("阻挡Tag，鼠标追踪"));
	GameplayTags.Player_Block_InputHeld = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Player.Block.InputHeld"),
		FString("阻挡Tag，InputHeld"));
	GameplayTags.Player_Block_InputPressed = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Player.Block.InputPressed"),
		FString("阻挡Tag，InputPressed"));
	GameplayTags.Player_Block_InputRealsed = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Player.Block.InputReleased"),
		FString("阻挡Tag，InputReleased"));
}
