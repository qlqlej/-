#include "third_monster_ai_controller.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "monster.h"

Athird_monster_ai_controller::Athird_monster_ai_controller()
{
	
}

void Athird_monster_ai_controller::BeginPlay()
{
	Super::BeginPlay();
}

void Athird_monster_ai_controller::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(bb_asset, Blackboard)) {
		// 원하는 행동트리 지정.

		if (!RunBehaviorTree(bt_asset)) {

		}
	}
}

void Athird_monster_ai_controller::OnUnPossess()
{
	Super::OnUnPossess();
}

void Athird_monster_ai_controller::SetTarget(UObject* target)
{
	Blackboard->SetValueAsObject(TEXT("Target"), target);
}

AMyCharacter* Athird_monster_ai_controller::GetTarget() const
{
	return Cast<AMyCharacter>(Blackboard->GetValueAsObject(TEXT("Target")));
}