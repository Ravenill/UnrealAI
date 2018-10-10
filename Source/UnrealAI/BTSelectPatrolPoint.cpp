// Fill out your copyright notice in the Description page of Project Settings.

#include "BTSelectPatrolPoint.h"
#include "BasicAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTSelectPatrolPoint::ExecuteTask(UBehaviorTreeComponent & ComponentOwner, uint8 * NodeMemory)
{
    if (ABasicAIController* AIController = Cast<ABasicAIController>(ComponentOwner.GetAIOwner()))
    {
        if (UBlackboardComponent* Blackboard = Cast<UBlackboardComponent>(ComponentOwner.GetBlackboardComponent()))
        {
            TArray<AActor*> AvaliblePoints = AIController->GetPatrolPoints();
            APatrolPoint* ActualPatrolPoint = GetActualPatrolPoint(Blackboard);
            APatrolPoint* NextPatrolPoint = GetRandomPatrolPoint(AvaliblePoints, ActualPatrolPoint);
            SetKey(Blackboard, NextPatrolPoint);

            return EBTNodeResult::Succeeded;
        }
    }

    return EBTNodeResult::Failed;
}

APatrolPoint * UBTSelectPatrolPoint::GetActualPatrolPoint(UBlackboardComponent* Blackboard) const
{
    return Cast<APatrolPoint>(Blackboard->GetValueAsObject("PatrolPoint"));
}

APatrolPoint* UBTSelectPatrolPoint::GetRandomPatrolPoint(TArray<AActor*>& AvaliblePoints, APatrolPoint* ActualPatrolPoint) const
{
    int RandomIterator = FMath::RandRange(0, AvaliblePoints.Num() - 1);
    APatrolPoint* PatrolPoint = Cast<APatrolPoint>(AvaliblePoints[RandomIterator]);

    if (PatrolPoint == ActualPatrolPoint)
    {
        return GetRandomPatrolPoint(AvaliblePoints, ActualPatrolPoint);
    }
    else
    {
        return PatrolPoint;
    }
}

void UBTSelectPatrolPoint::SetKey(UBlackboardComponent* Blackboard, APatrolPoint* NewPatrolPoint) const
{
    Blackboard->SetValueAsObject("PatrolPoint", NewPatrolPoint);
}
