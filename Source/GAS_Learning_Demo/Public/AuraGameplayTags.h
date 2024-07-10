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

private:
	static  FAuraGameplayTags GameplayTags;
};
