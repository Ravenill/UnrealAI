// Fill out your copyright notice in the Description page of Project Settings.

#include "BTForgetSeenTarget.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTForgetSeenTarget::ExecuteTask(UBehaviorTreeComponent& ComponentOwner, uint8* NodeMemory)
{
    if (UBlackboardComponent* Blackboard = Cast<UBlackboardComponent>(ComponentOwner.GetBlackboardComponent()))
    {
        Blackboard->ClearValue("DetectedPawn");
        Blackboard->ClearValue("DetectedPawnLocation");

        return EBTNodeResult::Succeeded;
    }
    return EBTNodeResult::Failed;
}
