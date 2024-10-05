// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AuraCharacter.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/LevelUpInfo.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Game/AuraGameModeBase.h"
#include "GameFramework/GameSession.h"
#include "GameFramework/SpringArmComponent.h"
#include "Inventory/InventoryComponent.h"
#include "Inventory/UItem.h"
#include "Kismet/GameplayStatics.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

AAuraCharacter::AAuraCharacter()
{

	// 创建弹簧臂组件
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(RootComponent, FName("SpringArm"));

	// 创建摄像机
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm, FName("Camera"));

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>("Inventory");
	
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// 不在控制器旋转时旋转。使其仅影响摄像机。
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void AAuraCharacter::LoadInventoryAsync()
{
	if (AAuraGameModeBase* GameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(this)))
	{
		if (ULoadScreenSaveGame* SaveGame = Cast<ULoadScreenSaveGame>(GameMode->RetrieveInGameSaveData()))
		{
			TArray<UUItem*> Items;
			for (const FItemDataToSaveAndLoad& SavedItem : SaveGame->SavedItems)
			{
				UUItem* Item = NewObject<UUItem>();

				Item->Name = SavedItem.Name;
				Item->Quantity = SavedItem.Quantity;
				Item->ItemID = SavedItem.ItemID;
				Item->Description = SavedItem.Description;
				Item->MaxStackSize = 64;	

				Items.Add(Item);
			}

			InventoryComponent->Inventory->ReplaceItems(Items);
		}
	}
}

void AAuraCharacter::LoadInventory()
{
	if (!IsValid(InventoryComponent))
	{
		InventoryComponent = NewObject<UInventoryComponent>(this, UInventoryComponent::StaticClass());
		InventoryComponent->RegisterComponent();
	}
	
	FTimerHandle LoadInventoryTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(LoadInventoryTimerHandle, this, &AAuraCharacter::LoadInventoryAsync, 0.1f, false);
	
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// for service
	InitAbilityActorInfo();

	LoadProgress();

	LoadInventory();
	
	// 
	if (AAuraGameModeBase* GameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(this)))
	{
		GameMode->LoadWorldState(GetWorld());
	}

	
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// for client
	InitAbilityActorInfo();
}

void AAuraCharacter::LoadProgress()
{
	if (AAuraGameModeBase* GameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(this)))
	{
		ULoadScreenSaveGame* SaveGame = GameMode->RetrieveInGameSaveData();
		if (SaveGame == nullptr) return;
		
		if (AAuraPlayerState* AuraPlayerState = Cast<AAuraPlayerState>(GetPlayerState()))
		{
			AuraPlayerState->SetLevel(SaveGame->PlayerInformation.PlayerLevel);
			AuraPlayerState->SetXP(SaveGame->PlayerInformation.PlayerXP);
			AuraPlayerState->SetAttributePoints(SaveGame->PlayerInformation.AttributePoints);
			AuraPlayerState->SetSpellPoints(SaveGame->PlayerInformation.SpellPoints);
		}

		// 应用PrimaryAttribute GE 都是从SaveGameData中获取
		UAuraAbilitySystemLibrary::InitializeDefaultAttributes_SetByCaller(this, AbilitySystemComponent, SaveGame);


		// TODO: 设置玩家的所在的地图和位置
		SetActorTransform(SaveGame->PlayerInformation.PlayerTransform);


		// TODO: 给角色赋予技能, 如果是第一次，存档里并没有保存技能， 应该直接赋予初始技能， 如果是保存后，应该从存档中导入角色技能
		if (SaveGame->bIsFirstSave)
		{
			// 第一次
			GiveChararcterAbilities();
		}
		else
		{
			// 从存档中导入
			if (UAuraAbilitySystemComponent* AuraASC = Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent))
			{	
				AuraASC->AddCharacterAbilitiesFromSaveData(SaveGame);	
			}
		}
		
	}
}

AInventory* AAuraCharacter::GetInventory() const
{
	return InventoryComponent->Inventory;
}

void AAuraCharacter::AddToXP_Implementation(int32 InXP)
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);

	AuraPlayerState->AddToXP(InXP);
}

void AAuraCharacter::LevelUp_Implementation()
{
	// TODO: 添加升级后的 cue 之类的东西
	IPlayerInterface::LevelUp_Implementation();
}

int32 AAuraCharacter::GetXP_Implementation() const
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	return AuraPlayerState->GetPlayerXP();
}

int32 AAuraCharacter::FindLevelForXP_Implementation(int32 InXP) const
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	return AuraPlayerState->LevelUpInfo->FindLevelForXP(InXP);
}

int32 AAuraCharacter::GetRewardAttributePoints_Implementation(int32 Level) const
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	return AuraPlayerState->LevelUpInfo->LevelUpInfomation[Level].AttributePointAward;
}

int32 AAuraCharacter::GetRewardSpellPoints_Implementation(int32 Level) const
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	return AuraPlayerState->LevelUpInfo->LevelUpInfomation[Level].SpellPointAward;
}

void AAuraCharacter::AddToAttributePoints_Implementation(int32 InAttributePoints)
{
	// TODO: 添加属性点
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	AuraPlayerState->AddToAttributePoints(InAttributePoints);
}

void AAuraCharacter::AddToPlayerLevel_Implementation(int32 InPlayerLevels)
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	AuraPlayerState->AddToLevel(InPlayerLevels);

	if (UAuraAbilitySystemComponent* AuraASC = Cast<UAuraAbilitySystemComponent>(GetAbilitySystemComponent()))
	{
		AuraASC->UpdateAbilityStatuses(AuraPlayerState->GetPlayerLevel());;
	}
}

void AAuraCharacter::AddToSpellPoints_Implementation(int32 InSpellPoints)
{
	// TODO: 添加技能点
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	AuraPlayerState->AddToSpellPoints(InSpellPoints);
}

int32 AAuraCharacter::GetAttributePoints_Implementation()
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	return AuraPlayerState->GetAttributePoints();
}

int32 AAuraCharacter::GetSpellPoints_Implementation()
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	return AuraPlayerState->GetSpellPoints();
}

void AAuraCharacter::ShowMagicCircle_Implementation(UMaterialInstance* DecalMaterial)
{
	if (AAuraPlayerController* PlayerController = Cast<AAuraPlayerController>(GetController()))
	{
		PlayerController->ShowMagicCircle(DecalMaterial);
		PlayerController->bShowMouseCursor = false;
	}
	
}

void AAuraCharacter::HideMagicCircle_Implementation()
{
	if (AAuraPlayerController* PlayerController = Cast<AAuraPlayerController>(GetController()))
	{
		PlayerController->HideMagicCircle();
		PlayerController->bShowMouseCursor = true;
	}
}

int32 AAuraCharacter::GetCharacterLevel_Implementation()
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	return AuraPlayerState->GetPlayerLevel();
}

void AAuraCharacter::SaveProgress_Implementation()
{
	if (AAuraGameModeBase* GameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(this)))
	{
		ULoadScreenSaveGame* SaveGame = GameMode->RetrieveInGameSaveData();
		if (SaveGame == nullptr) return;

		// 保存游戏中的信息
		SaveGame->PlayerInformation.PlayerTransform = GetTransform();
		SaveGame->MapName = UGameplayStatics::GetCurrentLevelName(GetWorld());

		if (AAuraPlayerState* AuraPlayerState = Cast<AAuraPlayerState>(GetPlayerState()))
		{
			SaveGame->PlayerInformation.AttributePoints = AuraPlayerState->GetAttributePoints();
			SaveGame->PlayerInformation.PlayerLevel = AuraPlayerState->GetPlayerLevel();
			SaveGame->PlayerInformation.SpellPoints = AuraPlayerState->GetSpellPoints();
			SaveGame->PlayerInformation.PlayerXP = AuraPlayerState->GetPlayerXP();
		}

		if (UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(GetAttributeSet()) )
		{
			SaveGame->PlayerInformation.Strength = AuraAttributeSet->GetStrength();
			SaveGame->PlayerInformation.Intelligence = AuraAttributeSet->GetIntelligence();
			SaveGame->PlayerInformation.Resilience = AuraAttributeSet->GetResilience();
			SaveGame->PlayerInformation.Viger = AuraAttributeSet->GetViger();
		}

		// 保存玩家背包中的物品
		SaveGame->SavedItems.Empty();
		for (UUItem* Item : GetInventory()->Items)
		{
			FItemDataToSaveAndLoad SavedItem;
			SavedItem.Name = Item->Name;
			SavedItem.Quantity = Item->Quantity;
			SavedItem.ItemID = Item->ItemID;
			SavedItem.Description = Item->Description;
			
			SaveGame->SavedItems.Add(SavedItem);
			
		}
		
		// 保存玩家的技能
		if (!HasAuthority()) return;

		UAuraAbilitySystemComponent* AuraASC = Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent);
		FForEachAbility SaveAbilityDelegate;
		SaveGame->SaveAbility.Empty();
		SaveAbilityDelegate.BindLambda([this, AuraASC, SaveGame] (const FGameplayAbilitySpec& AbilitySpec)
		{
			const FGameplayTag AbilityTag = AuraASC->GetGameplayTagFormAbilitySpec(AbilitySpec);
			UAbilityInfo* AbilityInfo = UAuraAbilitySystemLibrary::GetAbilityInfo(this);
			FAuraAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AbilityTag);
			
			FSaveAbilities SaveAbilities;
			SaveAbilities.GameplayAbility = Info.Ability;
			SaveAbilities.AbilityLevel = AbilitySpec.Level;
			SaveAbilities.AbilitySlot = AuraASC->GetSlotFromAbilityTag(AbilityTag);
			SaveAbilities.AbilityStatus = AuraASC->GetStatusFromAbilityTag(AbilityTag);
			SaveAbilities.AbilityTag = AbilityTag;
			SaveAbilities.AbilityType = Info.AbilityType;

			SaveGame->SaveAbility.AddUnique(SaveAbilities);
		});
		AuraASC->ForEachAbility(SaveAbilityDelegate);

		SaveGame->bIsFirstSave = false;
		
		GameMode->SaveInGameSaveData(SaveGame);

		GameMode->SaveWorldState(GetWorld());
	}
}



void AAuraCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	
	
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	Cast<UAuraAbilitySystemComponent>(AuraPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();

	// 在ASC设置好后，绑定Debuff事件
	BindEventOnDebuffTagChanged();
	
	AttributeSet = AuraPlayerState->GetAttributeSet();

	OnAscRegistered.Broadcast(AbilitySystemComponent);
	// 在多人游戏中，该AuraPlayerController可以为null
	if(AAuraPlayerController* AuraPlayerController = Cast<AAuraPlayerController> (GetController()))
	{
		if(AAuraHUD* AuraHUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD()))
		{
			AuraHUD->InitOverlay(AuraPlayerController, AuraPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState, this);

	
}
