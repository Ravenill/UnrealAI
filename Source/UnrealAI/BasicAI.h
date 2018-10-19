// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIStatus.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h""
#include "BasicAI.generated.h"

UCLASS()
class UNREALAI_API ABasicAI : public ACharacter
{
	GENERATED_BODY()

private:
    EAIStatus Status;

private:
    void SetupSenses();

    UFUNCTION()
    void OnPawnDetected(APawn* Pawn);
    bool IsInAlarmedRange(const FVector &AIPosition, const FVector &PawnPosition) const;
    void SetOnPawnDetectedAIStatus(APawn* Pawn);

    UFUNCTION()
    void OnHearNoise(APawn* Pawn, const FVector& Location, float Volume);
    void SetOnHearNoiseAIStatus();

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
    UAISenseConfig_Sight* Sight;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void SetAIStatus(EAIStatus status);
};
