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
	const int pistolIdx{0};
	if (InventoryComponent->UseItem(pistolIdx))
	{
		CheckItemCanBeUsed(pistolIdx, InventoryComponent);
		return EBTNodeResult::Succeeded;
	}
	
	const int shotgunIdx{1};
	if (InventoryComponent->UseItem(shotgunIdx))
	{
		CheckItemCanBeUsed(shotgunIdx, InventoryComponent);
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}

void UTask_AttackZombie::CheckItemCanBeUsed(const int itemIdx, UInventoryComponent* inventory)
{
	if (inventory->GetInventory()[itemIdx]->GetValue() <=0)
	{
		inventory->RemoveItem(itemIdx);
	};
}
