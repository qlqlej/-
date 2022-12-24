// Fill out your copyright notice in the Description page of Project Settings.


#include "public_character.h"
#include "weapon.h"
#include "Components/CapsuleComponent.h"


// Sets default values
Apublic_character::Apublic_character()
{
	PrimaryActorTick.bCanEverTick = true;

	health = 100.f;
	combo_cnt = 0;
	bis_attack_button_when_attack = false;
}
USkeletalMeshComponent* Apublic_character::GetSpecificPawnMesh() const
{
	return GetMesh();
}

FName Apublic_character::GetWeaponAttachPoint() const
{
	return weapon_attachpoint;
}
void Apublic_character::EquipWeapon(Aweapon* weapon)
{
	if (weapon)
	{
		SetCurrentWeapon(weapon, current_weapon);
	}
}

void Apublic_character::WeaponAttack()
{
	if (current_weapon)
	{
		current_weapon->owner = !is_othercharacter;

		if (during_attack == false)//공격중이지 않을떄
			StartAttack();
		else if (during_attack == true)//공격중일때
			bis_attack_button_when_attack = true;
	}
}

void Apublic_character::AddWeapon(Aweapon* weapon)
{
	if (weapon)
	{
		inventory.AddUnique(weapon);
	}
}

void Apublic_character::StartAttack()
{
	current_weapon->SetActorEnableCollision(true);
	UAnimInstance* anim_instnace = GetMesh()->GetAnimInstance();
	if (!anim_instnace || !attack_anim) return;

	during_attack = true;

	const char* combo_list[] = { "Combo01", "Combo02","Combo03", "Combo04"};
	if (!(anim_instnace->Montage_IsPlaying(attack_anim)))
	{	
		anim_instnace->Montage_Play(attack_anim);
	}
	else
	{
		anim_instnace->Montage_Play(attack_anim);
		anim_instnace->Montage_JumpToSection(FName(combo_list[combo_cnt]), attack_anim);
	}
}

void Apublic_character::EndAttacking()
{
	during_attack = false;
	combo_cnt = 0;
}

void Apublic_character::AttackInputChecking()
{
	if (combo_cnt >= 3)
		combo_cnt = 0;
	if (bis_attack_button_when_attack == true)
	{
		combo_cnt += 1;
		bis_attack_button_when_attack = false;
		StartAttack();
	}
}

void Apublic_character::SetCurrentWeapon(Aweapon* new_weapon, Aweapon* last_weapon)
{
	Aweapon* local_last_weapon = NULL;

	if (last_weapon != NULL)
	{
		local_last_weapon = last_weapon;
	}
	else if (new_weapon != current_weapon)
	{
		local_last_weapon = current_weapon;
	}
	
	if (local_last_weapon)
	{
		local_last_weapon->OnUnEquip();
	}
	current_weapon = new_weapon;

	if (new_weapon)
	{
		new_weapon->SetOwningPawn(this);
		new_weapon->OnEquip(last_weapon);
	}
}

void Apublic_character::SpawnDefaultsInventory()
{
	int32 num_weapon_classes = DefaultInventoryClasses.Num();

	for (int32 i = 0; i < num_weapon_classes; i++)
	{
		if (DefaultInventoryClasses[i])
		{
			FActorSpawnParameters spawn_info;

			Aweapon* new_weapon = GetWorld()->SpawnActor<Aweapon>(DefaultInventoryClasses[i], spawn_info);
			AddWeapon(new_weapon);
		}
	}
	if (inventory.Num() > 0)
	{
		EquipWeapon(inventory[0]);
	}
}

void Apublic_character::OnHit(float damage_taken, FDamageEvent const& damage_event, APawn* pawn_instrigator, AActor* damage_causer)
{

	if (damage_taken > 0.f)
	{
		ApplyDamageMomentum(damage_taken, damage_event, pawn_instrigator, damage_causer);
	}
}


void Apublic_character::OnDieAnimationEnd()
{
	this->SetActorHiddenInGame(true);
	SetLifeSpan(0.1f);
}



