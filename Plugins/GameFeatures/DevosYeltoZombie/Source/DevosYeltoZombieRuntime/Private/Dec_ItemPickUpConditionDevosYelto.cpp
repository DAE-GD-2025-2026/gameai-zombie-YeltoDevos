// Fill out your copyright notice in the Description page of Project Settings.


#include "Dec_ItemPickUpConditionDevosYelto.h"

bool UDec_ItemPickUpConditionDevosYelto::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	return ItemKey.IsSet();
}