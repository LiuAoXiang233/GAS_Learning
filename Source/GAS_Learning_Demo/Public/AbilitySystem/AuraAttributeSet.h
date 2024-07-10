// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AuraAttributeSet.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()
	FEffectProperties(){}

	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;

	UPROPERTY()
	AController* SourceController = nullptr;

	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;

	UPROPERTY()
	AController* TargetController = nullptr;

	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
};


template<class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;

/**
 * 
 */
UCLASS()
class GAS_LEARNING_DEMO_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UAuraAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;


	//  FGameplayAttribute(*)()		 =====		TBaseStaticDelegateInstance<FGameplayAttribute(), FDefaultDelegateUserPolicy>::FFuncPtr
	TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagsToAttributes;
	
	/*
	 *	Primary.Attribute
	 *		-Strength		力量
	 *		-Intelligence	智力
	 *		-Resilience		韧性
	 *		-Viger			生命力
	 */

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "Primary Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Strength);


	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelligence, Category = "Primary Attributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Intelligence);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Resilience, Category = "Primary Attributes")
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resilience);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Viger, Category = "Primary Attributes")
	FGameplayAttributeData Viger;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Viger);

	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;

	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;

	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& OldResilence) const;

	UFUNCTION()
	void OnRep_Viger(const FGameplayAttributeData& OldViger) const;

	/*
	 *	Sceondary Attribute
	 *		-Physical Damage Penetration	物理伤害穿透			该值取决于 Resilience 和 Strength				适应力 * 1.2 + 力量 * 1.1 + 7
	 *		-Spell Damage Penetration		法术伤害穿透			该值取决于 Resilience 和 Intelligence			适应力 * 1 + 智力 * 3.2 + 3
	 *		-Armor							护甲					该值取决于 Resilience 和 Strength				适应力 * 4 + 力量 * 2.1 + 11
	 *		-Magic Resistance				魔抗					该值取决于 Resilience 和 Intelligence			适应力 * 3.5 + 智力 * 4.2 + 2
	 *		-Spell Strength					法强					该值取决于 Intelligence 和 Viger				{5 * （智力 + 1） + 2 } + 生命力 * 2.3 
	 *		-Attack Power					攻击力				该值取决于 Strength	和 Viger				{1.3 * （力量 + 5） + 7} + 生命力 * 0.7
	 *		-Max HP							最大生命值			该值取决于 Viger 和 Resilience				{（生命力 + 2） * 12 + 7} + 适应力 * 3 
	 *		-Max MP							最大法力值			该值取决于 Intelligence 和 Resilience			{（智力 + 1） * 5 + 3} + 适应力 * 1.5  
	 *		-Speed							移速					该值取决于 Viger 和 Resilience 和 Strength	生命力 * 20 + 适应力 * 30.5 + 力量 * 10 
	 */

	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PhysicalDamagePenetration, Category = "Secondary Attributes")
	FGameplayAttributeData PhysicalDamagePenetration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, PhysicalDamagePenetration);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_SpellDamagePenetration, Category = "Secondary Attributes")
	FGameplayAttributeData SpellDamagePenetration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, SpellDamagePenetration);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category = "Secondary Attributes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Armor);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MagicResistance, Category = "Secondary Attributes")
	FGameplayAttributeData MagicResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MagicResistance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_SpellStrength, Category = "Secondary Attributes")
	FGameplayAttributeData SpellStrength;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, SpellStrength);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AttackPower, Category = "Secondary Attributes")
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, AttackPower);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHP, Category = "Secondary Attributes")
	FGameplayAttributeData MaxHP;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHP);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMP, Category = "Secondary Attributes")
	FGameplayAttributeData MaxMP;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMP);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Speed, Category = "Secondary Attributes")
	FGameplayAttributeData Speed;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Speed);

	UFUNCTION()
	void OnRep_PhysicalDamagePenetration(const FGameplayAttributeData& OldPhysicalDamagePenetration) const;

	UFUNCTION()
	void OnRep_SpellDamagePenetration(const FGameplayAttributeData& OldSpellDamagePenetration) const;

	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;

	UFUNCTION()
	void OnRep_MagicResistance(const FGameplayAttributeData& OldMagicResistance) const;

	UFUNCTION()
	void OnRep_SpellStrength(const FGameplayAttributeData& OldSpellStrength) const;

	UFUNCTION()
	void OnRep_AttackPower(const FGameplayAttributeData& OldAttackPower) const;

	UFUNCTION()
	void OnRep_MaxHP(const FGameplayAttributeData& OldMaxHP) const;

	UFUNCTION()
	void OnRep_MaxMP(const FGameplayAttributeData& OldMaxMP) const;

	UFUNCTION()
	void OnRep_Speed(const FGameplayAttributeData& OldSpeed) const;
	
	
	/*
	 *	Vital.Attribute
	 *		-HP		跟 Viger 有关
	 *	
	 *		-MP		跟 Intelligence 有关
	 *	
	 */

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);
	
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana);
	

	
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;


	

private:

	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
	
};
