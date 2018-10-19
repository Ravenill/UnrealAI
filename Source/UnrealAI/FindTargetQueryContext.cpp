// Fill out your copyright notice in the Description page of Project Settings.

#include "FindTargetQueryContext.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "UnrealAICharacter.h"
#include "BasicAI.h"

void UFindTargetQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
    Super::ProvideContext(QueryInstance, ContextData);

    ABasicAI* AI = Cast<ABasicAI>(QueryInstance.Owner.Get());
    ABasicAIController* AIController = Cast<ABasicAIController>(AI->GetController());

    AssignTarget(AIController, ContextData);
   
}

void UFindTargetQueryContext::AssignTarget(ABasicAIController* AIController, FEnvQueryContextData& ContextData) const
{
    if (AIController)
    {
        if (AActor* Target = AIController->GetSeeingPawn())
        {
            UEnvQueryItemType_Actor::SetContextHelper(ContextData, Target);
        }
    }
}
