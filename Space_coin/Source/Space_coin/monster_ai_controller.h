#pragma once

#include "game_info.h"
#include "MyCharacter.h"
#include "AIController.h"
#include "monster_ai_controller.generated.h"

UCLASS()
class SPACE_COIN_API Amonster_ai_controller : public AAIController
{
	GENERATED_BODY()

public:
	Amonster_ai_controller();

protected:
	UBlackboardData* bb_asset; 

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;   

public:
	void SetTarget(UObject* target);

	AMyCharacter* GetTarget() const;

};
