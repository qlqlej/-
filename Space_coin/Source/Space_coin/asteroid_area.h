#pragma once

#include "game_info.h"
#include "GameFramework/Actor.h"
#include "asteroid_area.generated.h"

UCLASS()
class SPACE_COIN_API Aasteroid_area : public AActor
{
	GENERATED_BODY()
	
public:	
	Aasteroid_area();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	UBoxComponent* box_collision;

	AActor* spawn_asteroid;

	UBlueprint* bp_asteroid_one;
	UBlueprint* bp_asteroid_two;
	UBlueprint* bp_asteroid_three;

	bool asteroid_start;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
