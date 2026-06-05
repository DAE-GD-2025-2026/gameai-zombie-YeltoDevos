// Fill out your copyright notice in the Description page of Project Settings.


#include "Task_VisitHouse.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/PathFollowingComponent.h"

EBTNodeResult::Type UTask_VisitHouse::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard) return EBTNodeResult::Failed;

	UObject* HouseObject = Blackboard->GetValueAsObject(HouseKey.SelectedKeyName);
	//Check if house has been visited
	bool visitedHouse = std::ranges::any_of(VisitedHouses, [HouseObject](const auto House){return House == HouseObject;});
	if (visitedHouse)
	{
		Blackboard->SetValueAsObject("House", nullptr);
		return EBTNodeResult::Succeeded;
	}
	
	Blackboard->SetValueAsObject("House", HouseObject);
		
	EPathFollowingRequestResult::Type result{};
	if (AActor* House = Cast<AActor>(HouseObject))
	{
		result = OwnerComp.GetAIOwner()->MoveToActor(House);
	}
		
	if (result == EPathFollowingRequestResult::Type::AlreadyAtGoal)
	{
		VisitedHouses.emplace_back(HouseObject);
		return EBTNodeResult::Succeeded;
	}

	
	return EBTNodeResult::Succeeded;
}
