// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTSForgetSeenTarget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALAI_API UBTSForgetSeenTarget : public UBTService
{
	GENERATED_BODY()

private:
    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
