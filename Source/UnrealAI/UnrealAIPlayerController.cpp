// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "UnrealAIPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "UnrealAICharacter.h"
#include "Engine/World.h"

AUnrealAIPlayerController::AUnrealAIPlayerController()
{
	bShowMouseCursor = false;
	DefaultMouseCursor = EMouseCursor::None;
}

void AUnrealAIPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	MoveWithAxis();
}

void AUnrealAIPlayerController::MoveWithAxis()
{
	if (AUnrealAICharacter* Pawn = Cast<AUnrealAICharacter>(GetPawn()))
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, Pawn->GetActorLocation() + Pawn->GetCurrentPlayerVelocity());
	}
}

void AUnrealAIPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	//WSAD movement
	InputComponent->BindAxis("MoveX", this, &AUnrealAIPlayerController::ChangePlayerXVelocity);
	InputComponent->BindAxis("MoveY", this, &AUnrealAIPlayerController::ChangePlayerYVelocity);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AUnrealAIPlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AUnrealAIPlayerController::MoveToTouchLocation);
}

void AUnrealAIPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void AUnrealAIPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > 120.0f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}
void AUnrealAIPlayerController::ChangePlayerXVelocity(float AxisValue)
{
	if (AUnrealAICharacter* MyPawn = Cast<AUnrealAICharacter>(GetPawn()))
	{
		const float Velocity = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
		MyPawn->SetCurrentPlayerVelocityOnXAxis(Velocity);
	}
}

void AUnrealAIPlayerController::ChangePlayerYVelocity(float AxisValue)
{
	if (AUnrealAICharacter* MyPawn = Cast<AUnrealAICharacter>(GetPawn()))
	{
		const float Velocity = FMath::Clamp(AxisValue, -1.0f, 1.0f) * 100.0f;
		MyPawn->SetCurrentPlayerVelocityOnYAxis(Velocity);
	}
}