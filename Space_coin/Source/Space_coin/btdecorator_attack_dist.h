#pragma once

#include "game_info.h"
#include "BehaviorTree/BTDecorator.h"
#include "btdecorator_attack_dist.generated.h"

UCLASS()
class SPACE_COIN_API Ubtdecorator_attack_dist : public UBTDecorator
{
	GENERATED_BODY()

public:
	Ubtdecorator_attack_dist();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;

};
