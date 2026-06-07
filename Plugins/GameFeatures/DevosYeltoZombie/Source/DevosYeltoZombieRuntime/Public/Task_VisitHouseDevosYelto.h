// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Village/House/House.h"
#include "Task_VisitHouseDevosYelto.generated.h"

/**
 * 
 */
UCLASS()
class DEVOSYELTOZOMBIERUNTIME_API UTask_VisitHouseDevosYelto : public UBTTaskNode
{
	GENERATED_BODY()
	
	std::vector<UObject*> VisitedHouses{};
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
public:
	
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector HouseKey;
	
};
