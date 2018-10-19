// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTForgetSeenTarget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALAI_API UBTForgetSeenTarget : public UBTTaskNode
{
	GENERATED_BODY()

private:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& ComponentOwner, uint8* NodeMemory) override;
};
