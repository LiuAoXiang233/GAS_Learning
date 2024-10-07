// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/CanTakeActor.h"

#include "Character/AuraCharacter.h"
#include "Inventory/Inventory.h"
#include "Inventory/UItem.h"

// Sets default values
ACanTakeActor::ACanTakeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Item = CreateDefaultSubobject<UUItem>(TEXT("Item"));


}

void ACanTakeActor::OnOverlap(AActor* TargetActor)
{
	if (AAuraCharacter* AuraCharacter = Cast<AAuraCharacter>(TargetActor))
	{
		AuraCharacter->GetInventory()->AddItem(Item);

		
		Destroy();
	}
}

FString ACanTakeActor::GetDescription()
{
	return FString("");
}


// Called when the game starts or when spawned
void ACanTakeActor::BeginPlay()
{
	Super::BeginPlay();

	if (!Item)
	{
		Item = NewObject<UUItem>();

	}
	Description = GetDescription();
	Item->ItemInfo.Description = GetDescription();
	Item->Quantity = Quantity;
	Item->ItemInfo.Name = Name;
	Item->ItemInfo.ItemID = ItemID;
	Item->ItemInfo.MaxStackSize = MaxStackSize;
}

// Called every frame
void ACanTakeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

