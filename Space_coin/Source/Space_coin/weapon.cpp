// Fill out your copyright notice in the Description page of Project Settings.

#include "weapon.h"
#include "Engine.h"
#include "Components/SphereComponent.h"
#include "Animation/AnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "MainGamePlayerController.h"
#include "damage_number_ui.h"
#include "game_instance.h"


Aweapon::Aweapon(const class FObjectInitializer& objectinitalizer)
	:Super(objectinitalizer)
{
	PrimaryActorTick.bCanEverTick = true;

	weapon_mesh = objectinitalizer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("WeaponMesh"));
	weapon_mesh->CastShadow = true;
	weapon_mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = weapon_mesh;

	weapon_collision = CreateDefaultSubobject<USphereComponent>(TEXT("WeaponCollision"));
	weapon_collision->InitSphereRadius(30.0f);
	weapon_collision->AttachTo(weapon_mesh, "DamageSocket");

	inPlayRate = 1.0f;


}

void Aweapon::SetOwningPawn(Apublic_character* new_owner)
{
	if (my_pawn != new_owner)
	{
		my_pawn = new_owner;
	}
}

void Aweapon::AttachMeshToPawn()
{
	if (my_pawn)
	{
		USkeletalMeshComponent* pawn_mesh = my_pawn->GetSpecificPawnMesh();
		FName attach_point = my_pawn->GetWeaponAttachPoint();
		weapon_mesh->AttachTo(pawn_mesh, attach_point);
	}
}

void Aweapon::OnEquip(const Aweapon* last_weapon)
{
	AttachMeshToPawn();
}

void Aweapon::OnUnEquip()
{
	weapon_mesh->DetachFromParent();
}



void Aweapon::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	class Amonster* monster_character = Cast<Amonster>(OtherActor);
	if (monster_character != nullptr && my_pawn->during_attack == true)
	{
		UNiagaraComponent* ultimate_effect = UNiagaraFunctionLibrary::SpawnSystemAttached(spark, weapon_mesh, TEXT("None"),
			FVector::ZeroVector, FRotator::ZeroRotator, FVector(10, 10, 10), EAttachLocation::SnapToTarget, false, ENCPoolMethod::None, true, true);
		
		SetActorEnableCollision(false);

		damage = Cast<AMyCharacter>(my_pawn)->atk;
		float random = FMath::RandRange(0, 99) + FMath::RandRange(0, 99) * 0.01;
		critical_percent = Cast<AMyCharacter>(my_pawn)->critical_percent;
		if (critical_percent > random)
		{
			damage = damage * 2;
			critical = true;
		}
		else
		{
			critical = false;
		}
		if (owner == true) 
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), sword_hit_sound, OtherActor->GetActorLocation());

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
				damage_number_ui_object->damage_amount = Cast<AMyCharacter>(my_pawn)->atk;
				damage_number_ui_object->critical = false;
				damage_number_ui_object->damage_target = monster_character;
				damage_number_ui_object->AddToViewport();
			}

			CS_DAMAGE_MONSTER_PACKET infodata;
			infodata.damage = damage;
			infodata.attack_sessionID = Cast<AMyCharacter>(my_pawn)->mySessionID;
			infodata.sessionID = monster_character->sessionID;
			infodata.size = sizeof(CS_DAMAGE_MONSTER_PACKET);
			infodata.type = CS_DAMAGE_MONSTER;
			infodata.monsterType = monster_character->monster_type;

			Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
			GameInstanceRef->client->SendToMonsterDamage(infodata);
		}
	}

}
