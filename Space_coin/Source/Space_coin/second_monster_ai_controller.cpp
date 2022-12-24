#include "second_monster_ai_controller.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "monster.h"

Asecond_monster_ai_controller::Asecond_monster_ai_controller()
{
}

void Asecond_monster_ai_controller::BeginPlay()
{
	Super::BeginPlay();
}

void Asecond_monster_ai_controller::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(bb_asset, Blackboard)) {
		// 원하는 행동트리 지정.

		if (!RunBehaviorTree(bt_asset)) {

		}
	}
}

void Asecond_monster_ai_controller::OnUnPossess()
{
	Super::OnUnPossess();
}

void Asecond_monster_ai_controller::SetTarget(UObject* target)
{
	Blackboard->SetValueAsObject(TEXT("Target"), target);
}

AMyCharacter* Asecond_monster_ai_controller::GetTarget() const
{
	return Cast<AMyCharacter>(Blackboard->GetValueAsObject(TEXT("Target")));
}