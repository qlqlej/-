#pragma once

#include "game_info.h"
#include "BehaviorTree/BTTaskNode.h"
#include "bttask_attack.generated.h"

UCLASS()
class SPACE_COIN_API Ubttask_attack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	Ubttask_attack();

private:
	bool attack; 

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

public:
	void AttackEnd();

};
