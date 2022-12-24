// Fill out your copyright notice in the Description page of Project Settings.


#include "sword_slash.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "MainGamePlayerController.h"
#include "damage_number_ui.h"
#include "game_instance.h"

Asword_slash::Asword_slash()
{
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMovment =
		CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));

	collision_box = CreateDefaultSubobject<UBoxComponent>(TEXT("box Collision"));
	collision_box->BodyInstance.SetCollisionProfileName("Projectile");

	RootComponent = collision_box;
	ProjectileMovment->UpdatedComponent = collision_box;
	ProjectileMovment->InitialSpeed = speed;
	ProjectileMovment->MaxSpeed = 100000.0f;
	ProjectileMovment->bRotationFollowsVelocity = true;
	ProjectileMovment->bShouldBounce = false;
	ProjectileMovment->ProjectileGravityScale = 0;

	InitialLifeSpan = 3.0f;
}
void Asword_slash::BeginPlay()
{
	Super::BeginPlay();

	collision_box->OnComponentBeginOverlap.AddDynamic(this, &Asword_slash::OnOverlapBegin);

}
void Asword_slash::OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& hitResult)
{
	
	class Amonster* monster_character = Cast<Amonster>(otherActor);
	if (monster_character != nullptr)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(), spark, otherActor->GetActorLocation(), FRotator::ZeroRotator, FVector(3.0f), true, true, ENCPoolMethod::None, true);
		if (owner == true) 
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), sword_hit_sound, otherActor->GetActorLocation());

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

}