#include "asteroid_one.h"

Aasteroid_one::Aasteroid_one()
{
	PrimaryActorTick.bCanEverTick = true;

	asteroid_static_mesh = CreateDefaultSubobject<UStaticMeshComponent> (TEXT("asteroid_static_mesh"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/SpaceCoinContent/Mesh/Asteroid/asteroid1_LOD0'"));

	if (MeshAsset.Succeeded()) {
		asteroid_static_mesh->SetStaticMesh(MeshAsset.Object);
	}
	
	asteroid_particle_system = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("asteroid_particle_system"));
	asteroid_particle_system->AttachTo(asteroid_static_mesh);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystemAsset(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Fire'"));

	if (ParticleSystemAsset.Succeeded()) {
		asteroid_particle_system->SetTemplate(ParticleSystemAsset.Object);
		asteroid_particle_system->SetRelativeLocation(FVector(0.f, -6000.f, 0.f));
		asteroid_particle_system->SetRelativeScale3D(FVector(300.f, 300.f, 300.f));
	}

	asteroid_static_mesh->SetSimulatePhysics(true);
	asteroid_static_mesh->SetCollisionProfileName("PhysicsActor");

}

void Aasteroid_one::BeginPlay()
{
	Super::BeginPlay();

	asteroid_static_mesh->SetEnableGravity(true);
	
}

void Aasteroid_one::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

