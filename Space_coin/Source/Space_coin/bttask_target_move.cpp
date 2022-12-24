#include "bttask_target_move.h"
#include "monster_ai_controller.h"
#include "monster.h"

Ubttask_target_move::Ubttask_target_move()
{
	NodeName = TEXT("TargetMove");
	bNotifyTick = true;
}

EBTNodeResult::Type Ubttask_target_move::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	Amonster_ai_controller* controller = Cast<Amonster_ai_controller>(OwnerComp.GetAIOwner());
	if (!IsValid(controller)) {
		return EBTNodeResult::Failed;
	}

	Amonster* monster = Cast<Amonster>(controller->GetPawn());
	if (!IsValid(monster)) {
		return EBTNodeResult::Failed;
	}

	ACharacter* target = controller->GetTarget();
	if (!IsValid(target)) {
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::InProgress;
}

void Ubttask_target_move::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	Amonster_ai_controller* controller = Cast<Amonster_ai_controller>(OwnerComp.GetAIOwner());

	Amonster* monster = Cast<Amonster>(controller->GetPawn());

	ACharacter* target = controller->GetTarget();
	if (!target) {
		controller->StopMovement();

		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

		return;
	}

	// 몬스터 사망시 이동 멈추도록 

	// 몬스터가 살아있을 경우 이동 시작
	UAIBlueprintHelperLibrary::SimpleMoveToActor(controller, target);

	// 거리 구하기
	FVector ai_loc = monster->GetActorLocation();
	FVector target_loc = target->GetActorLocation();

	ai_loc.Z = 0.f;
	target_loc.Z = 0.f;

	float dist = FVector::Distance(ai_loc, target_loc);

	if (dist <= monster->GetAttackDistance()) {
		controller->StopMovement();

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);

		return;
	}
}
