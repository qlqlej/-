#include "asteroid_three.h"

Aasteroid_three::Aasteroid_three()
{
	PrimaryActorTick.bCanEverTick = true;

	asteroid_static_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("asteroid_static_mesh"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/SpaceCoinContent/Mesh/Asteroid/asteroid3_LOD0'"));

	if (MeshAsset.Succeeded()) {
		asteroid_static_mesh->SetStaticMesh(MeshAsset.Object);
	}

	asteroid_particle_system = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("asteroid_particle_system"));
	asteroid_particle_system->AttachTo(asteroid_static_mesh);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystemAsset(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Fire'"));

	if (ParticleSystemAsset.Succeeded()) {
		asteroid_particle_system->SetTemplate(ParticleSystemAsset.Object);
		asteroid_particle_system->SetRelativeLocation(FVector(-7000.f, 24000.f, 22000.f));
		asteroid_particle_system->SetRelativeScale3D(FVector(1500.f, 1500.f, 1500.f));
	}

	asteroid_static_mesh->SetSimulatePhysics(true);
	asteroid_static_mesh->SetCollisionProfileName("PhysicsActor");

}

void Aasteroid_three::BeginPlay()
{
	Super::BeginPlay();

	asteroid_static_mesh->SetEnableGravity(true);

}

void Aasteroid_three::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

