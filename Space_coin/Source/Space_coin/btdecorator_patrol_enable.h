#pragma once

#include "game_info.h"
#include "BehaviorTree/BTDecorator.h"
#include "btdecorator_patrol_enable.generated.h"

UCLASS()
class SPACE_COIN_API Ubtdecorator_patrol_enable : public UBTDecorator
{
	GENERATED_BODY()

public:
	Ubtdecorator_patrol_enable();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;

};
