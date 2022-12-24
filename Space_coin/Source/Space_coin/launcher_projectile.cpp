// Fill out your copyright notice in the Description page of Project Settings.

#include "launcher_projectile.h"
#include "Gameframework/ProjectileMovementComponent.h"
#include "game_instance.h"
#include "Client.h"
#include "MainGamePlayerController.h"
#include "damage_number_ui.h"
#include "monster.h"

// Sets default values
Alauncher_projectile::Alauncher_projectile()
{
	collision_comp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	collision_comp->InitSphereRadius(5.0f);
	collision_comp->BodyInstance.SetCollisionProfileName("Projectile");
	collision_comp->OnComponentHit.AddDynamic(this, &Alauncher_projectile::OnHit);

	collision_comp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	collision_comp->CanCharacterStepUpOn = ECB_No;

	RootComponent = collision_comp;

	projectile_movment = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	projectile_movment->UpdatedComponent = collision_comp;
	projectile_movment->InitialSpeed = 3000.f;
	projectile_movment->MaxSpeed = 3000.f;
	projectile_movment->bRotationFollowsVelocity = true;
	projectile_movment->bShouldBounce = true;

	InitialLifeSpan = 10.0f;
	radius = 100;

	explosion_particle_range = 4.0f;
}



void Alauncher_projectile::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle handle;
	GetWorld()->GetTimerManager().SetTimer(handle, this, &Alauncher_projectile::OnDetonate, 5.f, false);
}
void Alauncher_projectile::OnHit(UPrimitiveComponent* hit_comp, AActor* other_actor, UPrimitiveComponent* other_comp, FVector normal_impulse, const FHitResult& hit)
{
	if ((other_actor != NULL) && (other_actor != this))
	{
		OnDetonate();
	}

}
void Alauncher_projectile::OnDetonate()
{
	UParticleSystemComponent* Explosion = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosion_particles, GetActorTransform());
	Explosion->SetRelativeScale3D(FVector(explosion_particle_range));

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), explosion_sound, GetActorLocation());

	TArray<FHitResult> hit_actors;

	FVector start_trace = GetActorLocation();
	FVector end_trace = start_trace;
	end_trace.Z += 300.f;

	FCollisionShape collision_shape;
	collision_shape.ShapeType = ECollisionShape::Sphere;
	collision_shape.SetSphere(radius);

	if (GetWorld()->SweepMultiByChannel(hit_actors, start_trace, end_trace, FQuat::FQuat(), ECC_WorldStatic, collision_shape))
	{
		for (auto actors :hit_actors)
		{
			class Amonster* monster_character = Cast<Amonster>(actors.Actor);
			if (monster_character != nullptr)
			{
				if (owner == true) 
				{
					AMainGamePlayerController* player_controller = Cast<AMainGamePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
					damage_number_ui_object = CreateWidget<Udamage_number_ui>(player_controller, damage_number_class);
					damage_number_ui_object->damage_amount = damage;
					damage_number_ui_object->damage_target = monster_character;
					damage_number_ui_object->AddToViewport();

					CS_DAMAGE_MONSTER_PACKET infodata;
					infodata.damage = damage;
					infodata.attack_sessionID = session_id;
					infodata.sessionID = monster_character->sessionID;
					infodata.size = sizeof(CS_DAMAGE_MONSTER_PACKET);
					infodata.type = CS_DAMAGE_MONSTER;
					infodata.monsterType = monster_character->monster_type;

					Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
					GameInstanceRef->client->SendToMonsterDamage(infodata);
				}
			}
			UStaticMeshComponent* sm = Cast<UStaticMeshComponent>((actors).Actor->GetRootComponent());
			
			if (sm)
			{
				sm->AddRadialImpulse(GetActorLocation(), 1000.f, 5000.f, ERadialImpulseFalloff::RIF_Linear, true);
			}
		}
	}

	Destroy();
}