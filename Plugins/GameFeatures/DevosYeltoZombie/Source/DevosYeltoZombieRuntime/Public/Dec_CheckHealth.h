// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "Dec_CheckHealth.generated.h"

/**
 * 
 */
UCLASS()
class DEVOSYELTOZOMBIERUNTIME_API UDec_CheckHealth : public UBTDecorator
{
	GENERATED_BODY()
	
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
public:
};
