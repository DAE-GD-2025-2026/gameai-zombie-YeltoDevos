// Fill out your copyright notice in the Description page of Project Settings.


#include "Dec_CheckEnergyDevosYelto.h"
#include "AIController.h"
#include "Survivor/SurvivorPawn.h"
#include "Common/StaminaComponent.h"

bool UDec_CheckEnergyDevosYelto::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	ASurvivorPawn* survivor = Cast<ASurvivorPawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (!survivor) return false;
	
	UStaminaComponent* staminaComp = Cast<UStaminaComponent>(survivor->GetComponentByClass(UStaminaComponent::StaticClass()));
	if (!staminaComp) return false;
	
	float staminapercent{ (staminaComp->GetCurrentStamina()) / (staminaComp->GetMaxStamina()) };
	
	if (staminapercent <= 0.3)
	{
		GEngine->AddOnScreenDebugMessage(5, 2.f, FColor::Red, 
			FString::Printf(TEXT("Health under threshold")));
		return true;
	}
	
	return false;
}