// Fill out your copyright notice in the Description page of Project Settings.


#include "sniper_projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "MyCharacter.h"
#include "Engine.h"
#include "game_instance.h"
#include "Client.h"
#include "MainGamePlayerController.h"
#include "damage_number_ui.h"
#include "monster.h"

Asniper_projectile::Asniper_projectile()
{
	projectile_speed = 100000.f;
	gravity_delay = 0.1f;
	gravity_scale = 3.5f;

	projectile_collision = CreateDefaultSubobject<UBoxComponent>(FName("ProjectileCollision"));
	projectile_collision->InitBoxExtent(FVector(2.f));
	projectile_collision->BodyInstance.SetCollisionProfileName("Projectile");

	SetRootComponent(projectile_collision);


	projectile_movement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovment"));
	projectile_movement->UpdatedComponent = projectile_collision;
	projectile_movement->InitialSpeed = projectile_speed;
	projectile_movement->bShouldBounce = false;
	projectile_movement->ProjectileGravityScale = 0.f;

	projectile_mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("ProjectileMesh"));
	projectile_mesh->SetupAttachment(RootComponent);

	
	InitialLifeSpan = 3.0f;

}

void Asniper_projectile::BeginPlay()
{
	Super::BeginPlay();
	projectile_collision->OnComponentHit.AddDynamic(this, &Asniper_projectile::OnHit);
	FTimerHandle dummy_handle;
	GetWorldTimerManager().SetTimer(dummy_handle, this, &Asniper_projectile::ApplyGravity, gravity_delay, false);
	UNiagaraComponent* shoot_spark = UNiagaraFunctionLibrary::SpawnSystemAttached(trail, projectile_mesh, TEXT("None"),
		FVector(-50,0,0), FRotator::ZeroRotator, EAttachLocation::SnapToTarget, false, true, ENCPoolMethod::None, true);
}

void Asniper_projectile::OnHit(UPrimitiveComponent* hit_comp, AActor* other_actor, UPrimitiveComponent* other_comp, FVector normal_impulse, const FHitResult& hit)
{
	SetActorEnableCollision(false);
	if (other_actor->IsA(AMyCharacter::StaticClass()))
	{
	}
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
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		GetWorld(), spark, GetActorLocation(), FRotator::ZeroRotator, FVector(3.0f), true, true, ENCPoolMethod::None, true);
	projectile_movement->ProjectileGravityScale = 0;
	SetActorLocation(GetActorLocation());
	FTimerHandle handle2;
	GetWorld()->GetTimerManager().SetTimer(handle2, FTimerDelegate::CreateLambda([&]()
		{
			Destroy();
		}), 0.7f, false);
	
}
void Asniper_projectile::ApplyGravity()
{
	projectile_movement->ProjectileGravityScale = gravity_scale;
}



