// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/Classes/Components/PawnNoiseEmitterComponent.h"
#include "UnrealAICharacter.generated.h"

UCLASS(Blueprintable)
class AUnrealAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AUnrealAICharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	//FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

    /** Noise Emitter Component **/
    UPROPERTY(VisibleAnywhere, Category = AI)
    class UPawnNoiseEmitterComponent* PawnNoiseEmitter;

public:
	void SetCurrentPlayerVelocityOnXAxis(float Velocity);
	void SetCurrentPlayerVelocityOnYAxis(float Velocity);

	FORCEINLINE FVector GetCurrentPlayerVelocity() const { return CurrentPlayerVelocity; }

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Player Velocity. */
	FVector CurrentPlayerVelocity;
};
