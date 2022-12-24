#include "asteroid_two.h"


Aasteroid_two::Aasteroid_two()
{

	PrimaryActorTick.bCanEverTick = true;

	asteroid_static_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("asteroid_static_mesh"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/SpaceCoinContent/Mesh/Asteroid/asteroid2_LOD0'"));

	if (MeshAsset.Succeeded()) {
		asteroid_static_mesh->SetStaticMesh(MeshAsset.Object); 
	}

	asteroid_particle_system = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("asteroid_particle_system"));
	asteroid_particle_system->AttachTo(asteroid_static_mesh);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleSystemAsset(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Fire'"));

	if (ParticleSystemAsset.Succeeded()) {
		asteroid_particle_system->SetTemplate(ParticleSystemAsset.Object);
		asteroid_particle_system->SetRelativeLocation(FVector(10000.f, 12000.f, 22000.f));
		asteroid_particle_system->SetRelativeScale3D(FVector(900.f, 900.f, 900.f));
	}

	asteroid_static_mesh->SetSimulatePhysics(true);
	asteroid_static_mesh->SetCollisionProfileName("PhysicsActor");

}

void Aasteroid_two::BeginPlay()
{
	Super::BeginPlay();

	asteroid_static_mesh->SetEnableGravity(true);

}

void Aasteroid_two::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

