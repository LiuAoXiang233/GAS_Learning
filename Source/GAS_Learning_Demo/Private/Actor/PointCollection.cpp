// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/PointCollection.h"

#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
APointCollection::APointCollection()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	Pt_0 = CreateDefaultSubobject<USceneComponent>("Pt_0");
	Pt_0->SetupAttachment(GetRootComponent());
	ImmutablePts.Add(Pt_0);

	Pt_1 = CreateDefaultSubobject<USceneComponent>("Pt_1");
	Pt_1->SetupAttachment(Pt_0);
	ImmutablePts.Add(Pt_1);

	Pt_2 = CreateDefaultSubobject<USceneComponent>("Pt_2");
	Pt_2->SetupAttachment(Pt_0);
	ImmutablePts.Add(Pt_2);

	Pt_3 = CreateDefaultSubobject<USceneComponent>("Pt_3");
	Pt_3->SetupAttachment(Pt_0);
	ImmutablePts.Add(Pt_3);

	Pt_4 = CreateDefaultSubobject<USceneComponent>("Pt_4");
	Pt_4->SetupAttachment(Pt_0);
	ImmutablePts.Add(Pt_4);

	Pt_5 = CreateDefaultSubobject<USceneComponent>("Pt_5");
	Pt_5->SetupAttachment(Pt_0);
	ImmutablePts.Add(Pt_5);

	Pt_6 = CreateDefaultSubobject<USceneComponent>("Pt_6");
	Pt_6->SetupAttachment(Pt_0);
	ImmutablePts.Add(Pt_6);

	Pt_7 = CreateDefaultSubobject<USceneComponent>("Pt_7");
	Pt_7->SetupAttachment(Pt_0);
	ImmutablePts.Add(Pt_7);

	Pt_8 = CreateDefaultSubobject<USceneComponent>("Pt_8");
	Pt_8->SetupAttachment(Pt_0);
	ImmutablePts.Add(Pt_8);


	Pt_9 = CreateDefaultSubobject<USceneComponent>("Pt_9");
	Pt_9->SetupAttachment(Pt_0);
	ImmutablePts.Add(Pt_9);

	Pt_10 = CreateDefaultSubobject<USceneComponent>("Pt_10");
	Pt_10->SetupAttachment(Pt_0);
	ImmutablePts.Add(Pt_10);


}

TArray<USceneComponent*> APointCollection::GetGroundPoints(const FVector& GroundLocation, int32 NumPoints, float YawOverride)
{
	checkf(NumPoints <= ImmutablePts.Num(), TEXT("NumPoints 不能比 11 大."));
	TArray<USceneComponent*> CopyArray;
	
	for (USceneComponent* Pt : ImmutablePts)
	{
		if (CopyArray.Num() >= NumPoints) return CopyArray;
		
		if (Pt != Pt_0)
		{
			FVector ToPoint = Pt->GetComponentLocation() - Pt_0->GetComponentLocation();
			ToPoint = ToPoint.RotateAngleAxis(YawOverride, FVector::UpVector);
			Pt->SetWorldLocation(Pt_0->GetComponentLocation() + ToPoint);
		}

		const FVector HigherLocation = FVector(Pt->GetComponentLocation().X, Pt->GetComponentLocation().Y, Pt->GetComponentLocation().Z + 500.f);
		const FVector LowerLocation = FVector(Pt->GetComponentLocation().X, Pt->GetComponentLocation().Y, Pt->GetComponentLocation().Z - 500.f);

		TArray<AActor*> IgnoreActors;
		UAuraAbilitySystemLibrary::GetLivePlayerWithinRadius(this, IgnoreActors, TArray<AActor*>(), 1500.f, GetActorLocation());

		FHitResult HitResult;
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActors(IgnoreActors);
		GetWorld()->LineTraceSingleByProfile(HitResult, HigherLocation, LowerLocation, FName("BlockAll"), QueryParams);

		FVector AdjuestLocation = FVector(Pt->GetComponentLocation().X, Pt->GetComponentLocation().Y, HitResult.ImpactPoint.Z);
		Pt->SetWorldLocation(AdjuestLocation);
		Pt->SetWorldRotation(UKismetMathLibrary::MakeRotFromZ(HitResult.ImpactNormal));

		CopyArray.Add(Pt);
	}
	return CopyArray;
}


void APointCollection::BeginPlay()
{
	Super::BeginPlay();
	
}

