// Fill out your copyright notice in the Description page of Project Settings.

#include "BTBackToPatroling.h"
#include "BasicAI.h"
#include "BasicAIController.h"
#include "AIStatus.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTBackToPatroling::ExecuteTask(UBehaviorTreeComponent& ComponentOwner, uint8* NodeMemory)
{
    if (ABasicAI* AI = Cast<ABasicAI>(ComponentOwner.GetAIOwner()->GetPawn()))
    {
        AI->SetAIStatus(EAIStatus::STAT_PATROLING);
        return EBTNodeResult::Succeeded;
    }
    return EBTNodeResult::Failed;
}