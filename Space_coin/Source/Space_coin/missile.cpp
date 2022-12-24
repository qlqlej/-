// Fill out your copyright notice in the Description page of Project Settings.


#include "missile.h"
#include "TimerManager.h"
#include "Engine.h"
#include "game_instance.h"
#include "Client.h"
#include "MainGamePlayerController.h"
#include "damage_number_ui.h"
#include "monster.h"

Amissile::Amissile(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	collision_comp = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("CollisionComp"));
	RootComponent = collision_comp;

	missile_mesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("MissileMesh"));
	missile_mesh->SetupAttachment(RootComponent);

	projectile_movement = ObjectInitializer.CreateDefaultSubobject<UProjectileMovementComponent>(this, TEXT("ProjectileMovement"));
	projectile_movement->UpdatedComponent = collision_comp;
	
	projectile_movement->HomingAccelerationMagnitude = 1000.0f;
	projectile_movement->InitialSpeed = 1000;
	projectile_movement->MaxSpeed = 1000;
	projectile_movement->bShouldBounce = true;
	projectile_movement->Velocity = FVector(0, 0, 0);
	projectile_movement->ProjectileGravityScale = 0.f;
	
	has_target_position = false;
	has_no_target = false;
	target = NULL;
	delay_timer = 0.f;
	has_finished_delay = false;
	lifetime_countdown = 15.f;
	can_be_destroyed = false;
}

#pragma region Setup Target Logic
void Amissile::BeginPlay()
{
	Super::BeginPlay();
	collision_comp->OnComponentHit.AddDynamic(this, &Amissile::OnHit);
	
	if (!has_finished_delay)
	{
		projectile_movement->Velocity = GetActorUpVector() * 200.f;

		this->SetActorEnableCollision(false);
	}
}

void Amissile::LockOn(Amonster* monster)
{
	
	if (monster)
	{
		missile_target_monster = monster;
		FTimerHandle handle;
		GetWorldTimerManager().SetTimer(handle, this, &Amissile::Homing, 1.5f, false);
	}
}

void Amissile::Homing()
{
	if (IsValid(missile_target_monster))
	{
		if (this)
		{
			projectile_movement->HomingTargetComponent =
				missile_target_monster->GetCapsuleComponent();
			projectile_movement->bIsHomingProjectile = true;
			projectile_movement->HomingAccelerationMagnitude = 4000;
		}
		
	}
	
}

void Amissile::Loop()
{
	FTimerHandle handle;
	GetWorld()->GetTimerManager().SetTimer(handle, this, &Amissile::Loop, 0.5f, false);
}




void Amissile::UpdateTarget()
{
	
}
void Amissile::DelayLogic(float dTime)
{
	if (!has_finished_delay)
	{
		delay_timer += 1 * dTime;

		if (delay_timer > 1.5f)
		{
			this->SetActorEnableCollision(true);
			has_finished_delay = true;
		}
	}
}



#pragma endregion


void Amissile::Tick(float DeltaTime)
{
	
	Super::Tick(DeltaTime);
	
	if (!has_finished_delay)
	{
		DelayLogic(DeltaTime);
	}
	else
	{
		if (this->IsValidLowLevel() && !IsValid(missile_target_monster))
		{
			PlayExplosion(explosion_system);
			PlayExplosionSound(explosion_sound);
			Destroy();
		}
	}
}


void Amissile::OnHit(UPrimitiveComponent* hit_comp, AActor* other_actor, UPrimitiveComponent* other_comp, FVector normal_impulse, const FHitResult& hit)
{
	class Amonster* monster_character = Cast<Amonster>(other_actor);
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

	PlayExplosion(explosion_system);
	PlayExplosionSound(explosion_sound);

	if (this->IsValidLowLevel())
		Destroy();
	
	
}


void Amissile::Explode()
{
	PlayExplosion(explosion_system);
	PlayExplosionSound(explosion_sound);

	if (this->IsValidLowLevel())
		Destroy();
}


class UParticleSystemComponent* Amissile::PlayExplosion(class UParticleSystem* explosion)
{
	class UParticleSystemComponent* retVal = NULL;

	if (explosion)
	{
		class UWorld* const world = GetWorld();

		if (world)
		{
			FVector myPos = GetActorLocation();
			FRotator myRot = GetActorRotation();

			retVal = UGameplayStatics::SpawnEmitterAtLocation(world, explosion, myPos, myRot, true);
		}
	}

	return retVal;
}


class UAudioComponent* Amissile::PlayExplosionSound(class USoundCue* sound)
{
	class UAudioComponent* retVal = NULL;

	if (sound)
		retVal = UGameplayStatics::SpawnSoundAttached(sound, this->GetRootComponent());

	return retVal;
}


