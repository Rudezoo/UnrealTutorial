// Fill out your copyright notice in the Description page of Project Settings.


#include "Colider.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "ColiderMovementComponent.h"

// Sets default values
AColider::AColider()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



	sphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SetRootComponent(sphereComponent);
	sphereComponent->SetupAttachment(GetRootComponent());
	sphereComponent->InitSphereRadius(40.f);
	sphereComponent->SetCollisionProfileName(TEXT("Pawn"));

	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	meshComponent->SetupAttachment(GetRootComponent());
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshComponentAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	if (MeshComponentAsset.Succeeded()) {
		meshComponent->SetStaticMesh(MeshComponentAsset.Object);
		meshComponent->SetRelativeLocation(FVector(0.f,0.f,-40.f));
		meshComponent->SetWorldScale3D(FVector(0.8f,0.8f,0.8f));
	}
	
	springarm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Springarm"));
	springarm->SetupAttachment(GetRootComponent());

	springarm->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
	springarm->TargetArmLength = 400.f;
	springarm->bEnableCameraLag = true;
	springarm->CameraLagSpeed = 3.0f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(springarm,USpringArmComponent::SocketName);

	OurMovementComponent = CreateDefaultSubobject<UColiderMovementComponent>(TEXT("OutMovementComponent"));
	OurMovementComponent->UpdatedComponent = RootComponent;

	CameraInput = FVector2D(0.f,0.f);
	
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AColider::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AColider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += CameraInput.X;
	
	SetActorRotation(NewRotation);

	FRotator newspringarmRotaion = springarm->GetComponentRotation();
	newspringarmRotaion.Pitch = FMath::Clamp(newspringarmRotaion.Pitch += CameraInput.Y, -80.f, -15.f);

	springarm->SetWorldRotation(newspringarmRotaion);

}

// Called to bind functionality to input
void AColider::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"),this,&AColider::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AColider::MoveRight);

	PlayerInputComponent->BindAxis(TEXT("CameraPitch"), this, &AColider::PitchCamera);
	PlayerInputComponent->BindAxis(TEXT("CameraYaw"), this, &AColider::YawCamera);

}


void AColider::MoveForward(float input) {
	FVector Forward = GetActorForwardVector();
	FVector Direction = FRotationMatrix(GetActorRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, input);
	//if (OurMovementComponent) {
	//	OurMovementComponent->AddInputVector(Forward* input); //our custom addmovement
	//}
	
}
void AColider::MoveRight(float input) {
	FVector Right = GetActorRightVector();
	FVector Direction = FRotationMatrix(GetActorRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, input);
	/*if (OurMovementComponent) {
		OurMovementComponent->AddInputVector(Right*input);
	}*/
}

void AColider::YawCamera(float axisvalue)
{
	CameraInput.X = axisvalue;
}

void AColider::PitchCamera(float axisvalue)
{
	CameraInput.Y = axisvalue;
}


UPawnMovementComponent* AColider::GetMovementComponent() const {
	return OurMovementComponent;
}