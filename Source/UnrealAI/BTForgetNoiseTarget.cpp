// Fill out your copyright notice in the Description page of Project Settings.

#include "BTForgetNoiseTarget.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTForgetNoiseTarget::ExecuteTask(UBehaviorTreeComponent& ComponentOwner, uint8* NodeMemory)
{
    if (UBlackboardComponent* Blackboard = Cast<UBlackboardComponent>(ComponentOwner.GetBlackboardComponent()))
    {
        Blackboard->ClearValue("NoiseGeneratedBy");
        Blackboard->ClearValue("NoiseLocation");

        return EBTNodeResult::Succeeded;
    }
    return EBTNodeResult::Failed;
}
