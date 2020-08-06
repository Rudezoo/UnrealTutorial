// Fill out your copyright notice in the Description page of Project Settings.


#include "Floater.h"

// Sets default values
AFloater::AFloater()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Staticmesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CustomStaticmesh"));

	Intial = FVector(0.0f);
	PlacedLocation = FVector(0.0f);
	WorldOrigin = FVector(0.0f,0.0f,0.0f);
	InitialDirection=FVector(0.0f, 0.0f, 0.0f);

	bflloaterLocation = false;
	bShouldFloat = false;

	Initialforce = FVector(200000.f, 0.0f, 0.0f);
	Initialtorque = FVector(200000.f, 0.0f, 0.0f);

	RunningTime = 0.f;

	A = 0;
	B = 0;
	C = 0;
	D = 0;
}

// Called when the game starts or when spawned
void AFloater::BeginPlay()
{
	Super::BeginPlay();

	float initialx = FMath::FRandRange(-500.f,500.f);
	float initialy = FMath::FRandRange(-500.f, 500.f);
	float initialz = FMath::FRandRange(0.f, 500.f);

	Intial.X = initialx;
	Intial.Y= initialy;
	Intial.Z = initialz;


	PlacedLocation = GetActorLocation();

	if (bflloaterLocation) {
		SetActorLocation(Intial);
	}
	
	basezlocation = PlacedLocation.Z;

	Staticmesh->AddForce(Initialforce);
	Staticmesh->AddTorque(Initialtorque);
	
	
}

// Called every frame
void AFloater::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bShouldFloat) {
		FVector newlocation= GetActorLocation();

		newlocation.Z = basezlocation + FMath::Sin(B*RunningTime - C)*A+D;

		SetActorLocation(newlocation);
		RunningTime += DeltaTime;

	}


	
}

