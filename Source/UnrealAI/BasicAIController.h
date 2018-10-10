// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BasicAI.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BasicAIController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALAI_API ABasicAIController : public AAIController
{
	GENERATED_BODY()

private:
	UBlackboardComponent* Blackboard;
	UBehaviorTreeComponent* BehaviorTree;

	TArray<AActor*> PatrolPoints;

    // Blackboard keys
    UPROPERTY(EditDefaultsOnly, Category = AI)
    FName DetectedPawn;

    UPROPERTY(EditDefaultsOnly, Category = AI)
    FName NoiseGenereatedBy;

    UPROPERTY(EditDefaultsOnly, Category = AI)
    FName PatrolPoint;

    UPROPERTY(EditDefaultsOnly, Category = AI)
    FName NoiseVolume;

    UPROPERTY(EditDefaultsOnly, Category = AI)
    FName NoiseLocation;

    void initializeKeys();

private:
    void InitializeBlackboard(ABasicAI* AI) const;
    void LoadPatrolPointsToArray();
    void StartBehaviorTree(ABasicAI* AI) const;

public:
    ABasicAIController();

public:
	FORCEINLINE UBlackboardComponent* GetBlackboard() const { return Blackboard; }
	FORCEINLINE UBehaviorTreeComponent* GetBehaviorTree() const{ return BehaviorTree; }
    FORCEINLINE TArray<AActor*> GetPatrolPoints() const { return PatrolPoints; }
	
	virtual void Possess(APawn* Pawn) override;

    void SetDetectedPawn(APawn* Pawn);
    void SetNoiseDetails(APawn* Instigator, const FVector& Location, float Volume);
};
