#include "btservice_player_detect.h"
#include "monster_ai_controller.h"
#include "monster.h"
#include "DrawDebugHelpers.h"

Ubtservice_player_detect::Ubtservice_player_detect()
{
	NodeName = TEXT("PlayerDetect");
	Interval = 0.5f;  
	RandomDeviation = 0.f;  
}

void Ubtservice_player_detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	Amonster_ai_controller* controller = Cast<Amonster_ai_controller>(OwnerComp.GetAIOwner());
	if (!IsValid(controller)) {
		return;
	}

	Amonster* monster = Cast<Amonster>(controller->GetPawn());
	if (!IsValid(monster)) {
		return;
	}

	FCollisionQueryParams params(NAME_None, false, monster);
	TArray<FOverlapResult> result_array;
	float trace_range = monster->GetTraceRange();
	bool overlap = GetWorld()->OverlapMultiByChannel(result_array, monster->GetActorLocation(), FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel4, FCollisionShape::MakeSphere(trace_range), params);

#if ENABLE_DRAW_DEBUG  
	FVector center = monster->GetActorLocation();
	FColor draw_color = overlap ? FColor::Red : FColor::Green;

	DrawDebugSphere(GetWorld(), center, trace_range, 10, draw_color, false, 0.5f);

#endif
	if (overlap) {
		controller->SetTarget(result_array[0].GetActor());
	}
	else {
		controller->SetTarget(nullptr);
	}

}