// Fill out your copyright notice in the Description page of Project Settings.


#include "Dec_CheckHealth.h"

#include "AIController.h"
#include "Survivor/SurvivorPawn.h"
#include "Common/HealthComponent.h"

bool UDec_CheckHealth::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	ASurvivorPawn* survivor = Cast<ASurvivorPawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (!survivor) return false;
	
	UHealthComponent* healthComp = Cast<UHealthComponent>(survivor->GetComponentByClass(UHealthComponent::StaticClass()));
	if (!healthComp) return false;
	
	float healthpercent{ static_cast<float>(healthComp->GetHealth()) / static_cast<float>(healthComp->GetMaxHealth()) };
	
	if (healthpercent <= 0.5)
	{
		GEngine->AddOnScreenDebugMessage(5, 2.f, FColor::Red, 
			FString::Printf(TEXT("Health under threshold")));
		return true;
	}
	
	
	return false;
}