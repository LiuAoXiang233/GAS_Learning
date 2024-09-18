#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

class ULoadScreenSaveGame;
class UAuraAbilitySystemComponent;
/**
 * 
 */

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer& /* AssetTagContainer*/);
DECLARE_MULTICAST_DELEGATE(FAbilitiesGiven);
DECLARE_DELEGATE_OneParam(FForEachAbility, const FGameplayAbilitySpec&);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FAbilitiesStatusChanged, const FGameplayTag& /*Ability Tag*/, const FGameplayTag& /*Status Tag*/, int32 /*Ability Level*/);
DECLARE_MULTICAST_DELEGATE_FourParams(FAbilityEquip, const FGameplayTag& /*Ability Tag*/, const FGameplayTag& /*Status Tag*/, const FGameplayTag& /*Slot Tag*/, const FGameplayTag& /*PreSlot Tag*/);
DECLARE_MULTICAST_DELEGATE_OneParam(FDeActivePassiveAbility, const FGameplayTag& /*Ability Tag*/);
DECLARE_MULTICAST_DELEGATE_TwoParams(FActivatePassiveSpell, const FGameplayTag& /*Ability Tag*/, bool /*bActivate*/)


UCLASS()
class GAS_LEARNING_DEMO_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void AbilityActorInfoSet();
	void AddCharacterAbilitiesFromSaveData(ULoadScreenSaveGame* SaveData);
	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& Abilities);
	void AddCharacterPassiveAbilities(const TArray<TSubclassOf<UGameplayAbility>>& PassiveAbilities);
	void AbilityInputTagPressed(const FGameplayTag& GameplayTag);
	void AbilityInputTagHeld(const FGameplayTag& GameplayTag);
	void AbilityInputTagReleased(const FGameplayTag& GameplayTag);
	void ForEachAbility(const FForEachAbility& Delegate);
	
	static FGameplayTag GetGameplayTagFormAbilitySpec(const FGameplayAbilitySpec& GameplayAbilitySpec);
	static FGameplayTag GetInputTagFormAbilitySpec(const FGameplayAbilitySpec& GameplayAbilitySpec);
	static FGameplayTag GetStatusFromSpec(const FGameplayAbilitySpec& GameplayAbilitySpec);

	FGameplayTag GetStatusFromAbilityTag(const FGameplayTag& AbilityTag);
	FGameplayTag GetSlotFromAbilityTag(const FGameplayTag& AbilityTag);
	FGameplayAbilitySpec* GetAbilitySpecFromAbilityTag(const FGameplayTag& AbilityTag);
	bool SlotIsEmpty(const FGameplayTag& Slot);
	static bool AbilityHasSlot(const FGameplayAbilitySpec& AbilitySpec, const FGameplayTag& Slot);
	FGameplayAbilitySpec* GetAbilitySpecWithSlot(const FGameplayTag& Slot);
	bool IsPassiveAbilityOfAbiltiySpec(const FGameplayAbilitySpec& Spec) const;
	static bool SpecHasAnySlot(const FGameplayAbilitySpec& Spec);
	static void AssignSlotToAbility(FGameplayAbilitySpec& Spec, const FGameplayTag& Slot);

	void UpgradeAttribute(const FGameplayTag& GameplayTag);

	UFUNCTION(Server, Reliable)
	void ServerUpgradeAttribute(const FGameplayTag& GameplayTag);

	UFUNCTION(Server, Reliable)
	void ServerSpendSpellPoints(const FGameplayTag& GameplayTag);

	UFUNCTION(Server, Reliable)
	void ServerEquipAbility(const FGameplayTag& AbilityTag, const FGameplayTag& Slot);

	UFUNCTION(Client, Reliable)
	void ClientEquipAbility(const FGameplayTag& AbilityTag, const FGameplayTag& Status, const FGameplayTag& Slot, const FGameplayTag& PreSlot);
	
	FEffectAssetTags EffectAssetTags;
	FAbilitiesGiven AbilitiesGivenDelegate;
	FAbilitiesStatusChanged AbilitiesStatusChanged;
	FAbilityEquip AbilityEquip;
	FDeActivePassiveAbility DeActivePassiveAbility;
	FActivatePassiveSpell ActivatePassiveSpell;

	bool bStartUpAbilitiesGiven = false;

	void UpdateAbilityStatuses(int32 Level);

	bool GetDescriptionByAbilityTag(const FGameplayTag& AbilityTag, FString& Description, FString& NextLevelDescription);

	static void ClearSlot(FGameplayAbilitySpec* AbilitySpec);
	void ClearAbilitiesOfSlot(const FGameplayTag& Slot);
	static bool AbilityHasSlot(FGameplayAbilitySpec* AbilitySpec, const FGameplayTag& Slot);

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastActivatePassiveSpell(const FGameplayTag& AbilityTag, bool bActivate);

protected:
	UFUNCTION(Client, Reliable)
	void ClintEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);

	UFUNCTION(Client, Reliable)
	void ClintUpdateAbilitiesStatus(const FGameplayTag& AbilityTag, const FGameplayTag& StatusTag, int32 AbilityLevel);
	virtual void OnRep_ActivateAbilities() override;
};



