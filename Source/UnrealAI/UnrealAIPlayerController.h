// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UnrealAIPlayerController.generated.h"

UCLASS()
class AUnrealAIPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AUnrealAIPlayerController();

protected:
	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** Input function for axis move */
	void ChangePlayerXVelocity(float AxisValue);
	void ChangePlayerYVelocity(float AxisValue);

	/** Navigate with axis */
	void MoveWithAxis();

	/** Navigate player to the current touch location. */
	void MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);
	
	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);
};
