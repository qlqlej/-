#include "btdecorator_attack_dist.h"
#include "monster_ai_controller.h"
#include "monster.h"

Ubtdecorator_attack_dist::Ubtdecorator_attack_dist()
{
	NodeName = TEXT("AttackDistance");
}

bool Ubtdecorator_attack_dist::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
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

	if (monster->IsAttack()) {
		controller->StopMovement();
		return true;
	}

	ACharacter* target = controller->GetTarget();
	if (!IsValid(target)) {
		return false;
	}

	FVector ai_loc = monster->GetActorLocation();
	FVector target_loc = target->GetActorLocation();

	ai_loc.Z = 0.f;
	target_loc.Z = 0.f;

	float dist = FVector::Distance(ai_loc, target_loc);


	if (dist <= monster->GetAttackDistance()) {
		controller->StopMovement();
		return true;
	}


	return false;
}