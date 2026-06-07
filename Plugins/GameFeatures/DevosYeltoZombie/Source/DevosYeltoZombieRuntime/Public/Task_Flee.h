// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Task_Flee.generated.h"

/**
 * 
 */
UCLASS()
class DEVOSYELTOZOMBIERUNTIME_API UTask_Flee : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float radius;
	
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector FleeTarget;
	
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	float FleeDistance{500.f};
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
