#include "first_monster_ai_controller.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "monster.h"

Afirst_monster_ai_controller::Afirst_monster_ai_controller()
{
	
}

void Afirst_monster_ai_controller::BeginPlay()
{
	Super::BeginPlay();
}

void Afirst_monster_ai_controller::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if(UseBlackboard(bb_asset, Blackboard))  {
		// 원하는 행동트리 지정.

		if (!RunBehaviorTree(bt_asset)) {

		}
	}
}

void Afirst_monster_ai_controller::OnUnPossess()
{
	Super::OnUnPossess();
}

void Afirst_monster_ai_controller::SetTarget(UObject* target)
{
	Blackboard->SetValueAsObject(TEXT("Target"), target); 
}

AMyCharacter* Afirst_monster_ai_controller::GetTarget() const
{
	return Cast<AMyCharacter>(Blackboard->GetValueAsObject(TEXT("Target")));
}

void Afirst_monster_ai_controller::SetPlayerAttack(bool attack)  // PlayerAttack 설정.
{
	Blackboard->SetValueAsBool(TEXT("PlayerAttack"), attack);
}