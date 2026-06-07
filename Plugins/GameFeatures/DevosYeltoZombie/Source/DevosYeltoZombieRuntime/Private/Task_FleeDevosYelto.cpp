// Fill out your copyright notice in the Description page of Project Settings.


#include "Task_FleeDevosYelto.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "Survivor/SurvivorPawn.h"

EBTNodeResult::Type UTask_FleeDevosYelto::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
	
	EPathFollowingRequestResult::Type result{};
	result = OwnerComp.GetAIOwner()->MoveToLocation(fleePoint);
	
	if (result == EPathFollowingRequestResult::Type::Failed) return EBTNodeResult::Failed;
	
	return EBTNodeResult::Succeeded;
}
