// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * 
 */

struct FAuraGameplayTags
{
public:
	static FAuraGameplayTags Get() {return GameplayTags;}
	static void InitialNativeGameplayTags();


	/*
	 *	Secondary Attributes
	 *	
	 */
	FGameplayTag Attribute_Secondary_CriticalHitRate;
	FGameplayTag Attribute_Secondary_CriticalHitResistance;
	FGameplayTag Attribute_Secondary_Armor;
	FGameplayTag Attribute_Secondary_PhysicalDamagePenetration;
	FGameplayTag Attribute_Secondary_SpellDamagePenetration;
	FGameplayTag Attribute_Secondary_MagicResistance;
	FGameplayTag Attribute_Secondary_SpellStrength;
	FGameplayTag Attribute_Secondary_AttackPower;
	FGameplayTag Attribute_Secondary_MaxHP;
	FGameplayTag Attribute_Secondary_MaxMP;
	FGameplayTag Attribute_Secondary_Speed;

	/*
	 *
	 *	Primary Attributes
	 */
	FGameplayTag Attribute_Primary_Strength;
	FGameplayTag Attribute_Primary_Intelligence;
	FGameplayTag Attribute_Primary_Resilience;
	FGameplayTag Attribute_Primary_Viger;

	
	/*
	 *
	 *	Input Tags
	 * 
	 */
	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;


	/*
	 *	Other Tags
	 *
	 *	元素攻击	火 、 水 、 草 、 雷 、 冰 、 风 、 岩
	*	火 Fire

		水 Water

		冰 Cryo

		风 Anemo

		草 Dendro

		岩 Geo

		雷 Electro
	 *	物理攻击
	 */
	FGameplayTag Damage;
	FGameplayTag Damage_Fire;
	FGameplayTag Damage_Water;
	FGameplayTag Damage_Cryo;
	FGameplayTag Damage_Anemo;
	FGameplayTag Damage_Dendro;
	FGameplayTag Damage_Geo;
	FGameplayTag Damage_Electro;
	FGameplayTag Damage_Physical;

	FGameplayTag Damage_Resistance_Fire;
	FGameplayTag Damage_Resistance_Water;
	FGameplayTag Damage_Resistance_Cryo;
	FGameplayTag Damage_Resistance_Anemo;
	FGameplayTag Damage_Resistance_Dendro;
	FGameplayTag Damage_Resistance_Geo;
	FGameplayTag Damage_Resistance_Electro;
	FGameplayTag Damage_Resistance_Physical;



	FGameplayTag Abilities_Attack;

	TMap<FGameplayTag, FGameplayTag> DamageTypesToResistance;
	FGameplayTag Effect_HitReact;

	
private:
	static  FAuraGameplayTags GameplayTags;
};
