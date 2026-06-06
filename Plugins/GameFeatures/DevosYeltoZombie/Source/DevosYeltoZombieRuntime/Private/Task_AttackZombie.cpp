// Fill out your copyright notice in the Description page of Project Settings.


#include "Task_AttackZombie.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Common/InventoryComponent.h"
#include "Navigation/PathFollowingComponent.h"
#include "Survivor/SurvivorPawn.h"
#include "Zombies/BaseZombie.h"

EBTNodeResult::Type UTask_AttackZombie::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard) return EBTNodeResult::Failed;
	
	ASurvivorPawn* survivor = Cast<ASurvivorPawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (!survivor) return EBTNodeResult::Failed;
	
	UInventoryComponent* InventoryComponent = Cast<UInventoryComponent>(survivor->GetComponentByClass(UInventoryComponent::StaticClass()));
	if (!InventoryComponent) return EBTNodeResult::Failed;
	
	ABaseZombie* Zombie = Cast<ABaseZombie>(Blackboard->GetValueAsObject(ZombieKey.SelectedKeyName));
	if (!Zombie) return EBTNodeResult::Failed;
	
	OwnerComp.GetAIOwner()->MoveToActor(Zombie);
	if (InventoryComponent->UseItem(0))
	{
		return EBTNodeResult::Succeeded;
	}
	else
	{
		InventoryComponent->RemoveItem(0);
	}
	
	if (InventoryComponent->UseItem(1))
	{
		return EBTNodeResult::Succeeded;
	}
	else
	{
		InventoryComponent->RemoveItem(1);
	}
	
	return EBTNodeResult::Failed;
}