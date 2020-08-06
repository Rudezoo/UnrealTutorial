// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Floater.generated.h"

UCLASS()
class MYPROJECT_API AFloater : public AActor
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:

	float RunningTime;
	float basezlocation;

	//Amplitude - how mush we iccilate up and down
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly,Category="FloaterVariable")
	float A;

	//Period - 2* PI/Abs(B)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FloaterVariable")
	float B;

	// Phase Shift - C/B
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FloaterVariable")
	float C;

	//Vertucal Shift
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FloaterVariable")
	float D;

public:	
	// Called every frame
	AFloater();


	UPROPERTY(VisibleAnyWhere,BlueprintReadWrite, Category = "MymeshComponent")
	UStaticMeshComponent* Staticmesh;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "FloaterVariable")
	FVector Intial ;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "FloaterVariable")
	FVector PlacedLocation;

	UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly, Category="FloaterVariable")
	FVector WorldOrigin;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "FloaterVariable")
	FVector InitialDirection;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FloaterVariable")
	bool bShouldFloat;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="FloaterVariable")
	bool bflloaterLocation;

	UPROPERTY(BlueprintReadWrite,EditInstanceOnly, Category = "FloaterVariable")
	FVector Initialforce;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "FloaterVariable")
	FVector Initialtorque;

	virtual void Tick(float DeltaTime) override;

};
