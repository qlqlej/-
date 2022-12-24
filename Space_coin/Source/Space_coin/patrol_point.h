#pragma once

#include "game_info.h"
#include "GameFramework/Actor.h"
#include "patrol_point.generated.h"

UCLASS()
class SPACE_COIN_API Apatrol_point : public AActor
{
	GENERATED_BODY()
	
public:	
	Apatrol_point();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
