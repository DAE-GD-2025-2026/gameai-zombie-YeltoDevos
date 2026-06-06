// Fill out your copyright notice in the Description page of Project Settings.


#include "Dec_ItemPickUpCondition.h"

bool UDec_ItemPickUpCondition::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	return ItemKey.IsSet();
}