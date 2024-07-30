// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyCharacter.h"

#include "AuraGameplayTags.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AI/AuraAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GAS_Learning_Demo/GAS_Learning_Demo.h"
#include "UI/Widget/AuraUserWidget.h"


AEnemyCharacter::AEnemyCharacter()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	
	AbilitySystemComponent = CreateDefaultSubobject<UAuraAbilitySystemComponent>("AbilitySystem");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	AttributeSet = CreateDefaultSubobject<UAuraAttributeSet>("AttributeSet");
	
	ProgressBar = CreateDefaultSubobject<UWidgetComponent>("HP Bar");
	ProgressBar->SetupAttachment(GetRootComponent());
	
}

void AEnemyCharacter::HitReactTagChanged(const FGameplayTag Tag, int32 NewCount)
{
	bHitRecating = NewCount > 0;

	GetCharacterMovement()->MaxWalkSpeed = bHitRecating ? 0.f : BaseWalkSpeed;

	if (AIController && AIController->GetBlackboardComponent())
	{
		AIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), bHitRecating);
	}
	

}


void AEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!HasAuthority()) return;
	
	AIController = Cast<AAuraAIController>(NewController);
	AIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->GetBlackboardAsset());
	AIController->RunBehaviorTree(BehaviorTree);

	AIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), false);
	AIController->GetBlackboardComponent()->SetValueAsBool(FName("RangedAttacker"), CharacterClass != ECharacterClass::Warrior);

}

void AEnemyCharacter::HighLightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AEnemyCharacter::UnHighLightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

void AEnemyCharacter::SetCombatTarget_Implementation(AActor* InTarget)
{
	CombatTarget = InTarget;
}

AActor* AEnemyCharacter::GetCombatTarget_Implementation() const
{
	return CombatTarget;
}


int32 AEnemyCharacter::GetCharacterLevel()
{
	return Level;
}

void AEnemyCharacter::Die()
{
	SetLifeSpan(LifeSpan);
	Super::Die();
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;

	if (HasAuthority())
	{
		UAuraAbilitySystemLibrary::GiveStartUpAbilities(this, AbilitySystemComponent, CharacterClass);
	}
	
	InitAbilityActorInfo();
	

	if (UAuraUserWidget* UserWidget = Cast<UAuraUserWidget>(ProgressBar->GetUserWidgetObject()))
	{
		UserWidget->SetWidgetController(this);
	}
	
	if (const UAuraAttributeSet* AS = Cast<UAuraAttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetHealthAttribute()).AddLambda(
		[this] (const FOnAttributeChangeData& Data)
		{
			OnEnemyHealthChanged.Broadcast(Data.NewValue);
		}
		);

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetMaxHPAttribute()).AddLambda(
			[this] (const FOnAttributeChangeData& Data)
			{
				OnEnemyMaxHealthChanged.Broadcast(Data.NewValue);
			}
		);

		AbilitySystemComponent->RegisterGameplayTagEvent(FAuraGameplayTags::Get().Effect_HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(
			this,
			&AEnemyCharacter::HitReactTagChanged
		);

		OnEnemyHealthChanged.Broadcast(AS->GetHealth());
		OnEnemyMaxHealthChanged.Broadcast(AS->GetMaxHP());
	}

	
	
}

void AEnemyCharacter::InitAbilityActorInfo()
{
	
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	if (HasAuthority())
	{
		InitializeDefaultAttributes();
	}
	

	
}

void AEnemyCharacter::InitializeDefaultAttributes() const
{
	UAuraAbilitySystemLibrary::InitializeDefaultAttributes(this, CharacterClass, Level, AbilitySystemComponent);
}
