// Copyright Igor Berus 2017

#pragma once

#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "PatrollingGuard.generated.h"

//class UChooseNextWaypoint;

/**
 * 
 */
UCLASS()
class S05_TESTINGGROUNDS_API APatrollingGuard : public ATP_ThirdPersonCharacter
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditInstanceOnly, Category = "Patrol Route")
	TArray<AActor*> PatrolPoints;

	/*int32 Index = 0;

	UChooseNextWaypoint ChooseNextWaypoint;

	void CycleIndex();*/
};
