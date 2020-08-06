// Fill out your copyright notice in the Description page of Project Settings.


#include "ColiderMovementComponent.h"

void UColiderMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime,TickType,ThisTickFunction);

	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	FVector DesireMovementthisFrame = ConsumeInputVector().GetClampedToMaxSize(1.0f);

	if (!DesireMovementthisFrame.IsNearlyZero()) {
		FHitResult Hit;
		SafeMoveUpdatedComponent(DesireMovementthisFrame,UpdatedComponent->GetComponentRotation(),true,Hit);

		//if hit something
		if (Hit.IsValidBlockingHit()) {
			SlideAlongSurface(DesireMovementthisFrame, 1.f - Hit.Time, Hit.Normal, Hit);
			UE_LOG(LogTemp,Warning,TEXT("HIT"));
		}
	}
}
