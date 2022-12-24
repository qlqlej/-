#include "btservice_player_attack.h"
#include "first_monster_ai_controller.h"
#include "monster.h"
#include "DrawDebugHelpers.h"

Ubtservice_player_attack::Ubtservice_player_attack()
{
	NodeName = TEXT("PlayerAttack");
	Interval = 0.1f;
	RandomDeviation = 0.f;
}

void Ubtservice_player_attack::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	Afirst_monster_ai_controller* controller = Cast<Afirst_monster_ai_controller>(OwnerComp.GetAIOwner());
	if (!IsValid(controller)) {
		return;
	}

	Amonster* monster = Cast<Amonster>(controller->GetPawn());
	if (!IsValid(monster)) {
		return;
	}

	bool overlap = false;

	// 공격 확인

	controller->SetPlayerAttack(overlap);

}