// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"
#include "PatrolPoint.h"
#include "GameFramework/Pawn.h"

ABasicAIController::ABasicAIController()
{
    BehaviorTree = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
    Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

    InitializeKeys();
}

void ABasicAIController::InitializeKeys()
{
    DetectedPawn = "DetectedPawn";
    DetectedPawnLocation = "DetectedPawnLocation";
    NoiseGeneratedBy = "NoiseGeneratedBy";
    PatrolPoint = "PatrolPoint";
    NoiseVolume = "NoiseVolume";
    NoiseLocation = "NoiseLocation";
    Status = "Status";
}

void ABasicAIController::InitializeAIBlackboard(ABasicAI* AI) const
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
        InitializeAIBlackboard(AI);
        LoadPatrolPointsToArray();
        StartBehaviorTree(AI);
    }
}

void ABasicAIController::SetDetectedPawn(APawn* Pawn)
{
    if (Blackboard)
    {
        Blackboard->SetValueAsObject(DetectedPawn, Pawn);
        Blackboard->SetValueAsVector(DetectedPawnLocation, Pawn->GetActorLocation());
    }
}

void ABasicAIController::SetNoiseDetails(APawn* Instigator, const FVector& Location, float Volume)
{
    if (Blackboard)
    {
        Blackboard->SetValueAsObject(NoiseGeneratedBy, Instigator);
        Blackboard->SetValueAsVector(NoiseLocation, Location);
        Blackboard->SetValueAsFloat(NoiseVolume, Volume);
    }
}

void ABasicAIController::SetAIStatus(EAIStatus& status)
{
    if (Blackboard)
    {
        Blackboard->SetValueAsEnum(Status, static_cast<uint8>(status));
    }
}

AActor* ABasicAIController::GetSeeingPawn()
{
    if (UObject* object = Blackboard->GetValueAsObject(DetectedPawn))
    {
        return Cast<AActor>(object);
    }
    return nullptr;
}