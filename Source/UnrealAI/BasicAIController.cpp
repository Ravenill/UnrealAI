// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"
#include "PatrolPoint.h"

ABasicAIController::ABasicAIController()
{
    BehaviorTree = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
    Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

    initializeKeys();
}

void ABasicAIController::initializeKeys()
{
    DetectedPawn = "DetectedPawn";
    NoiseGenereatedBy = "NoiseGenereatedBy";
    PatrolPoint = "PatrolPoint";
    NoiseVolume = "NoiseVolume";
    NoiseLocation = "NoiseLocation";
}

void ABasicAIController::InitializeBlackboard(ABasicAI* AI) const
{
    if (UBlackboardData* BlackboardData = AI->BehaviorTree->BlackboardAsset)
    {
        Blackboard->InitializeBlackboard(*BlackboardData);
    }
}

void ABasicAIController::LoadPatrolPointsToArray()
{
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APatrolPoint::StaticClass(), PatrolPoints);
}

void ABasicAIController::StartBehaviorTree(ABasicAI* AI) const
{
    BehaviorTree->StartTree(*(AI->BehaviorTree));
}

void ABasicAIController::Possess(APawn * Pawn)
{
    Super::Possess(Pawn);

    if (ABasicAI* AI = Cast<ABasicAI>(Pawn))
    {
        InitializeBlackboard(AI);
        LoadPatrolPointsToArray();
        StartBehaviorTree(AI);
    }
}

void ABasicAIController::SetDetectedPawn(APawn* Pawn)
{
    if (Blackboard)
    {
        Blackboard->SetValueAsObject(DetectedPawn, Pawn);
    }
}

void ABasicAIController::SetNoiseDetails(APawn* Instigator, const FVector& Location, float Volume)
{
    if (Blackboard)
    {
        Blackboard->SetValueAsObject(NoiseGenereatedBy, Instigator);
        Blackboard->SetValueAsVector(NoiseVolume, Location);
        Blackboard->SetValueAsFloat(NoiseLocation, Volume);
    }
}