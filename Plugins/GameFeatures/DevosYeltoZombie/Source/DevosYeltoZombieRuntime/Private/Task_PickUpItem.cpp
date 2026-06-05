// Fill out your copyright notice in the Description page of Project Settings.

#include "Task_PickUpItem.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Common/InventoryComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "Survivor/SurvivorPawn.h"

EBTNodeResult::Type UTask_PickUpItem::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard) return EBTNodeResult::Failed;

	UObject* ItemObject = Blackboard->GetValueAsObject(ItemKey.SelectedKeyName);
	
	Blackboard->SetValueAsObject("Item", ItemObject);
		
	EPathFollowingRequestResult::Type result{};
	if (AActor* Item = Cast<AActor>(ItemObject))
	{
		result = OwnerComp.GetAIOwner()->MoveToActor(Item);
	}
	
	if (ASurvivorPawn* survivor = Cast<ASurvivorPawn>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		UInventoryComponent* InventoryComponent = Cast<UInventoryComponent>(survivor->GetComponentByClass(UInventoryComponent::StaticClass()));
		if (InventoryComponent)
		{
			InventoryComponent->GrabItem(1, Cast<ABaseItem>(ItemObject));
			Blackboard->SetValueAsObject("Item", nullptr);
		}
	}
	
	return EBTNodeResult::Succeeded;
}
