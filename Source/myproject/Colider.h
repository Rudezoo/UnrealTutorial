// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Colider.generated.h"

UCLASS()
class MYPROJECT_API AColider : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AColider();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class USpringArmComponent* springarm;

	UPROPERTY(VisibleAnywhere,Category="Mesh")
	class UStaticMeshComponent* meshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class USphereComponent* sphereComponent;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	class UColiderMovementComponent* OurMovementComponent;
 
	virtual UPawnMovementComponent* GetMovementComponent() const override;

	FORCEINLINE UStaticMeshComponent* getmeshComponent() { return meshComponent; }
	FORCEINLINE void setmeshComponent(UStaticMeshComponent* mesh) { meshComponent = mesh; }

	FORCEINLINE USphereComponent* getsphereComponent() { return sphereComponent; }
	FORCEINLINE void setsphereComponent(USphereComponent* sphere) { sphereComponent = sphere; }

	FORCEINLINE UCameraComponent* getcameraComponent() { return Camera; }
	FORCEINLINE void setcameraComponent(UCameraComponent* camera) { Camera = camera; }

	FORCEINLINE USpringArmComponent* getspringarmComponent() { return springarm; }
	FORCEINLINE void setspringarmComponent(USpringArmComponent* spring) { springarm = spring; }



private:
	void MoveForward(float input);
	void MoveRight(float input);

	void PitchCamera(float axisvalue);
	void YawCamera(float axisvalue);

	FVector2D CameraInput;
};
