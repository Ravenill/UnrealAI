// Fill out your copyright notice in the Description page of Project Settings.

#include "BTSForgetSeenTarget.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTSForgetSeenTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    if (UBlackboardComponent* Blackboard = Cast<UBlackboardComponent>(OwnerComp.GetBlackboardComponent()))
    {
        Blackboard->ClearValue("DetectedPawn");
        Blackboard->ClearValue("DetectedPawnLocation");
    }

    ScheduleNextTick(NodeMemory);
}
