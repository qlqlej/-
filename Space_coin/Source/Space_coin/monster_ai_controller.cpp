#include "monster_ai_controller.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "monster.h"

Amonster_ai_controller::Amonster_ai_controller()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBAsset(TEXT("BlackboardData'/Game/SpaceCoinContent/Monster/blackboard/monster_bb.monster_bb'"));

	if (BBAsset.Succeeded()) {
		bb_asset = BBAsset.Object;
	}
}

void Amonster_ai_controller::BeginPlay()
{
	Super::BeginPlay();
}

void Amonster_ai_controller::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}

void Amonster_ai_controller::OnUnPossess()
{
	Super::OnUnPossess();
}

void Amonster_ai_controller::SetTarget(UObject* target)
{
	Blackboard->SetValueAsObject(TEXT("Target"), target);
}


AMyCharacter* Amonster_ai_controller::GetTarget() const
{
	return Cast<AMyCharacter>(Blackboard->GetValueAsObject(TEXT("Target")));
}