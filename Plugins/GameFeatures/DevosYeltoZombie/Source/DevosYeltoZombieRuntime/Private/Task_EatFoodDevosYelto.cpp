// Fill out your copyright notice in the Description page of Project Settings.


#include "Task_EatFoodDevosYelto.h"
#include "AIController.h"
#include "Survivor/SurvivorPawn.h"
#include "Common/InventoryComponent.h"

EBTNodeResult::Type UTask_EatFoodDevosYelto::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ASurvivorPawn* survivor = Cast<ASurvivorPawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (!survivor) return EBTNodeResult::Failed;
	
	UInventoryComponent* InventoryComponent = Cast<UInventoryComponent>(survivor->GetComponentByClass(UInventoryComponent::StaticClass()));
	if (!InventoryComponent) return EBTNodeResult::Failed;
	
	const int foodIdx{3};
	if (InventoryComponent->UseItem(foodIdx))
	{
		if (InventoryComponent->GetInventory()[foodIdx]->GetValue() <=0)
		{
			InventoryComponent->RemoveItem(foodIdx);
		};
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}