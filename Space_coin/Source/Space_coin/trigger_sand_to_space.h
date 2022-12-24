#pragma once

#include "game_info.h"
#include "GameFramework/Actor.h"
#include "trigger_sand_to_space.generated.h"

UCLASS()
class SPACE_COIN_API Atrigger_sand_to_space : public AActor
{
	GENERATED_BODY()
	
public:	
	Atrigger_sand_to_space();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* volume_box;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


};
