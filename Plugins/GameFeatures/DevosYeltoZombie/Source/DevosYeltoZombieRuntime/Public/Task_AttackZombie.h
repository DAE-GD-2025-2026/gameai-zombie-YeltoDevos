// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Task_AttackZombie.generated.h"

class UInventoryComponent;

/**
 * 
 */
UCLASS()
class DEVOSYELTOZOMBIERUNTIME_API UTask_AttackZombie : public UBTTaskNode
{
	GENERATED_BODY()
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	void CheckItemCanBeUsed(const int itemIdx, UInventoryComponent* inventory);
	
public:
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector ZombieKey;
};
