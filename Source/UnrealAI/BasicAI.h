// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BasicAI.generated.h"

UCLASS()
class UNREALAI_API ABasicAI : public ACharacter
{
	GENERATED_BODY()

private:
    void SetupSenses();

    UFUNCTION()
    void OnPawnDetected(APawn* Pawn);

    UFUNCTION()
    void OnHearNoise(APawn* Pawn, const FVector& Location, float Volume);

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
	// Sets default values for this character's properties
	ABasicAI();

public:
    UPROPERTY(EditAnywhere, Category = AI)
    class UBehaviorTree* BehaviorTree;

    UPROPERTY(VisibleAnywhere, Category = AI)
    class UPawnSensingComponent* PawnSensingComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
