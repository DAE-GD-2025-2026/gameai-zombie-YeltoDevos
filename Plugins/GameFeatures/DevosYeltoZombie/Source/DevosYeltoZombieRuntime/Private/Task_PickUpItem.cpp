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
	
	ASurvivorPawn* survivor = Cast<ASurvivorPawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (!survivor) return EBTNodeResult::Failed;
	
	UInventoryComponent* InventoryComponent = Cast<UInventoryComponent>(survivor->GetComponentByClass(UInventoryComponent::StaticClass()));
	if (!InventoryComponent) return EBTNodeResult::Failed;

	

	UObject* ItemObject = Blackboard->GetValueAsObject(ItemKey.SelectedKeyName);
		
	// EPathFollowingRequestResult::Type result{};
	// if (AActor* Item = Cast<AActor>(ItemObject))
	// {
	// 	  result = OwnerComp.GetAIOwner()->MoveToActor(Item);
	// }
	
	int slotIdx{};
	if (ItemKey.SelectedKeyName == "Pistol")
	{
		slotIdx = 0;
	}
	else if (ItemKey.SelectedKeyName == "Shotgun")
	{
		slotIdx = 1;
	}	
	else if (ItemKey.SelectedKeyName == "Medkit")
	{
		slotIdx = 2;
	}
	else if (ItemKey.SelectedKeyName == "Food")
	{
		slotIdx = 3;
	}
	else if (ItemKey.SelectedKeyName == "Garbage")
	{
		slotIdx = 4;
	}
	

	if (InventoryComponent->GrabItem(slotIdx, Cast<ABaseItem>(ItemObject)))
	{
		//Blackboard->SetValueAsObject(ItemKey.SelectedKeyName, nullptr);
		return EBTNodeResult::Succeeded;
	}

	
	return EBTNodeResult::Failed;
}
