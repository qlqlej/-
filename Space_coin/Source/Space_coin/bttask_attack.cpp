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


	monster->ChangeAnim(Emonster_anim::Attack);  // ���Ͱ� ������� �� ���� ����

	attack = true;  // attack ���� ��.

	monster->Attack();  // ���� ���·� ����.

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

	// Ÿ�� �ٶ󺸵��� ȸ��.
	FVector dir = target->GetActorLocation() - monster->GetActorLocation();
	dir.Normalize();

	monster->SetActorRotation(FRotator(0.f, dir.Rotation().Yaw, 0.f));

	// ������ ������ ��� ����.
	if (!attack) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

void Ubttask_attack::AttackEnd()
{
	attack = false;  
}