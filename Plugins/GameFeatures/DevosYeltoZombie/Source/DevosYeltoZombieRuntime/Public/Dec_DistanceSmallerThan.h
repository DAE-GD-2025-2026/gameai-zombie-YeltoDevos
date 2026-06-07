// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "Dec_DistanceSmallerThan.generated.h"

/**
 * 
 */
UCLASS()
class DEVOSYELTOZOMBIERUNTIME_API UDec_DistanceSmallerThan : public UBTDecorator
{
	GENERATED_BODY()
	
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
public:
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector ZombieKey;
	
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	float Distance{200.f};
};
