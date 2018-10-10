// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicAI.h"
#include "BasicAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
ABasicAI::ABasicAI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    SetupSenses();
}

void ABasicAI::SetupSenses()
{
    PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
    PawnSensingComponent->SetPeripheralVisionAngle(95.0f);
}

// Called when the game starts or when spawned
void ABasicAI::BeginPlay()
{
	Super::BeginPlay();

    if (PawnSensingComponent)
    {
        PawnSensingComponent->OnSeePawn.AddDynamic(this, &ABasicAI::OnPawnDetected);
        PawnSensingComponent->OnHearNoise.AddDynamic(this, &ABasicAI::OnHearNoise);
    }
}

// Called every frame
void ABasicAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABasicAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABasicAI::OnPawnDetected(APawn* Pawn)
{
    if (ABasicAIController* AIController = Cast<ABasicAIController>(GetController()))
    {
        AIController->SetDetectedPawn(Pawn);
    }
}

void ABasicAI::OnHearNoise(APawn* Instigator, const FVector& Location, float Volume)
{
    if (ABasicAIController* AIController = Cast<ABasicAIController>(GetController()))
    {
        AIController->SetNoiseDetails(Instigator, Location, Volume);
    }
}
