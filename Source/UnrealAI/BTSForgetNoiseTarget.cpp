// Fill out your copyright notice in the Description page of Project Settings.

#include "BTSForgetNoiseTarget.h"
#include "BehaviorTree/BlackboardComponent.h"

void UBTSForgetNoiseTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    if (UBlackboardComponent* Blackboard = Cast<UBlackboardComponent>(OwnerComp.GetBlackboardComponent()))
    {
        Blackboard->ClearValue("NoiseGeneratedBy");
        Blackboard->ClearValue("NoiseLocation");
    }

    ScheduleNextTick(NodeMemory);
}
