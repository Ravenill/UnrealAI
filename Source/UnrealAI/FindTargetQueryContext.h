// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "BasicAIController.h"
#include "FindTargetQueryContext.generated.h"

/**
 * 
 */
UCLASS()
class UNREALAI_API UFindTargetQueryContext : public UEnvQueryContext
{
    GENERATED_BODY()

private:
    void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;

    void AssignTarget(ABasicAIController* AIController, FEnvQueryContextData& ContextData) const;
};
