#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "asteroid_two.generated.h"

UCLASS()
class SPACE_COIN_API Aasteroid_two : public AActor
{
	GENERATED_BODY()
	
public:	
	Aasteroid_two();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* asteroid_static_mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* asteroid_particle_system;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
