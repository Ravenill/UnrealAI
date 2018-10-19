// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "PatrolPoint.h"
#include "BTSelectPatrolPoint.generated.h"

/**
 * 
 */
UCLASS()
class UNREALAI_API UBTSelectPatrolPoint : public UBTTaskNode
{
    GENERATED_BODY()

private:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& ComponentOwner, uint8* NodeMemory) override;

private:
    APatrolPoint * GetActualPatrolPoint(UBlackboardComponent* Blackboard) const;
    APatrolPoint* GetRandomPatrolPoint(TArray<AActor*>& AvaliblePoints, APatrolPoint* ActualPatrolPoint) const;
    void SetKey(UBlackboardComponent* Blackboard, APatrolPoint* NewPatrolPoint) const;   
};
