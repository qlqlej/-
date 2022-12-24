#pragma once

#include "game_info.h"
#include "GameFramework/Actor.h"
#include "fog_water.generated.h"

UCLASS()
class SPACE_COIN_API Afog_water : public AActor
{
	GENERATED_BODY()
	
public:	
	Afog_water();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Light)
	class UExponentialHeightFogComponent* fog;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
