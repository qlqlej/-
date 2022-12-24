#include "bttask_attack.h"
#include "monster_ai_controller.h"
#include "monster.h"

Ubttask_attack::Ubttask_attack()
{
	NodeName = TEXT("Attack");
	bNotifyTick = true;
	attack = false;
}

EBTNodeResult::Type Ubttask_attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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


	monster->ChangeAnim(Emonster_anim::Attack);  // 몬스터가 살아있을 때 공격 시작

	attack = true;  // attack 진행 중.

	monster->Attack();  // 공격 상태로 설정.

	return EBTNodeResult::InProgress;
}

void Ubttask_attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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

	// 타겟 바라보도록 회전.
	FVector dir = target->GetActorLocation() - monster->GetActorLocation();
	dir.Normalize();

	monster->SetActorRotation(FRotator(0.f, dir.Rotation().Yaw, 0.f));

	// 공격이 끝났을 경우 종료.
	if (!attack) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

void Ubttask_attack::AttackEnd()
{
	attack = false;  
}