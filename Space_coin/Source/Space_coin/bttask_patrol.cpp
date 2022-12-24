#include "bttask_patrol.h"
#include "monster_ai_controller.h"
#include "monster.h"

Ubttask_patrol::Ubttask_patrol()
{
	NodeName = TEXT("Patrol");
	bNotifyTick = true;
}

EBTNodeResult::Type Ubttask_patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type result = Super::ExecuteTask(OwnerComp, NodeMemory);

	return EBTNodeResult::InProgress;
}

void Ubttask_patrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	Amonster_ai_controller* controller = Cast<Amonster_ai_controller>(OwnerComp.GetAIOwner());

	Amonster* monster = Cast<Amonster>(controller->GetPawn());

	// ���� ����� �̵� ���ߵ��� 

	// ���Ͱ� ������� ��� �̵� ����.
	FVector monster_loc = monster->GetActorLocation();
	FVector patrol_point_loc = monster->GetPatrolPoint()->GetActorLocation();

	patrol_point_loc.Z = monster_loc.Z;

	controller->MoveToActor(monster->GetPatrolPoint(), -1.f, false, true);


	// ���Ͱ� �ش� ��ġ�� �����ߴ��� �Ǵ�.
	monster_loc.Z = 0.f;
	patrol_point_loc.Z = 0.f;

	float dist = FVector::Distance(monster_loc, patrol_point_loc);

	if (dist <= 5.f) {  // �ش� ��ġ�� �����ؼ� ���̻� �������� ���� ���
		monster->ChangeAnim(Emonster_anim::Idle);  // Idle�� �ִϸ��̼� ����.

		controller->StopMovement();

		monster->NextPatrolPoint();

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}