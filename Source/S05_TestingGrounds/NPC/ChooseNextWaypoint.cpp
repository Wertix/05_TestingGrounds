// Copyright Igor Berus 2017

#include "S05_TestingGrounds.h"
#include "ChooseNextWaypoint.h"
#include "AIController.h"
#include "PatrolRoute.h"
#include "BehaviorTree/BlackboardComponent.h"
//
//UChooseNextWaypoint::UChooseNextWaypoint()
//{
//}

int32 UChooseNextWaypoint::ReturnIndex() const { return Index; }

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// TODO protect against empty patrol routes

	// Get the patrol route
	auto ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	auto PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();
	if (!ensure(PatrolRoute))
	{
		return EBTNodeResult::Failed;
	}
	// Warn about empty patrol routes
	auto PatrolPoints = PatrolRoute->GetPatrolPoints();
	if (PatrolPoints.Num() <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("A guard has missing patrol points."));
		return EBTNodeResult::Failed;
	}

	// Set next waypoint
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);

	// Cycle the index
	auto NextIndex = (Index + 1) % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);

	return EBTNodeResult::Succeeded;
}
