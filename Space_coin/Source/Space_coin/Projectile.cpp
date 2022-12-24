// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Client.h"
#include "game_instance.h"
#include "monster.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "MainGamePlayerController.h"
#include "damage_number_ui.h"
#include "Math/UnrealMathUtility.h"


AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	collision_sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	collision_sphere->InitSphereRadius(20.0f);
	collision_sphere->BodyInstance.SetCollisionProfileName("Projectile");
	
	RootComponent = collision_sphere;

	ProjectileMovment =
		CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovment->UpdatedComponent = collision_sphere;
	ProjectileMovment->InitialSpeed = speed;
	ProjectileMovment->MaxSpeed = 1000000.0f;
	ProjectileMovment->bRotationFollowsVelocity = true;
	ProjectileMovment->bShouldBounce = true;

	InitialLifeSpan = 3.0f;
}


void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	collision_sphere->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

}


void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::OnHit(UPrimitiveComponent* hit_comp, AActor* other_actor, UPrimitiveComponent* other_comp, FVector normal_impulse, const FHitResult& hit)
{
	class Amonster* monster_character = Cast<Amonster>(other_actor);
	if (monster_character != nullptr)
	{
		float random = FMath::RandRange(0,99) + FMath::RandRange(0, 99)*0.01;
		if (critical_percent > random)
		{
			damage = damage * 2;
			critical = true;
		}
		if (owner == true) 
		{
			if (critical)
			{
				AMainGamePlayerController* player_controller = Cast<AMainGamePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
				critical_damage_number_ui_object = CreateWidget<Udamage_number_ui>(player_controller, critical_damage_number_class);
				critical_damage_number_ui_object->damage_amount = damage;
				critical_damage_number_ui_object->critical = true;
				critical_damage_number_ui_object->damage_target = monster_character;
				critical_damage_number_ui_object->AddToViewport();
			}
			else
			{
				AMainGamePlayerController* player_controller = Cast<AMainGamePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
				damage_number_ui_object = CreateWidget<Udamage_number_ui>(player_controller, damage_number_class);
				damage_number_ui_object->damage_amount = damage;
				damage_number_ui_object->critical = false;
				damage_number_ui_object->damage_target = monster_character;
				damage_number_ui_object->AddToViewport();
			}

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
		hit_delegate.ExecuteIfBound();
	}
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		GetWorld(), spark, GetActorLocation(), FRotator::ZeroRotator, FVector(3.0f), true, true, ENCPoolMethod::None, true);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), hit_sound, GetActorLocation());
	
	Destroy();
}
