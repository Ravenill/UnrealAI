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
    Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
    PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));

    PawnSensingComponent->SetPeripheralVisionAngle(95.0f);
    PawnSensingComponent->SightRadius = 1300.0f;
    PawnSensingComponent->LOSHearingThreshold = 850.0f;
    PawnSensingComponent->HearingThreshold = 650.0f;
    Sight->LoseSightRadius = 1500.0f;
}

// Called when the game starts or when spawned
void ABasicAI::BeginPlay()
{
	Super::BeginPlay();

    Status = EAIStatus::STAT_PATROLING;

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

void ABasicAI::SetAIStatus(EAIStatus status)
{
    Status = status;

    if (ABasicAIController* AIController = Cast<ABasicAIController>(GetController()))
    {
        AIController->SetAIStatus(Status);
    }
}

void ABasicAI::OnPawnDetected(APawn* Pawn)
{
    if (ABasicAIController* AIController = Cast<ABasicAIController>(GetController()))
    {
        AIController->SetDetectedPawn(Pawn);
        SetOnPawnDetectedAIStatus(Pawn);
    }
}

void ABasicAI::SetOnPawnDetectedAIStatus(APawn* Pawn)
{
    if (IsInAlarmedRange(GetActorLocation(), Pawn->GetActorLocation()))
    {
        SetAIStatus(EAIStatus::STAT_ALARMED);
    }
    else if (Status != EAIStatus::STAT_ALARMED)
    {
        SetAIStatus(EAIStatus::STAT_INVESTIGATING);
    }
}

bool ABasicAI::IsInAlarmedRange(const FVector &AIPosition, const FVector &PawnPosition) const
{
    const float ALARMED_RANGE = 320.0f;
    
    float distance = FVector::Distance(AIPosition, PawnPosition);
    if (distance < ALARMED_RANGE)
    {
        return true;
    }
    /*GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::FromInt(distance));*/
    return false;
}

void ABasicAI::OnHearNoise(APawn* Instigator, const FVector& Location, float Volume)
{
    if (ABasicAIController* AIController = Cast<ABasicAIController>(GetController()))
    {
        AIController->SetNoiseDetails(Instigator, Location, Volume);
        SetOnHearNoiseAIStatus();

        //GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("I hear you!"));
    }
}

void ABasicAI::SetOnHearNoiseAIStatus()
{
    if (Status == EAIStatus::STAT_PATROLING || Status == EAIStatus::STAT_INVESTIGATING)
    {
        SetAIStatus(EAIStatus::STAT_SUSPICIOUS);
    }
}