#pragma once

#include "game_info.h"
#include "BehaviorTree/BTTaskNode.h"
#include "bttask_patrol.generated.h"

UCLASS()
class SPACE_COIN_API Ubttask_patrol : public UBTTaskNode
{
	GENERATED_BODY()

public:
	Ubttask_patrol();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

};
