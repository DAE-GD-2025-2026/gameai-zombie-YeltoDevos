// Fill out your copyright notice in the Description page of Project Settings.


#include "Dec_DistanceSmallerThanDevosYelto.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Zombies/BaseZombie.h"
#include "Survivor/SurvivorPawn.h"

bool UDec_DistanceSmallerThanDevosYelto::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard) return false;
	
	ABaseZombie* zombie = Cast<ABaseZombie>(Blackboard->GetValueAsObject(ZombieKey.SelectedKeyName));
	if (!zombie) return false;
	
	ASurvivorPawn* survivor = Cast<ASurvivorPawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (!survivor) return false;
	
	
	const double distance{ (zombie->GetActorLocation() - survivor->GetActorLocation()).Length() };
	
	if (distance < Distance) return true;
	
	return false;
}