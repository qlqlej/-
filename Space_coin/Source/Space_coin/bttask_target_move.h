#pragma once

#include "game_info.h"
#include "BehaviorTree/BTTaskNode.h"
#include "bttask_target_move.generated.h"

UCLASS()
class SPACE_COIN_API Ubttask_target_move : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	Ubttask_target_move();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory); 
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

};
