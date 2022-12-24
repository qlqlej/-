// Fill out your copyright notice in the Description page of Project Settings.


#include "inventory_component.h"
#include "MyCharacter.h"
#include "game_instance.h"
// Sets default values for this component's properties
Uinventory_component::Uinventory_component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...

	inventory_map = {};
}


// Called when the game starts
void Uinventory_component::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void Uinventory_component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void Uinventory_component::AddtoInventory(int32 itemid, int32 quantity)
{
	if (quantity > 0)
	{
		if (inventory_map.Contains(itemid))
		{
			inventory_map.Add(itemid, quantity + inventory_map[itemid]);
		}
		else
		{
			inventory_map.Add(itemid, quantity);
		}
		Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
		switch (GameInstanceRef->mycharacter_type)
		{
		case CHARACTER_TYPE::HUMAN:
		{
			AMyCharacter* player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			switch (itemid)
			{
			case 0:
			{
				GameInstanceRef->critical_up = inventory_map[itemid];
				player->AddCriticalPercent();
				break;
			}
			case 1:
				GameInstanceRef->speed_up = inventory_map[itemid];
				player->AddSpeed();
				break;
			case 2:
				GameInstanceRef->attack_up = inventory_map[itemid];
				player->AddAtk();
				break;
			case 3:
				GameInstanceRef->hp_up = inventory_map[itemid];
				player->AddMaxHp();
				break;
			case 4:
				GameInstanceRef->recover_hp_up = inventory_map[itemid];
				player->AddHealing();
				break;
			case 5:
				GameInstanceRef->sniper_up = inventory_map[itemid];
				player->AddSniperDamge();
				break;
			case 6:
				GameInstanceRef->attack_hp_up = inventory_map[itemid];
				player->AddAtkHpUp();
				break;
			case 7:
				GameInstanceRef->launcher_up = inventory_map[itemid];
				player->AddLauncherDamage();
				break;
			case 8:
				GameInstanceRef->launcher_range_up = inventory_map[itemid];
				player->AddLauncherRadius();
				break;
			case 9:
				GameInstanceRef->jump_up = inventory_map[itemid];
				player->AddJump();
				break;
			case 10:
				GameInstanceRef->missile_up = inventory_map[itemid];
				player->AddMissileDamage();
				break;
			case 11:
				GameInstanceRef->slash_up = inventory_map[itemid];
				player->AddSlashDamage();
				break;
			case 12:
				GameInstanceRef->slash_size_up = inventory_map[itemid];
				player->AddSlashSize();
				break;
			case 13:
				GameInstanceRef->ultimate_up = inventory_map[itemid];
				player->AddUltimateDamage();
				break;
			default:
				break;
			}
			break;
		}
		case CHARACTER_TYPE::SPACESHIP:
		{
			Aspace_ship* ship = Cast<Aspace_ship>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			switch (itemid)
			{
			case 0:
			{
				GameInstanceRef->critical_up = inventory_map[itemid];
				ship->owner_character->AddCriticalPercent();
		
				break;
			}
			case 1:
				GameInstanceRef->speed_up = inventory_map[itemid];
				ship->owner_character->AddSpeed();
		
				break;
			case 2:
				GameInstanceRef->attack_up = inventory_map[itemid];
				ship->owner_character->AddAtk();
	
				break;
			case 3:
				GameInstanceRef->hp_up = inventory_map[itemid];
				ship->owner_character->AddMaxHp();
				break;
			case 4:
				GameInstanceRef->recover_hp_up = inventory_map[itemid];
				ship->owner_character->AddHealing();
				break;
			case 5:
				GameInstanceRef->sniper_up = inventory_map[itemid];
				ship->owner_character->AddSniperDamge();
				break;
			case 6:
				GameInstanceRef->attack_hp_up = inventory_map[itemid];
				ship->owner_character->AddAtkHpUp();
				break;
			case 7:
				GameInstanceRef->launcher_up = inventory_map[itemid];
				ship->owner_character->AddLauncherDamage();
				break;
			case 8:
				GameInstanceRef->launcher_range_up = inventory_map[itemid];
				ship->owner_character->AddLauncherRadius();
				break;
			case 9:
				GameInstanceRef->jump_up = inventory_map[itemid];
				ship->owner_character->AddJump();
				break;
			case 10:
				GameInstanceRef->missile_up = inventory_map[itemid];
				ship->owner_character->AddMissileDamage();
				break;
			case 11:
				GameInstanceRef->slash_up = inventory_map[itemid];
				ship->owner_character->AddSlashDamage();
				break;
			case 12:
				GameInstanceRef->slash_size_up = inventory_map[itemid];
				ship->owner_character->AddSlashSize();
				break;
			case 13:
				GameInstanceRef->ultimate_up = inventory_map[itemid];
				ship->owner_character->AddUltimateDamage();
				break;
			default:
				break;
			}
			break;
		}
		default:
			break;
		}
		
	}
}

