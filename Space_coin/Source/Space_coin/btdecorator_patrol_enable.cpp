#include "btdecorator_patrol_enable.h"
#include "monster_ai_controller.h"
#include "monster.h"

Ubtdecorator_patrol_enable::Ubtdecorator_patrol_enable()
{
	NodeName = TEXT("PatrolEnable");
}

bool Ubtdecorator_patrol_enable::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool result = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	Amonster_ai_controller* controller = Cast<Amonster_ai_controller>(OwnerComp.GetAIOwner());
	if (!IsValid(controller)) {
		return false;
	}

	Amonster* monster = Cast<Amonster>(controller->GetPawn());
	if (!IsValid(monster)) {
		return false;
	}

	if (monster->GetPatrolPointCount() < 2) {
		return false;
	}

	return true;
}