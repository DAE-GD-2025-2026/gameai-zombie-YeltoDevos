// Fill out your copyright notice in the Description page of Project Settings.


#include "Task_Flee.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UTask_Flee::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	if (Blackboard && BlackBoardKey.SelectedKeyName != NAME_None)
	{
		UObject* Value = Blackboard->GetValueAsObject(BlackBoardKey.SelectedKeyName);
		Blackboard->SetValueAsObject("WanderLocation", Value);
	}
	
	
	
	return EBTNodeResult::Succeeded;
}