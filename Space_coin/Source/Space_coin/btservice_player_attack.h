#pragma once

#include "game_info.h"
#include "BehaviorTree/BTService.h"
#include "btservice_player_attack.generated.h"

UCLASS()
class SPACE_COIN_API Ubtservice_player_attack : public UBTService
{
	GENERATED_BODY()

public:
	Ubtservice_player_attack();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
