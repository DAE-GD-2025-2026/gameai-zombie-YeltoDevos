// Fill out your copyright notice in the Description page of Project Settings.


#include "Task_Flee.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Survivor/SurvivorPawn.h"

EBTNodeResult::Type UTask_Flee::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard) return EBTNodeResult::Failed;

	AActor* target = Cast<AActor>(Blackboard->GetValueAsObject(FleeTarget.SelectedKeyName));
	if (!target) return EBTNodeResult::Failed;
	
	ASurvivorPawn* survivor = Cast<ASurvivorPawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (!survivor) return EBTNodeResult::Failed;
	
	FVector fleeDirection{survivor->GetActorLocation() - target->GetActorLocation()};
	fleeDirection.Normalize();
	
	FVector fleePoint{survivor->GetActorLocation() + (fleeDirection * FleeDistance)};
	
	OwnerComp.GetAIOwner()->MoveToLocation(fleePoint);
	
	return EBTNodeResult::Succeeded;
}
