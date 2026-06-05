// Fill out your copyright notice in the Description page of Project Settings.

#include "StudentPerceptor.h"

#include <algorithm>

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Zombies/BaseZombie.h"
#include "Items/BaseItem.h"
#include "PurgeZones/PurgeZone.h"
#include "Village/House/House.h"

UStudentPerceptor::UStudentPerceptor()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UStudentPerceptor::BeginPlay()
{
	Super::BeginPlay();
	
	if (auto PerceptionComp = GetOwner()->GetComponentByClass<UAIPerceptionComponent>())
	{
		PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &UStudentPerceptor::OnPerceptionUpdated);
	}
	

}

void UStudentPerceptor::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, 
	FString::Printf(TEXT("Saw Something!")));
	
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn) return;
	
	AAIController* AIController = Cast<AAIController>(OwnerPawn->GetController());
	if (!AIController) return;
	
	UBlackboardComponent* blackBoard = AIController->GetBlackboardComponent();
	if (!blackBoard) return;
	
	
	if (Stimulus.WasSuccessfullySensed())												
	{
		if (ABaseZombie* SensedZombie = Cast<ABaseZombie>(Actor))
		{
			GEngine->AddOnScreenDebugMessage(5, 2.f, FColor::Orange, 
			FString::Printf(TEXT("Saw zombie!")));
			blackBoard->SetValueAsObject(FName("Zombie"), SensedZombie);
		}
		
		if (ABaseItem* Item = Cast<ABaseItem>(Actor))
		{
			GEngine->AddOnScreenDebugMessage(5, 2.f, FColor::Orange,
				FString::Printf(TEXT("Saw item!")));
			blackBoard->SetValueAsObject(FName("Item"), Item);
		}
		
		if (AHouse* SensedHouse = Cast<AHouse>(Actor))
		{
			GEngine->AddOnScreenDebugMessage(5, 1.f, FColor::Green, 
			FString::Printf(TEXT("Saw house!")));
			blackBoard->SetValueAsObject(FName("House"), SensedHouse);
		}
	}
}
