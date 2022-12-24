#pragma once

#include "EngineMinimal.h"
#include "GameFramework/Actor.h"
#include "asteroid_three.generated.h"

UCLASS()
class SPACE_COIN_API Aasteroid_three : public AActor
{
	GENERATED_BODY()
	
public:	
	Aasteroid_three();

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
