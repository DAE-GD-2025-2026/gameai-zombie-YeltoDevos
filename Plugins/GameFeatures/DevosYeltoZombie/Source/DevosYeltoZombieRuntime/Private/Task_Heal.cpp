// Fill out your copyright notice in the Description page of Project Settings.


#include "Task_Heal.h"
#include "AIController.h"
#include "Survivor/SurvivorPawn.h"
#include "Common/InventoryComponent.h"

EBTNodeResult::Type UTask_Heal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ASurvivorPawn* survivor = Cast<ASurvivorPawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (!survivor) return EBTNodeResult::Failed;
	
	UInventoryComponent* InventoryComponent = Cast<UInventoryComponent>(survivor->GetComponentByClass(UInventoryComponent::StaticClass()));
	if (!InventoryComponent) return EBTNodeResult::Failed;
	
	const int medkitIdx{2};
	if (InventoryComponent->UseItem(medkitIdx))
	{
		if (InventoryComponent->GetInventory()[medkitIdx]->GetValue() <=0)
		{
			InventoryComponent->RemoveItem(medkitIdx);
		};
		return EBTNodeResult::Succeeded;
		
	}
	
	return EBTNodeResult::Failed;
}