// Fill out your copyright notice in the Description page of Project Settings.

#include "MainGamePlayerController.h"
#include <chrono>
#include "Kismet/GameplayStatics.h"
#include "first_ice_monster.h"
#include "second_ice_monster.h"
#include "third_ice_monster.h"
#include "first_sand_monster.h"
#include "second_sand_monster.h"
#include "third_sand_monster.h"
#include "first_water_monster.h"
#include "second_water_monster.h"
#include "third_water_monster.h"
#include "first_swimming_monster.h"
#include "second_swimming_monster.h"
#include "third_swimming_monster.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/Vector.h"
#include "MyCharacter.h"
#include "TimerManager.h"
#include "MainGameModeBase.h"
#include "ui_play_map.h"
#include "ui_coin_map.h"
#include "ui_setting.h"
#include "ui_quest_map.h"
#include "skillui.h"
#include "sword_skill_cooltime_ui.h"
#include "shop_ui.h"
#include "space_ship.h"
#include "shop_slot_ui.h"
#include "inventory_ui.h"
#include "a_coin.h"
#include "b_coin.h"
#include "c_coin.h"
#include "weapon.h"
#include "player_name_ui.h"
#include "target_maker.h"
#include "Components/TextBlock.h"
#include <string>
#include <vector>
#include "UObject/ConstructorHelpers.h"
#include "Components/InputComponent.h"
#include "Sound/SoundMix.h"
#include "Sound/SoundClass.h"
#include "crosshair_ui.h"
#include "damage_number_ui.h"

using namespace chrono;

Client* client;
AMainGameModeBase* gamemode;

AMainGamePlayerController::AMainGamePlayerController()
{
	static ConstructorHelpers::FClassFinder<Uui_play_map> play_map(TEXT("WidgetBlueprint'/Game/SpaceCoinContent/UI/PlayMapUI/play_map_wb.play_map_wb_C'"));
	if (play_map.Succeeded()) {
		play_map_ui_class = play_map.Class;
	}

	static ConstructorHelpers::FClassFinder<Uui_coin_map> coin_map(TEXT("WidgetBlueprint'/Game/SpaceCoinContent/UI/CoinUI/coin_map_wb.coin_map_wb_C'"));
	if (coin_map.Succeeded()) {
		coin_map_ui_class = coin_map.Class;
	}

	static ConstructorHelpers::FClassFinder<Uui_setting> setting_map(TEXT("WidgetBlueprint'/Game/SpaceCoinContent/UI/PlayMapUI/setting_wb.setting_wb_C'"));
	if (setting_map.Succeeded()) {
		setting_ui_class = setting_map.Class;
	}

	static ConstructorHelpers::FClassFinder<Uui_quest_map> quest_map(TEXT("WidgetBlueprint'/Game/SpaceCoinContent/UI/QuestUI/quest_map_wb.quest_map_wb_C'"));
	if (quest_map.Succeeded()) {
		quest_map_ui_class = quest_map.Class;
	}
}

void AMainGamePlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
}

void AMainGamePlayerController::BeginPlay()
{
	Super::BeginPlay();
	Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
	client = GameInstanceRef->client;
	client->SetMainPC(Cast<AMainGamePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)));
	FInputModeGameOnly InputModeData;
	SetInputMode(InputModeData);
	myCharacter = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	if (myCharacter->mySessionID == -1 && GameInstanceRef->testlogin == true)
	{
		map_name = GetWorld()->GetMapName();
		myCharacter->mySessionID = GameInstanceRef->player_sessionID;
		myCharacter->myName = FName(*GameInstanceRef->player_name);

		int changemap_x;
		int changemap_y;
		int changemap_z;
		if (GameInstanceRef->map_name == "SpaceLevel") {
			if ("IcePlanet" == map_name) {
				changemap_x = 0 + (rand() % 1000 - 500);
				changemap_y = 0 + (rand() % 1000 - 500);
				changemap_z = 50000;
			}
			else if ("SandPlanet" == map_name) {
				changemap_x = 0 + (rand() % 1000 - 500);
				changemap_y = 0 + (rand() % 1000 - 500);
				changemap_z = 50000;
			}
			else if ("WaterPlanet" == map_name) {
				changemap_x = 0 + (rand() % 1000 - 500);
				changemap_y = 0 + (rand() % 1000 - 500);
				changemap_z = 50000;
			}
		}
		else if ("IcePlanet" == GameInstanceRef->map_name) {
			changemap_x = 16866 + (rand() % 1000 - 500);
			changemap_y = -13774 + (rand() % 1000 - 500);
			changemap_z = 4848 + (rand() % 1000 - 500);
		}
		else if ("SandPlanet" == GameInstanceRef->map_name) {
			changemap_x = -17534 + (rand() % 1000 - 500);
			changemap_y = -3330 + (rand() % 1000 - 500);
			changemap_z = 10316 + (rand() % 1000 - 500);
		}
		else if ("WaterPlanet" == GameInstanceRef->map_name) {
			changemap_x = 12712 + (rand() % 1000 - 500);
			changemap_y = 13870 + (rand() % 1000 - 500);
			changemap_z = -9203 + (rand() % 1000 - 500);
		}

		myCharacter->SetActorLocation(FVector(changemap_x, changemap_y, changemap_z));

		myCharacter->health = GameInstanceRef->player_health;
		myCharacter->money = GameInstanceRef->player_money;
		myCharacter->a_coin = GameInstanceRef->player_a_coin;
		myCharacter->b_coin = GameInstanceRef->player_b_coin;
		myCharacter->c_coin = GameInstanceRef->player_c_coin;
		myCharacter->SetCriticalPercent(GameInstanceRef->critical_up);
		myCharacter->SetSpeed(GameInstanceRef->speed_up);
		myCharacter->SetAtk(GameInstanceRef->attack_up);
		myCharacter->SetMaxHp(GameInstanceRef->hp_up);
		myCharacter->SetHealing(GameInstanceRef->recover_hp_up);
		myCharacter->SetSniperDamage(GameInstanceRef->sniper_up);
		myCharacter->SetAtkHpUp(GameInstanceRef->attack_hp_up);
		myCharacter->SetLauncherDamage(GameInstanceRef->launcher_up);
		myCharacter->SetLauncherRadius(GameInstanceRef->launcher_range_up);
		myCharacter->SetLauncherRadius(GameInstanceRef->launcher_range_up);
		myCharacter->SetJump(GameInstanceRef->jump_up);
		myCharacter->SetMissileDamage(GameInstanceRef->missile_up);
		myCharacter->SetSlashDamage(GameInstanceRef->slash_up);
		myCharacter->SetSlashSize(GameInstanceRef->slash_size_up);
		myCharacter->SetUltimateDamage(GameInstanceRef->ultimate_up);

		switch (GameInstanceRef->player_weapon_type)
		{
		case WEAPON_TYPE::SWORD:
		{
			myCharacter->SendOnChangeSword();
			break;
		}
		case WEAPON_TYPE::GUN:
		{
			myCharacter->SendOnChangeGun();
			break;
		}
		default:
			break;
		}
		switch (GameInstanceRef->mycharacter_type)
		{
		case CHARACTER_TYPE::HUMAN:
		{
			client->MainPC->Possess(myCharacter);
			break;
		}
		case CHARACTER_TYPE::SPACESHIP:
		{

			FVector spawnLocation = FVector(myCharacter->GetActorLocation().X, myCharacter->GetActorLocation().Y, myCharacter->GetActorLocation().Z);
			FRotator spawnRotation = myCharacter->GetActorRotation();
			FActorSpawnParameters spawnParam;
			Aspace_ship* spawnSpaceShip = GetWorld()->SpawnActor<Aspace_ship>(SpawnToOtherSpaceShip, spawnLocation, spawnRotation, spawnParam);
			if (spawnSpaceShip)
			{
				myCharacter->GetCharacterMovement()->GravityScale = 0;
				spawnSpaceShip->SetId(GameInstanceRef->player_sessionID);
				myCharacter->spaceship = spawnSpaceShip;
				myCharacter->enter = 1;
				spawnSpaceShip->EnterCharacter(myCharacter);
				spawnSpaceShip->is_openlevel = true;
				FTimerHandle handle;
				GetWorld()->GetTimerManager().SetTimer(handle, spawnSpaceShip, &Aspace_ship::UnOpenLevel, 1.15f, false);
			}
			break;
		}
		default:
			break;
		}

	}
	if (true == GameInstanceRef->bLogin) {
		GameInstanceRef->bLogin = false;
	}
	else if (true == GameInstanceRef->bChangeMap) {
		GameInstanceRef->bChangeMap = false;
	}	

	myCharacter->use = true;

	GetWorldTimerManager().SetTimer(PlayerInfoHandle, this, &AMainGamePlayerController::SendPlayerInfo, 0.5f, true);

	update_time = 1;

	/* ui */
	play_map_ui_object = CreateWidget<Uui_play_map>(this, play_map_ui_class);
	play_map_ui_object->AddToViewport();

	play_skill_ui_object = CreateWidget<Uskillui>(this, play_skill_class);
	play_skill_ui_object->AddToViewport();

	crosshair_ui_object = CreateWidget<Ucrosshair_ui>(this, crosshair_class);
	crosshair_ui_object->AddToViewport();

	if (!myCharacter->enter)
	{
		play_skill_ui_object->SetVisibility(ESlateVisibility::Visible);
		crosshair_ui_object->SetVisibility(ESlateVisibility::Visible);
	}
	else 
	{
		play_skill_ui_object->SetVisibility(ESlateVisibility::Hidden);
		crosshair_ui_object->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AMainGamePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
	

	FName(*GameInstanceRef->player_name) = myCharacter->myName;
	GameInstanceRef->player_health = myCharacter->health;
	GameInstanceRef->player_money = myCharacter->money;
	GameInstanceRef->player_a_coin = myCharacter->a_coin;
	GameInstanceRef->player_b_coin = myCharacter->b_coin;
	GameInstanceRef->player_c_coin = myCharacter->c_coin;

	if (!myCharacter->enter) {
		if (myCharacter->is_aiming)
		{
			crosshair_ui_object->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			crosshair_ui_object->SetVisibility(ESlateVisibility::Visible);
		}
		play_skill_ui_object->SetVisibility(ESlateVisibility::Visible);
	}
	else {
		play_skill_ui_object->SetVisibility(ESlateVisibility::Hidden);
		crosshair_ui_object->SetVisibility(ESlateVisibility::Hidden);
	}
	if (!shop_visible) {
		if (WasInputKeyJustPressed(EKeys::B)) {
			if (play_shop_ui_object)
			{
				play_shop_ui_object->RemoveFromParent();
			}
			play_shop_ui_object = CreateWidget<Ushop_ui>(this, play_shop_class);
			play_shop_ui_object->AddToViewport();
			play_shop_ui_object->PressBKey();
			if (play_shop_ui_object->GetVisibility() == ESlateVisibility::Visible) {
				bShowMouseCursor = true;
				myCharacter->GetCharacterMovement()->StopMovementImmediately();
				FInputModeUIOnly InputUIMode;
				InputUIMode.SetWidgetToFocus(play_shop_ui_object->TakeWidget());
				InputUIMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
				SetInputMode(InputUIMode);
				shop_visible = true;
			}
		}
	}
	if (!inventory_visible) {
		if (WasInputKeyJustPressed(EKeys::I)) {
			play_inventory_ui_object = CreateWidget<Uinventory_ui>(this, play_inventory_class);
			play_inventory_ui_object->AddToViewport();
			play_inventory_ui_object->PressIKey();
			if (play_inventory_ui_object->GetVisibility() == ESlateVisibility::Visible) {
				bShowMouseCursor = true;
				myCharacter->GetCharacterMovement()->StopMovementImmediately();
				FInputModeUIOnly InputUIMode;
				InputUIMode.SetWidgetToFocus(play_inventory_ui_object->TakeWidget());
				InputUIMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
				SetInputMode(InputUIMode);
				inventory_visible = true;
			}
		}
	}

	if (get_coin_api_first_time == false) {
		GetWorldTimerManager().SetTimer(CoinMapUIHandle, this, &AMainGamePlayerController::SendGetCoinPriceInfo, 1.0f, true);
		get_coin_api_first_time = true;
	}

	coin_map_ui_object = CreateWidget<Uui_coin_map>(this, coin_map_ui_class);
	if (!coin_map_ui_visible) { 
		GetWorldTimerManager().ClearTimer(CoinMapUIHandle);
		if (WasInputKeyJustPressed(EKeys::P)) { 
			GetWorldTimerManager().SetTimer(CoinMapUIHandle, this, &AMainGamePlayerController::SendGetCoinPriceInfo, 1.0f, true);
			coin_map_ui_object->AddToViewport();
			coin_map_ui_object->PressPKey();
			if (coin_map_ui_object->GetVisibility() == ESlateVisibility::Visible) {
				bShowMouseCursor = true;
				myCharacter->GetCharacterMovement()->StopMovementImmediately();
				FInputModeUIOnly InputUIMode;
				InputUIMode.SetWidgetToFocus(coin_map_ui_object->TakeWidget());
				InputUIMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
				SetInputMode(InputUIMode);
				coin_map_ui_visible = true;
			}
		}
	}

	if (!setting_ui_visible) {
		if (WasInputKeyJustPressed(EKeys::Escape)) {
			setting_ui_object = CreateWidget<Uui_setting>(this, setting_ui_class);
			setting_ui_object->AddToViewport();
			setting_ui_object->PressEscKey();
			if (setting_ui_object->GetVisibility() == ESlateVisibility::Visible) {
				bShowMouseCursor = true;
				myCharacter->GetCharacterMovement()->StopMovementImmediately();
				FInputModeUIOnly InputUIMode;
				InputUIMode.SetWidgetToFocus(setting_ui_object->TakeWidget());
				InputUIMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
				SetInputMode(InputUIMode);
				setting_ui_visible = true;
			}
		}
	}

	if (!quest_ui_visible) {
		if (WasInputKeyJustPressed(EKeys::Tab)) {
			quest_map_ui_object = CreateWidget<Uui_quest_map>(this, quest_map_ui_class);
			quest_map_ui_object->AddToViewport();
			quest_map_ui_object->PressTabKey();
			if (quest_map_ui_object->GetVisibility() == ESlateVisibility::Visible) {
				bShowMouseCursor = true;
				myCharacter->GetCharacterMovement()->StopMovementImmediately();
				FInputModeUIOnly InputUIMode;
				InputUIMode.SetWidgetToFocus(quest_map_ui_object->TakeWidget());
				InputUIMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
				SetInputMode(InputUIMode);
				quest_ui_visible = true;
			}
		}
	}

	if (!inventory_visible && !shop_visible && !coin_map_ui_visible && !setting_ui_visible && !quest_ui_visible)
	{
		FInputModeGameOnly InputModeData;
		SetInputMode(InputModeData);
		bShowMouseCursor = false;
	}

	play_skill_ui_object->cooltime_wb->UpdateDashCooltime(myCharacter->dash_skill_cooldown);
	play_skill_ui_object->cooltime_wb->UpdateLauncherCooltime(myCharacter->launcher_skill_cooldown);
	play_skill_ui_object->cooltime_wb->UpdateSniperCooltime(myCharacter->sniper_skill_cooldown);
	play_skill_ui_object->cooltime_wb->UpdateMissileCooltime(myCharacter->missile_skill_cooldown);

	play_skill_ui_object->cooltime_wb->UpdateDashCooltime(myCharacter->dash_skill_cooldown);
	play_skill_ui_object->cooltime_wb->UpdateLauncherCooltime(myCharacter->launcher_skill_cooldown);
	play_skill_ui_object->cooltime_wb->UpdateSniperCooltime(myCharacter->sniper_skill_cooldown);
	play_skill_ui_object->cooltime_wb->UpdateMissileCooltime(myCharacter->missile_skill_cooldown);
	play_skill_ui_object->sword_cooltime_wb->UpdateUltimateCooltime(myCharacter->ultimate_skill_cooldown);
	play_skill_ui_object->sword_cooltime_wb->UpdateDefenseCooltime(myCharacter->defense_skill_cooldown);
	play_skill_ui_object->sword_cooltime_wb->UpdateSlashCooltime(myCharacter->slash_skill_cooldown);


	if (true == sc_login_info_state) LoginProcess();

	if (true == sc_add_player_state) AddPlayerProcess();

	if (true == sc_move_player_state) PlayerMoveProcess();

	if (true == sc_remove_player_state) RemovePlayerProcess();

	if (true == sc_monster_info_state) AddMonsterProcess();

	if (true == sc_move_monster_state) MonsterMoveProcess();

	if (true == sc_remove_monster_state) RemoveMonsterProcess();

	if (true == sc_attack_monster_state) AttackMonsterProcess();

	if (true == sc_character_state) ChangeCharaterProcess();

	if (true == sc_weapon_state) ChangeWeaponProcess();

	if (true == sc_attack_skill_state) AttackSkillProcess();

	if (true == sc_spawn_spaceship_state) SpawnShipProcess();

	if (true == sc_change_map_state) ChangeMapProcess();

	if (true == sc_damage_monster_state) MonsterDamageProcess();

	if (true == sc_get_item_state) GetItemProcess();

	if (true == sc_item_buy_state) ItemBuyProcess();

	if (true == sc_get_coin_price_state) GetCoinPriceProcess();

	if (true == sc_buy_sell_state) BuySellProcess();

	if (true == sc_monster_attack_state) MonsterAttackProcess();

	if (true == sc_quest_state) QuestProcess();
}

// 패킷데이터 저장용 함수
void AMainGamePlayerController::SetLoginInfo(SC_LOGIN_INFO_PACKET* packet)
{
	sc_login_info_packet = new SC_LOGIN_INFO_PACKET;
	sc_login_info_packet->sessionID = packet->sessionID;
	sc_login_info_packet->character_type = packet->character_type;
	sc_login_info_packet->map_type = packet->map_type;
	strcpy_s(sc_login_info_packet->name, packet->name);
	sc_login_info_packet->x = packet->x;
	sc_login_info_packet->y = packet->y;
	sc_login_info_packet->z = packet->z;
	sc_login_info_packet->pitch = packet->pitch;
	sc_login_info_packet->yaw = packet->yaw;
	sc_login_info_packet->roll = packet->roll;
	sc_login_info_packet->a_coin = packet->a_coin;
	sc_login_info_packet->b_coin = packet->b_coin;
	sc_login_info_packet->c_coin = packet->c_coin;
	sc_login_info_packet->hp = packet->hp;
	sc_login_info_packet->gold = packet->gold;
	sc_login_info_packet->critical_up = packet->critical_up;
	sc_login_info_packet->speed_up = packet->speed_up;
	sc_login_info_packet->attack_up = packet->attack_up;
	sc_login_info_packet->hp_up = packet->hp_up;
	sc_login_info_packet->recover_hp_up = packet->recover_hp_up;
	sc_login_info_packet->sniper_up = packet->sniper_up;
	sc_login_info_packet->attack_hp_up = packet->attack_hp_up;
	sc_login_info_packet->launcher_up = packet->launcher_up;
	sc_login_info_packet->launcher_range_up = packet->launcher_range_up;
	sc_login_info_packet->jump_up = packet->jump_up;
	sc_login_info_packet->missile_up = packet->missile_up;
	sc_login_info_packet->slash_up = packet->slash_up;
	sc_login_info_packet->slash_size_up = packet->slash_size_up;
	sc_login_info_packet->ultimate_up = packet->ultimate_up; 
	sc_login_info_state = true;
}

void AMainGamePlayerController::SetAddPlayer(SC_ADD_PLAYER_PACKET* packet)
{
	if (true == myCharacter->use) {
		sc_add_player_packet = new SC_ADD_PLAYER_PACKET;
		sc_add_player_packet->sessionID = packet->sessionID;
		sc_add_player_packet->character_type = packet->character_type;
		sc_add_player_packet->weapon_type = packet->weapon_type;
		strcpy_s(sc_add_player_packet->name, packet->name);
		sc_add_player_packet->x = packet->x;
		sc_add_player_packet->y = packet->y;
		sc_add_player_packet->z = packet->z;
		sc_add_player_packet->hp = packet->hp;
		sc_add_player_packet->pitch = packet->pitch;
		sc_add_player_packet->yaw = packet->yaw;
		sc_add_player_packet->roll = packet->roll;
		sc_add_player_packet->cpitch = packet->cpitch;
		sc_add_player_packet->cyaw = packet->cyaw;
		sc_add_player_packet->croll = packet->croll;
		sc_add_player_state = true;

	}
}

void AMainGamePlayerController::UpdatePlayerToMove(SC_MOVE_PLAYER_PACKET* packet)
{
	if (true == myCharacter->use) {
		sc_move_player_packet = new SC_MOVE_PLAYER_PACKET;
		sc_move_player_packet->character_type = packet->character_type;
		sc_move_player_packet->sessionID = packet->sessionID;
		sc_move_player_packet->x = packet->x;
		sc_move_player_packet->y = packet->y;
		sc_move_player_packet->z = packet->z;
		sc_move_player_packet->hp = packet->hp;
		sc_move_player_packet->pitch = packet->pitch;
		sc_move_player_packet->yaw = packet->yaw;
		sc_move_player_packet->roll = packet->roll;
		sc_move_player_packet->cpitch = packet->cpitch;
		sc_move_player_packet->cyaw = packet->cyaw;
		sc_move_player_packet->croll = packet->croll;
		sc_move_player_packet->vx = packet->vx;
		sc_move_player_packet->vy = packet->vy;
		sc_move_player_packet->vz = packet->vz;
		sc_move_player_packet->ship_speed = packet->ship_speed;
		sc_move_player_packet->weapon_type = packet->weapon_type;
		strcpy_s(sc_move_player_packet->name , packet->name);
		sc_move_player_state = true;

	}
}

void AMainGamePlayerController::RemovePlayer(SC_REMOVE_PLAYER_PACKET* packet)
{
	if (true == myCharacter->use) {
		sc_remove_player_packet = new SC_REMOVE_PLAYER_PACKET;
		sc_remove_player_packet->sessionID = packet->sessionID;
		sc_remove_player_state = true;
	}
}

void AMainGamePlayerController::SetAddMonster(SC_MONSTER_INFO_PACKET* packet)
{
	if (true == myCharacter->use) {
		sc_monster_info_packet = new SC_MONSTER_INFO_PACKET;
		sc_monster_info_packet->sessionID = packet->sessionID;
		sc_monster_info_packet->monsterType = packet->monsterType;
		sc_monster_info_packet->x = packet->x;
		sc_monster_info_packet->y = packet->y;
		sc_monster_info_packet->z = packet->z;
		sc_monster_info_packet->pitch = packet->pitch;
		sc_monster_info_packet->yaw = packet->yaw;
		sc_monster_info_packet->roll = packet->roll;
		sc_monster_info_packet->hp = packet->hp;
		sc_monster_info_state = true;
	}
}

void AMainGamePlayerController::UpdateMonsterToMove(SC_MOVE_MONSTER_PACKET* packet)
{
	if (true == myCharacter->use) {
		sc_move_monster_packet = new SC_MOVE_MONSTER_PACKET;
		sc_move_monster_packet->sessionID = packet->sessionID;
		sc_move_monster_packet->monsterType = packet->monsterType;
		sc_move_monster_packet->x = packet->x;
		sc_move_monster_packet->y = packet->y;
		sc_move_monster_packet->z = packet->z;
		sc_move_monster_packet->pitch = packet->pitch;
		sc_move_monster_packet->yaw = packet->yaw;
		sc_move_monster_packet->roll = packet->roll;
		sc_move_monster_packet->hp = packet->hp;
		sc_move_monster_state = true;
	}
}

void AMainGamePlayerController::RemoveMonster(SC_REMOVE_MONSTER_PACKET* packet)
{
	if (true == myCharacter->use) {
		sc_remove_monster_packet = new SC_REMOVE_MONSTER_PACKET;
		sc_remove_monster_packet->sessionID = packet->sessionID;
		sc_remove_monster_state = true;
	}
}

void AMainGamePlayerController::AttackMonster(SC_ATTACK_MONSTER_PACKET* packet)
{
	if (true == myCharacter->use) {
		sc_attack_monster_packet = new SC_ATTACK_MONSTER_PACKET;
		sc_attack_monster_packet->sessionID = packet->sessionID;
		sc_attack_monster_packet->targetID = packet->targetID;
		sc_attack_monster_packet->x = packet->x;
		sc_attack_monster_packet->y = packet->y;
		sc_attack_monster_packet->z = packet->z;
		sc_attack_monster_packet->attack_type = packet->attack_type;
		sc_attack_monster_packet->monsterType = packet->monsterType;
		sc_attack_monster_state = true;
	}
}

void AMainGamePlayerController::ChangeCharacterState(SC_CHANGE_CHARACTER_PACKET* packet)
{
	if (true == myCharacter->use) {
		sc_change_character_packet = new SC_CHANGE_CHARACTER_PACKET;
		sc_change_character_packet->sessionID = packet->sessionID;
		sc_change_character_packet->x = packet->x;
		sc_change_character_packet->y = packet->y;
		sc_change_character_packet->z = packet->z;
		sc_change_character_packet->pitch = packet->pitch;
		sc_change_character_packet->yaw = packet->yaw;
		sc_change_character_packet->roll = packet->roll;
		strcpy_s(sc_change_character_packet->name, packet->name);
		switch (packet->type)
		{
		case SC_CHARACTER_CHANGE:
		{
			sc_change_character_packet->character_type = packet->character_type;
			sc_change_character_packet->weapon_type = packet->weapon_type;
			sc_character_state = true;

			
			break;
		}
		case SC_WEAPON_CHANGE:
		{
			sc_change_character_packet->weapon_type = packet->weapon_type;
			sc_weapon_state = true;

		
			break;
		}		
		}
	}
}

void AMainGamePlayerController::AttackSkill(SC_ATTACK_SKILL_PACKET* packet)
{
	if (true == myCharacter->use) {
		sc_attack_skill_packet = new SC_ATTACK_SKILL_PACKET;
		sc_attack_skill_packet->sessionID = packet->sessionID;
		sc_attack_skill_packet->attack_skill_type = packet->attack_skill_type;
		sc_attack_skill_packet->cpitch = packet->cpitch;
		sc_attack_skill_packet->cyaw = packet->cyaw;
		sc_attack_skill_packet->croll = packet->croll;
		sc_attack_skill_packet->x = packet->x;
		sc_attack_skill_packet->y = packet->y;
		sc_attack_skill_packet->z = packet->z;
		sc_attack_skill_packet->pitch = packet->pitch;
		sc_attack_skill_packet->yaw = packet->yaw;
		sc_attack_skill_packet->roll = packet->roll;
		sc_attack_skill_packet->weapon_type = packet->weapon_type;
		strcpy_s(sc_attack_skill_packet->name, packet->name);
		sc_attack_skill_packet->jump_velocity = packet->jump_velocity;
		sc_attack_skill_packet->launcher_particle_radius = packet->launcher_particle_radius;
		sc_attack_skill_packet->slash_size = packet->slash_size;
		sc_attack_skill_state = true;
	}
}

void AMainGamePlayerController::SpawnSpaceship(SC_SPAWN_SPACESHIP_PACKET* packet)
{
	if (true == myCharacter->use) {
		sc_spawn_spaceship_packet = new SC_SPAWN_SPACESHIP_PACKET;
		sc_spawn_spaceship_packet->owner_sessionID = packet->owner_sessionID;
		sc_spawn_spaceship_packet->x = packet->x;
		sc_spawn_spaceship_packet->y = packet->y;
		sc_spawn_spaceship_packet->z = packet->z;
		sc_spawn_spaceship_packet->pitch = packet->pitch;
		sc_spawn_spaceship_packet->roll = packet->roll;
		sc_spawn_spaceship_packet->yaw = packet->yaw;
		sc_spawn_spaceship_packet->player_x = packet->player_x;
		sc_spawn_spaceship_packet->player_y = packet->player_y;
		sc_spawn_spaceship_packet->player_z = packet->player_z;
		sc_spawn_spaceship_packet->player_pitch = packet->player_pitch;
		sc_spawn_spaceship_packet->player_yaw = packet->player_yaw;
		sc_spawn_spaceship_packet->player_roll = packet->player_roll;
		sc_spawn_spaceship_packet->weapon_type = packet->weapon_type;
		strcpy_s(sc_spawn_spaceship_packet->name, packet->name);
		sc_spawn_spaceship_state = true;
	}
}

void AMainGamePlayerController::CHangeMap(SC_CHANGE_MAP_PACKET* packet)
{
	sc_change_map_state = true;
}

void AMainGamePlayerController::MonsterDamage(SC_DAMAGE_MONSTER_PACKET* packet)
{
	if (true == myCharacter->use) {
		sc_damage_monster_packet = new SC_DAMAGE_MONSTER_PACKET;
		sc_damage_monster_packet->sessionID = packet->sessionID;
		sc_damage_monster_packet->hp = packet->hp;
		sc_damage_monster_packet->item = packet->item;
		sc_damage_monster_packet->attack_sessionID = packet->attack_sessionID;
		sc_damage_monster_packet->monsterType = packet->monsterType;
		sc_damage_monster_state = true;
	}
}

void AMainGamePlayerController::GetItem(SC_GET_ITEM_PACKET* packet)
{
	if (true == myCharacter->use) {
		sc_get_item_packet = new SC_GET_ITEM_PACKET;
		sc_get_item_packet->sessionID = packet->sessionID;
		sc_get_item_packet->a_coin = packet->a_coin;
		sc_get_item_packet->b_coin = packet->b_coin;
		sc_get_item_packet->c_coin = packet->c_coin;
		sc_get_item_state = true;

	}
}

void AMainGamePlayerController::GetCoinPrice(SC_COIN_PRICE_PACKET* packet)
{
	if (true == myCharacter->use) {
		sc_coin_price_packet = new SC_COIN_PRICE_PACKET;
		sc_coin_price_packet->size = packet->size;
		sc_coin_price_packet->type = packet->type;

		strcpy_s(sc_coin_price_packet->coin_data, sizeof(sc_coin_price_packet->coin_data), packet->coin_data);

		
		sc_get_coin_price_state = true;
	}
}

void AMainGamePlayerController::ItemBuy(SC_ITEM_BUY_PACKET* packet)
{
	if (true == myCharacter->use) {
		sc_item_buy_packet = new SC_ITEM_BUY_PACKET;
		sc_item_buy_packet->type = packet->type;
		sc_item_buy_packet->sessionID = packet->sessionID;
		sc_item_buy_packet->gold = packet->gold;
		sc_item_buy_packet->item_type = packet->item_type;
		sc_item_buy_packet->size = packet->size;

		sc_item_buy_state = true;
	}
}

void AMainGamePlayerController::BuySell(SC_BUY_SELL_PACKET* packet)
{
	if (true == myCharacter->use) {
		sc_buy_sell_packet = new SC_BUY_SELL_PACKET;
		sc_buy_sell_packet->type = packet->type;
		sc_buy_sell_packet->sessionID = packet->sessionID;
		sc_buy_sell_packet->gold = packet->gold;
		sc_buy_sell_packet->a_coin = packet->a_coin;
		sc_buy_sell_packet->b_coin = packet->b_coin;
		sc_buy_sell_packet->c_coin = packet->c_coin;
		sc_buy_sell_packet->size = packet->size;
		sc_buy_sell_state = true;
	}
}

void AMainGamePlayerController::MonsterAttack(SC_MONSTER_ATTACK_PACKET* packet)
{
	if (true == myCharacter->use) {
		sc_monster_attack_packet = new SC_MONSTER_ATTACK_PACKET;
		sc_monster_attack_packet->type = packet->type;
		sc_monster_attack_packet->damage = packet->damage;
		sc_monster_attack_packet->size = packet->size;

		sc_monster_attack_state = true;
	}
}

void AMainGamePlayerController::Quest(SC_QUEST_PACKET* packet)
{
	if (true == myCharacter->use) {
		sc_quest_packet = new SC_QUEST_PACKET;
		sc_quest_packet->type = packet->type;
		sc_quest_packet->quest_level = packet->quest_level;
		sc_quest_packet->goal_rate = packet->goal_rate;
		sc_quest_packet->now_rate = packet->now_rate;
		sc_quest_packet->a_coin = packet->a_coin;
		sc_quest_packet->b_coin = packet->b_coin;
		sc_quest_packet->c_coin = packet->c_coin;
		sc_quest_packet->a_purchase_cost = packet->a_purchase_cost;
		sc_quest_packet->b_purchase_cost = packet->b_purchase_cost;
		sc_quest_packet->c_purchase_cost = packet->c_purchase_cost;
		sc_quest_packet->size = packet->size;

		sc_quest_state = true;
	}
}

// 저장된 패킷 데이터 활용 함수
void AMainGamePlayerController::LoginProcess()
{
	
		/*현재 CHARACTER_TYPE::HUMAN 으로 생성되어 있으나 전달 받은 패킷이
		CHARACTER_TYPE::SPACESHIP 일 경우 생성된 캐릭터를 우주선으로 바꿀 필요가 있음*/
		switch (sc_login_info_packet->character_type)
		{
		case CHARACTER_TYPE::HUMAN:
		{
			myCharacter->mySessionID = sc_login_info_packet->sessionID;
			myCharacter->myName = sc_login_info_packet->name;
			myCharacter->health = sc_login_info_packet->hp;
			myCharacter->a_coin = sc_login_info_packet->a_coin;
			myCharacter->b_coin = sc_login_info_packet->b_coin;
			myCharacter->c_coin = sc_login_info_packet->c_coin;
			myCharacter->money = sc_login_info_packet->gold;
			myCharacter->OnChangeSword();
			myCharacter->SetCriticalPercent( sc_login_info_packet->critical_up);
			myCharacter->SetSpeed(sc_login_info_packet->speed_up);
			myCharacter->SetAtk(sc_login_info_packet->attack_up);
			myCharacter->SetMaxHp(sc_login_info_packet->hp_up);
			myCharacter->SetHealing(sc_login_info_packet->recover_hp_up);
			myCharacter->SetSniperDamage(sc_login_info_packet->sniper_up);
			myCharacter->SetAtkHpUp(sc_login_info_packet->attack_hp_up);
			myCharacter->SetLauncherDamage(sc_login_info_packet->launcher_up);
			myCharacter->SetLauncherRadius(sc_login_info_packet->launcher_range_up);
			myCharacter->SetJump(sc_login_info_packet->jump_up);
			myCharacter->SetMissileDamage(sc_login_info_packet->missile_up);
			myCharacter->SetSlashDamage(sc_login_info_packet->slash_up);
			myCharacter->SetSlashSize(sc_login_info_packet->slash_size_up);
			myCharacter->SetUltimateDamage(sc_login_info_packet->ultimate_up);
			myCharacter->use = true;
			myCharacter->SetActorLocation(FVector(sc_login_info_packet->x, sc_login_info_packet->y, sc_login_info_packet->z));
			myCharacter->SetActorRotation(FRotator(sc_login_info_packet->pitch, sc_login_info_packet->yaw, sc_login_info_packet->roll));

			Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
			GameInstanceRef->mycharacter_type = CHARACTER_TYPE::HUMAN;
			GameInstanceRef->player_sessionID = sc_login_info_packet->sessionID;
			GameInstanceRef->player_name = sc_login_info_packet->name;
			GameInstanceRef->player_a_coin = sc_login_info_packet->a_coin;
			GameInstanceRef->player_b_coin = sc_login_info_packet->b_coin;
			GameInstanceRef->player_c_coin = sc_login_info_packet->c_coin;
			GameInstanceRef->player_money = sc_login_info_packet->gold;
			GameInstanceRef->critical_up = sc_login_info_packet->critical_up;
			GameInstanceRef->speed_up = sc_login_info_packet->speed_up;
			GameInstanceRef->attack_up = sc_login_info_packet->attack_up;
			GameInstanceRef->hp_up = sc_login_info_packet->hp_up;
			GameInstanceRef->recover_hp_up = sc_login_info_packet->recover_hp_up;
			GameInstanceRef->sniper_up = sc_login_info_packet->sniper_up;
			GameInstanceRef->attack_hp_up = sc_login_info_packet->attack_hp_up;
			GameInstanceRef->launcher_up = sc_login_info_packet->launcher_up;
			GameInstanceRef->launcher_range_up = sc_login_info_packet->launcher_range_up;
			GameInstanceRef->jump_up = sc_login_info_packet->jump_up;
			GameInstanceRef->missile_up = sc_login_info_packet->missile_up;
			GameInstanceRef->slash_up = sc_login_info_packet->slash_up;
			GameInstanceRef->slash_size_up = sc_login_info_packet->slash_size_up;
			GameInstanceRef->ultimate_up = sc_login_info_packet->ultimate_up;

			GameInstanceRef->name_set = true;
			GameInstanceRef->money_set = true;
			GameInstanceRef->hp_set = true;

		}
			break;
		case CHARACTER_TYPE::SPACESHIP:
		{
			myCharacter->mySessionID = sc_login_info_packet->sessionID;
			myCharacter->myName = sc_login_info_packet->name;
			myCharacter->health = sc_login_info_packet->hp;
			myCharacter->a_coin = sc_login_info_packet->a_coin;
			myCharacter->b_coin = sc_login_info_packet->b_coin;
			myCharacter->c_coin = sc_login_info_packet->c_coin;
			myCharacter->money = sc_login_info_packet->gold;
			myCharacter->OnChangeSword();
			myCharacter->SetCriticalPercent(sc_login_info_packet->critical_up);
			myCharacter->SetSpeed(sc_login_info_packet->speed_up);
			myCharacter->SetAtk(sc_login_info_packet->attack_up);
			myCharacter->SetMaxHp(sc_login_info_packet->hp_up);
			myCharacter->SetHealing(sc_login_info_packet->recover_hp_up);
			myCharacter->SetSniperDamage(sc_login_info_packet->sniper_up);
			myCharacter->SetAtkHpUp(sc_login_info_packet->attack_hp_up);
			myCharacter->SetLauncherDamage(sc_login_info_packet->launcher_up);
			myCharacter->SetLauncherRadius(sc_login_info_packet->launcher_range_up);
			myCharacter->SetJump(sc_login_info_packet->jump_up);
			myCharacter->SetMissileDamage(sc_login_info_packet->missile_up);
			myCharacter->SetSlashDamage(sc_login_info_packet->slash_up);
			myCharacter->SetSlashSize(sc_login_info_packet->slash_size_up);
			myCharacter->SetUltimateDamage(sc_login_info_packet->ultimate_up);
			myCharacter->use = true;
			Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
			GameInstanceRef->mycharacter_type = CHARACTER_TYPE::SPACESHIP;
			GameInstanceRef->player_sessionID = sc_login_info_packet->sessionID;
			GameInstanceRef->player_name = sc_login_info_packet->name;
			GameInstanceRef->player_a_coin = sc_login_info_packet->a_coin;
			GameInstanceRef->player_b_coin = sc_login_info_packet->b_coin;
			GameInstanceRef->player_c_coin = sc_login_info_packet->c_coin;
			GameInstanceRef->player_money = sc_login_info_packet->gold;
			GameInstanceRef->critical_up = sc_login_info_packet->critical_up;
			GameInstanceRef->speed_up = sc_login_info_packet->speed_up;
			GameInstanceRef->attack_up = sc_login_info_packet->attack_up;
			GameInstanceRef->hp_up = sc_login_info_packet->hp_up;
			GameInstanceRef->recover_hp_up = sc_login_info_packet->recover_hp_up;
			GameInstanceRef->sniper_up = sc_login_info_packet->sniper_up;
			GameInstanceRef->attack_hp_up = sc_login_info_packet->attack_hp_up;
			GameInstanceRef->launcher_up = sc_login_info_packet->launcher_up;
			GameInstanceRef->launcher_range_up = sc_login_info_packet->launcher_range_up;
			GameInstanceRef->jump_up = sc_login_info_packet->jump_up;
			GameInstanceRef->missile_up = sc_login_info_packet->missile_up;
			GameInstanceRef->slash_up = sc_login_info_packet->slash_up;
			GameInstanceRef->slash_size_up = sc_login_info_packet->slash_size_up;
			GameInstanceRef->ultimate_up = sc_login_info_packet->ultimate_up;

			GameInstanceRef->name_set = true;
			GameInstanceRef->money_set = true;
			GameInstanceRef->hp_set = true;

			FVector spawnLocation = FVector(sc_login_info_packet->x, sc_login_info_packet->y, sc_login_info_packet->z);
			FRotator spawnRotation = FRotator(sc_login_info_packet->pitch, sc_login_info_packet->yaw, sc_login_info_packet->roll);
			myCharacter->SetActorLocation(spawnLocation);
			myCharacter->SetActorRotation(spawnRotation);
			myCharacter->GetCharacterMovement()->GravityScale = 0;
			//spawn ship
			FActorSpawnParameters spawnParam;
			FVector ShipspawnLocation = FVector(sc_login_info_packet->x, sc_login_info_packet->y, sc_login_info_packet->z + 5000);
			Aspace_ship* spawnSpaceShip = GetWorld()->SpawnActor<Aspace_ship>(myCharacter->ship_to_spawn, ShipspawnLocation, spawnRotation, spawnParam);
			if (spawnSpaceShip)
				spawnSpaceShip->SetId(sc_login_info_packet->sessionID);

			//enter ship
			myCharacter->spaceship = spawnSpaceShip;
			myCharacter->enter = 1;
			myCharacter->current_weapon->OnUnEquip();
			spawnSpaceShip->EnterCharacter(myCharacter);

			client->MainPC->Possess(Cast<APawn>(myCharacter->spaceship));
		}
			break;
		} 
		Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
		GameInstanceRef->testlogin = true;
	delete sc_login_info_packet;
	sc_login_info_state = false;
}

void AMainGamePlayerController::AddPlayerProcess()
{
	FVector spawnLocation;
	spawnLocation.X = sc_add_player_packet->x;
	spawnLocation.Y = sc_add_player_packet->y;
	spawnLocation.Z = sc_add_player_packet->z;

	FRotator spawnRotation;
	spawnRotation.Pitch = sc_add_player_packet->pitch;
	spawnRotation.Yaw = sc_add_player_packet->yaw;
	spawnRotation.Roll = sc_add_player_packet->roll;

	FActorSpawnParameters spawnParam;


	/*현재 CHARACTER_TYPE::HUMAN 으로 생성하나 전달 받은 패킷이
	CHARACTER_TYPE::SPACESHIP 일 경우 생성된 캐릭터를 우주선으로 생성할 필요가 있음*/
	switch (sc_add_player_packet->character_type)
	{
	case CHARACTER_TYPE::HUMAN: 
	{
		bool was_added = false;
		TArray<AActor*> AllPlayers;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyCharacter::StaticClass(), AllPlayers);
		for (auto& player : AllPlayers) {
			AMyCharacter* thisPlayer = Cast<AMyCharacter>(player);
			if (sc_add_player_packet->sessionID != thisPlayer->mySessionID) continue;
			was_added = true;
			break;
		}
		if (was_added == false)
		{
			// CHARACTER_TYPE::HUMAN으로 생성시 WEAPON_TYPE 에 따른 무기 렌더링 필요
			switch (sc_add_player_packet->weapon_type)
			{
			case WEAPON_TYPE::SWORD:
			{
				AMyCharacter* spawnPlayer = GetWorld()->SpawnActor<AMyCharacter>(SpawnToOtherPlayer, spawnLocation, spawnRotation, spawnParam);
				spawnPlayer->is_othercharacter = true;
				spawnPlayer->mySessionID = sc_add_player_packet->sessionID;
				spawnPlayer->myName = sc_add_player_packet->name;
				FText name = FText::FromName(spawnPlayer->myName);
				spawnPlayer->ui_player_name_ui->player_name->SetText(name);
				spawnPlayer->use = true;
				spawnPlayer->GetCharacterMovement()->GravityScale = 1;
				spawnPlayer->OnChangeSword();
				break;
			}
			case WEAPON_TYPE::GUN:
			{
				AMyCharacter* spawnPlayer = GetWorld()->SpawnActor<AMyCharacter>(SpawnToOtherPlayer, spawnLocation, spawnRotation, spawnParam);
				spawnPlayer->is_othercharacter = true;
				spawnPlayer->mySessionID = sc_add_player_packet->sessionID;
				spawnPlayer->myName = sc_add_player_packet->name;
				FText name = FText::FromName(spawnPlayer->myName);
				spawnPlayer->ui_player_name_ui->player_name->SetText(name);
				spawnPlayer->use = true;
				spawnPlayer->GetCharacterMovement()->GravityScale = 1;
				spawnPlayer->OnChangeGun();
				break;
			}
			}
		}
		break;
	}
	case CHARACTER_TYPE::SPACESHIP:
	{
		bool was_added = false;
		TArray<AActor*> AllPlayers;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Aspace_ship::StaticClass(), AllPlayers);
		for (auto& player : AllPlayers) {
			Aspace_ship* thisPlayer = Cast<Aspace_ship>(player);
			if (sc_add_player_packet->sessionID != thisPlayer->owner_session_id) continue;
			was_added = true;
			break;
		}
		if (was_added == false)
		{
			AMyCharacter* spawnPlayer = GetWorld()->SpawnActor<AMyCharacter>(SpawnToOtherPlayer, spawnLocation, spawnRotation, spawnParam);
			spawnPlayer->is_othercharacter = true;
			spawnPlayer->mySessionID = sc_add_player_packet->sessionID;
			spawnPlayer->myName = sc_add_player_packet->name;
			FText name = FText::FromName(spawnPlayer->myName);
			spawnPlayer->ui_player_name_ui->player_name->SetText(name);
			spawnPlayer->use = true;

			spawnPlayer->GetCharacterMovement()->StopMovementImmediately();
			spawnPlayer->SetActorEnableCollision(false);
			spawnPlayer->GetCharacterMovement()->GravityScale = 0;
			spawnPlayer->SetActorHiddenInGame(true);


			Aspace_ship* spawnSpaceShip = GetWorld()->SpawnActor<Aspace_ship>(SpawnToOtherSpaceShip, spawnLocation, spawnRotation, spawnParam);

			if (spawnSpaceShip)
			{
				spawnSpaceShip->SetId(sc_add_player_packet->sessionID);
				spawnSpaceShip->owner_character = spawnPlayer;
				spawnPlayer->spaceship = spawnSpaceShip;
			}

		}
		break;
	}

	}


	
	delete sc_add_player_packet;
	sc_add_player_state = false;
}

void AMainGamePlayerController::PlayerMoveProcess()
{
	switch (sc_move_player_packet->character_type)
	{
	case CHARACTER_TYPE::HUMAN:
	{
		bool was_added = false;
		TArray<AActor*> AllPlayers;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyCharacter::StaticClass(), AllPlayers);
		for (auto& player : AllPlayers) {
			AMyCharacter* thisPlayer = Cast<AMyCharacter>(player);
			if (sc_move_player_packet->sessionID != thisPlayer->mySessionID) continue;
			was_added = true;
			FLatentActionInfo Info;
			Info.CallbackTarget = thisPlayer;


			thisPlayer->health = sc_move_player_packet->hp;

			DestLocation = FVector(sc_move_player_packet->x, sc_move_player_packet->y, sc_move_player_packet->z);
			float dist = sqrt(
				pow(DestLocation.X - thisPlayer->GetActorLocation().X, 2) +
				pow(DestLocation.Y - thisPlayer->GetActorLocation().Y, 2) +
				pow(DestLocation.Z - thisPlayer->GetActorLocation().Z, 2)
			);
			
			if (thisPlayer->is_dashing)
			{
				UKismetSystemLibrary::MoveComponentTo(
					thisPlayer->GetCapsuleComponent(),
					FVector(sc_move_player_packet->x, sc_move_player_packet->y, sc_move_player_packet->z),
					FRotator(sc_move_player_packet->pitch, sc_move_player_packet->yaw, sc_move_player_packet->roll),
					false,
					false,
					1,
					false,
					EMoveComponentAction::Move,
					Info);

				thisPlayer->run = false;
				thisPlayer->PlayAnimMontage(thisPlayer->dash_montage, 0.5f, NAME_None);
				thisPlayer->is_dashing = false;
			}
			else
			{
				if (thisPlayer->is_jumping == true)
				{
					UKismetSystemLibrary::MoveComponentTo(
						thisPlayer->GetCapsuleComponent(),
						FVector(sc_move_player_packet->x, sc_move_player_packet->y, sc_move_player_packet->z),
						FRotator(sc_move_player_packet->pitch, sc_move_player_packet->yaw, sc_move_player_packet->roll),
						false,
						false,
						0.5,
						false,
						EMoveComponentAction::Move,
						Info);
				}
				else if(dist < 10 )
				{
					UKismetSystemLibrary::MoveComponentTo(
						thisPlayer->GetCapsuleComponent(),
						FVector(sc_move_player_packet->x, sc_move_player_packet->y, sc_move_player_packet->z),
						FRotator(sc_move_player_packet->pitch, sc_move_player_packet->yaw, sc_move_player_packet->roll),
						false,
						false,
						0.5,
						false,
						EMoveComponentAction::Move,
						Info);
				}
				else
				{
					UKismetSystemLibrary::MoveComponentTo(
						thisPlayer->GetCapsuleComponent(),
						FVector(sc_move_player_packet->x, sc_move_player_packet->y, sc_move_player_packet->z),
						FRotator(sc_move_player_packet->pitch, sc_move_player_packet->yaw, sc_move_player_packet->roll),
						false,
						false,
						update_time,
						false,
						EMoveComponentAction::Move,
						Info);
				}
				
			}
			
		

			
			if(thisPlayer->is_jumping == true)
			{
				thisPlayer->run = false;
			}
			else
			{
				thisPlayer->in_air = false;
				float velocity_x = (DestLocation.X - thisPlayer->GetActorLocation().X) / update_time;
				float velocity_y = (DestLocation.Y - thisPlayer->GetActorLocation().Y) / update_time;
				float velocity_z = (DestLocation.Z - thisPlayer->GetActorLocation().Z) / update_time;
				FVector velocity = FVector(velocity_x, velocity_y, velocity_z);
				if (velocity.Size() >= 10 && !thisPlayer->is_swimming && thisPlayer->enter == 0 && !thisPlayer->is_dashing)
				{
					thisPlayer->run = true;
					thisPlayer->other_player_swimming = false;
					thisPlayer->velocity_blend = velocity;
					thisPlayer->speed_blend = (dist / update_time) * 3;
					thisPlayer->rotation_blend = FRotator(sc_move_player_packet->pitch, sc_move_player_packet->yaw, sc_move_player_packet->roll);
					
				}
				else if (thisPlayer->is_swimming)
				{
					thisPlayer->run = false;
					thisPlayer->other_player_swimming = true;
					thisPlayer->swimming_speed_blend = (dist / update_time) * 10;
				}
				else
				{
					thisPlayer->velocity_blend = velocity;
					thisPlayer->other_player_swimming = false;
					thisPlayer->run = false;
					if (velocity.Size() < 10)
					{
						if (sc_move_player_packet->yaw  - thisPlayer->prev_yaw > 1)
						{
							thisPlayer->TurnRightLeft(true, false);
						}
						else
						{
							thisPlayer->turn_right = false;
						}
						if (sc_move_player_packet->yaw - thisPlayer->prev_yaw < -1)
						{
							thisPlayer->TurnRightLeft(false, true);
						}
						else
						{
							thisPlayer->turn_left = false;
						}
					}
					else
					{
						thisPlayer->TurnRightLeft(false, false);
					}
				}
			}

			thisPlayer->prev_yaw = sc_move_player_packet->yaw;
			break;
		}

		if (was_added == false)
		{
			FVector spawnLocation;
			spawnLocation.X = sc_move_player_packet->x;
			spawnLocation.Y = sc_move_player_packet->y;
			spawnLocation.Z = sc_move_player_packet->z;

			FRotator spawnRotation;
			spawnRotation.Pitch = sc_move_player_packet->pitch;
			spawnRotation.Yaw = sc_move_player_packet->yaw;
			spawnRotation.Roll = sc_move_player_packet->roll;

			FActorSpawnParameters spawnParam;
			
			switch (sc_move_player_packet->weapon_type)
			{
			case WEAPON_TYPE::SWORD:
			{
				AMyCharacter* spawnPlayer = GetWorld()->SpawnActor<AMyCharacter>(SpawnToOtherPlayer, spawnLocation, spawnRotation, spawnParam);
				spawnPlayer->is_othercharacter = true;
				spawnPlayer->mySessionID = sc_move_player_packet->sessionID;
				spawnPlayer->myName = sc_move_player_packet->name;
				FText name = FText::FromName(spawnPlayer->myName);
				spawnPlayer->ui_player_name_ui->player_name->SetText(name);
				spawnPlayer->use = true;
				spawnPlayer->OnChangeSword();
				break;
			}
			case WEAPON_TYPE::GUN:
			{
				AMyCharacter* spawnPlayer = GetWorld()->SpawnActor<AMyCharacter>(SpawnToOtherPlayer, spawnLocation, spawnRotation, spawnParam);
				spawnPlayer->is_othercharacter = true;
				spawnPlayer->mySessionID = sc_move_player_packet->sessionID;
				spawnPlayer->myName = sc_move_player_packet->name;
				FText name = FText::FromName(spawnPlayer->myName);
				spawnPlayer->ui_player_name_ui->player_name->SetText(name);
				spawnPlayer->use = true;
				spawnPlayer->OnChangeGun();
				break;
			}
			default:
				break;
			}
		}
		break;
	}
	case CHARACTER_TYPE::SPACESHIP:
	{
		bool was_added = false;
		TArray<AActor*> AllPlayers;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Aspace_ship::StaticClass(), AllPlayers);
		for (auto& player : AllPlayers) {
			Aspace_ship* thisPlayer = Cast<Aspace_ship>(player);
			if (sc_move_player_packet->sessionID != thisPlayer->owner_session_id) continue;
			was_added = true;
			FLatentActionInfo Info;
			Info.CallbackTarget = thisPlayer;

			thisPlayer->current_speed = sc_move_player_packet->ship_speed;
			DestLocation = FVector(sc_move_player_packet->x, sc_move_player_packet->y, sc_move_player_packet->z);
			float dist = sqrt(
				pow(DestLocation.X - thisPlayer->GetActorLocation().X, 2) +
				pow(DestLocation.Y - thisPlayer->GetActorLocation().Y, 2) +
				pow(DestLocation.Z - thisPlayer->GetActorLocation().Z, 2)
			);

			UKismetSystemLibrary::MoveComponentTo(
				thisPlayer->GetCapsuleComponent(),
				FVector(sc_move_player_packet->x, sc_move_player_packet->y, sc_move_player_packet->z),
				FRotator(sc_move_player_packet->pitch, sc_move_player_packet->yaw, sc_move_player_packet->roll),
				false,
				false,
				0.5,
				false,
				EMoveComponentAction::Move,
				Info);

			if (dist > 0)
			{
				float velocity_x = (DestLocation.X - thisPlayer->GetActorLocation().X) / update_time;
				float velocity_y = (DestLocation.Y - thisPlayer->GetActorLocation().Y) / update_time;
				float velocity_z = (DestLocation.Z - thisPlayer->GetActorLocation().Z) / update_time;

			}
			break;
		}

		if (was_added == false)
		{
			FVector spawnLocation;
			spawnLocation.X = sc_move_player_packet->x;
			spawnLocation.Y = sc_move_player_packet->y;
			spawnLocation.Z = sc_move_player_packet->z;

			FRotator spawnRotation;
			spawnRotation.Pitch = sc_move_player_packet->pitch;
			spawnRotation.Yaw = sc_move_player_packet->yaw;
			spawnRotation.Roll = sc_move_player_packet->roll;

			FActorSpawnParameters spawnParam;

			AMyCharacter* spawnPlayer = GetWorld()->SpawnActor<AMyCharacter>(SpawnToOtherPlayer, spawnLocation, spawnRotation, spawnParam);
			spawnPlayer->is_othercharacter = true;
			spawnPlayer->mySessionID = sc_move_player_packet->sessionID;
			spawnPlayer->myName = sc_move_player_packet->name;
			FText name = FText::FromName(spawnPlayer->myName);
			spawnPlayer->ui_player_name_ui->player_name->SetText(name);
			spawnPlayer->use = true;

			spawnPlayer->GetCharacterMovement()->StopMovementImmediately();
			spawnPlayer->SetActorEnableCollision(false);
			spawnPlayer->SetActorHiddenInGame(true);


			Aspace_ship* spawnSpaceShip = GetWorld()->SpawnActor<Aspace_ship>(SpawnToOtherSpaceShip, spawnLocation, spawnRotation, spawnParam);

			if (spawnSpaceShip)
			{
				spawnSpaceShip->SetId(sc_move_player_packet->sessionID);
				spawnSpaceShip->owner_character = spawnPlayer;
				spawnPlayer->spaceship = spawnSpaceShip;
			}
		}
		break;
	}
	default:
		break;
	}


	delete sc_move_player_packet;
	sc_move_player_state = false;
}

void AMainGamePlayerController::RemovePlayerProcess()
{
	TArray<AActor*> AllPlayers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyCharacter::StaticClass(), AllPlayers);
	for (auto& player : AllPlayers) {
		AMyCharacter* thisPlayer = Cast<AMyCharacter>(player);
		if (sc_remove_player_packet->sessionID != thisPlayer->mySessionID) continue;
		thisPlayer->Destroy();
		thisPlayer->current_weapon->Destroy();
		break;
	}

	TArray<AActor*> AllSpaceships;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), Aspace_ship::StaticClass(), AllSpaceships);
	for (auto& player : AllSpaceships) {
		Aspace_ship* thisPlayer = Cast<Aspace_ship>(player);
		if (sc_remove_player_packet->sessionID != thisPlayer->owner_session_id) continue;
		thisPlayer->owner_character->Destroy(); 
		thisPlayer->Destroy();
		break;
	}
	delete sc_remove_player_packet;
	sc_remove_player_state = false;
}

void AMainGamePlayerController::AddMonsterProcess()
{
	FVector spawnLocation;
	spawnLocation.X = sc_monster_info_packet->x;
	spawnLocation.Y = sc_monster_info_packet->y;
	spawnLocation.Z = sc_monster_info_packet->z;

	FRotator spawnRotation;
	spawnRotation.Pitch = sc_monster_info_packet->pitch;
	spawnRotation.Yaw = sc_monster_info_packet->yaw;
	spawnRotation.Roll = sc_monster_info_packet->roll;

	FActorSpawnParameters spawnParam;
	spawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	switch (sc_monster_info_packet->monsterType)
	{
	case MONSTER_TYPE::F_ICE:
	{
		TArray<AActor*> AllMonster;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Afirst_ice_monster::StaticClass(), AllMonster);
		for (auto& monster : AllMonster) {
			Afirst_ice_monster* thisMonster = Cast<Afirst_ice_monster>(monster);
			if (thisMonster->sessionID == sc_monster_info_packet->sessionID) {
				thisMonster->Destroy();
			}
		}
		Afirst_ice_monster* spawnMonster = GetWorld()->SpawnActor<Afirst_ice_monster>(SpawnToFirstIceMonster, spawnLocation, spawnRotation, spawnParam);
		spawnMonster->sessionID = sc_monster_info_packet->sessionID;
		spawnMonster->hp = sc_monster_info_packet->hp;
		spawnMonster->max_hp = 100;
		if (spawnMonster->hp <= 0)
		{
			spawnMonster->Destroy();
		}
		break;
	}
	case MONSTER_TYPE::S_ICE:
	{
		TArray<AActor*> AllMonster;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Asecond_ice_monster::StaticClass(), AllMonster);
		for (auto& monster : AllMonster) {
			Asecond_ice_monster* thisMonster = Cast<Asecond_ice_monster>(monster);
			if (thisMonster->sessionID == sc_monster_info_packet->sessionID) {
				thisMonster->Destroy();
			}
		}
		Asecond_ice_monster* spawnMonster = GetWorld()->SpawnActor<Asecond_ice_monster>(SpawnToSecondIceMonster, spawnLocation, spawnRotation, spawnParam);
		spawnMonster->sessionID = sc_monster_info_packet->sessionID;
		spawnMonster->hp = sc_monster_info_packet->hp;
		spawnMonster->max_hp = 200;
		if (spawnMonster->hp <= 0)
		{
			spawnMonster->Destroy();
		}
		break;
	}
	case MONSTER_TYPE::T_ICE:
	{
		TArray<AActor*> AllMonster;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Athird_ice_monster::StaticClass(), AllMonster);
		for (auto& monster : AllMonster) {
			Athird_ice_monster* thisMonster = Cast<Athird_ice_monster>(monster);
			if (thisMonster->sessionID == sc_monster_info_packet->sessionID) {
				thisMonster->Destroy();
			}
		}
		Athird_ice_monster* spawnMonster = GetWorld()->SpawnActor<Athird_ice_monster>(SpawnToThirdIceMonster, spawnLocation, spawnRotation, spawnParam);
		spawnMonster->sessionID = sc_monster_info_packet->sessionID;
		spawnMonster->hp = sc_monster_info_packet->hp;
		spawnMonster->max_hp = 400;
		if (spawnMonster->hp <= 0)
		{
			spawnMonster->Destroy();
		}
		break;
	}
	case MONSTER_TYPE::F_SAND:
	{
		TArray<AActor*> AllMonster;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Afirst_sand_monster::StaticClass(), AllMonster);
		for (auto& monster : AllMonster) {
			Afirst_sand_monster* thisMonster = Cast<Afirst_sand_monster>(monster);
			if (thisMonster->sessionID == sc_monster_info_packet->sessionID) {
				thisMonster->Destroy();
			}
		}
		Afirst_sand_monster* spawnMonster = GetWorld()->SpawnActor<Afirst_sand_monster>(SpawnToFirstSandMonster, spawnLocation, spawnRotation, spawnParam);
		spawnMonster->sessionID = sc_monster_info_packet->sessionID;
		spawnMonster->hp = sc_monster_info_packet->hp;
		spawnMonster->max_hp = 100;
		if (spawnMonster->hp <= 0)
		{
			spawnMonster->Destroy();
		}
		break;
	}
	case MONSTER_TYPE::S_SAND:
	{
		TArray<AActor*> AllMonster;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Asecond_sand_monster::StaticClass(), AllMonster);
		for (auto& monster : AllMonster) {
			Asecond_sand_monster* thisMonster = Cast<Asecond_sand_monster>(monster);
			if (thisMonster->sessionID == sc_monster_info_packet->sessionID) {
				thisMonster->Destroy();
			}
		}
		Asecond_sand_monster* spawnMonster = GetWorld()->SpawnActor<Asecond_sand_monster>(SpawnToSecondSandMonster, spawnLocation, spawnRotation, spawnParam);
		spawnMonster->sessionID = sc_monster_info_packet->sessionID;
		spawnMonster->hp = sc_monster_info_packet->hp;
		spawnMonster->max_hp = 200;
		if (spawnMonster->hp <= 0)
		{
			spawnMonster->Destroy();
		}
		break;
	}
	case MONSTER_TYPE::T_SAND:
	{
		TArray<AActor*> AllMonster;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Asecond_sand_monster::StaticClass(), AllMonster);
		for (auto& monster : AllMonster) {
			Asecond_sand_monster* thisMonster = Cast<Asecond_sand_monster>(monster);
			if (thisMonster->sessionID == sc_monster_info_packet->sessionID) {
				thisMonster->Destroy();
			}
		}
		Athird_sand_monster* spawnMonster = GetWorld()->SpawnActor<Athird_sand_monster>(SpawnToThirdSandMonster, spawnLocation, spawnRotation, spawnParam);
		spawnMonster->sessionID = sc_monster_info_packet->sessionID;
		spawnMonster->hp = sc_monster_info_packet->hp;
		spawnMonster->max_hp = 400;
		if (spawnMonster->hp <= 0)
		{
			spawnMonster->Destroy();
		}
		break;
	}
	case MONSTER_TYPE::F_WATER:
	{
		TArray<AActor*> AllMonster;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Afirst_water_monster::StaticClass(), AllMonster);
		for (auto& monster : AllMonster) {
			Afirst_water_monster* thisMonster = Cast<Afirst_water_monster>(monster);
			if (thisMonster->sessionID == sc_monster_info_packet->sessionID) {
				thisMonster->Destroy();
			}
		}
		Afirst_water_monster* spawnMonster = GetWorld()->SpawnActor<Afirst_water_monster>(SpawnToFirstWaterMonster, spawnLocation, spawnRotation, spawnParam);
		spawnMonster->sessionID = sc_monster_info_packet->sessionID;
		spawnMonster->hp = sc_monster_info_packet->hp;
		spawnMonster->max_hp = 100;
		if (spawnMonster->hp <= 0)
		{
			spawnMonster->Destroy();
		}
		break;
	}
	case MONSTER_TYPE::S_WATER:
	{
		TArray<AActor*> AllMonster;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Asecond_water_monster::StaticClass(), AllMonster);
		for (auto& monster : AllMonster) {
			Asecond_water_monster* thisMonster = Cast<Asecond_water_monster>(monster);
			if (thisMonster->sessionID == sc_monster_info_packet->sessionID) {
				thisMonster->Destroy();
			}
		}
		Asecond_water_monster* spawnMonster = GetWorld()->SpawnActor<Asecond_water_monster>(SpawnToSecondWaterMonster, spawnLocation, spawnRotation, spawnParam);
		spawnMonster->sessionID = sc_monster_info_packet->sessionID;
		spawnMonster->hp = sc_monster_info_packet->hp;
		spawnMonster->max_hp = 200;
		if (spawnMonster->hp <= 0)
		{
			spawnMonster->Destroy();
		}
		break;
	}
	case MONSTER_TYPE::T_WATER:
	{
		TArray<AActor*> AllMonster;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Athird_water_monster::StaticClass(), AllMonster);
		for (auto& monster : AllMonster) {
			Athird_water_monster* thisMonster = Cast<Athird_water_monster>(monster);
			if (thisMonster->sessionID == sc_monster_info_packet->sessionID) {
				thisMonster->Destroy();
			}
		}
		Athird_water_monster* spawnMonster = GetWorld()->SpawnActor<Athird_water_monster>(SpawnToThirdWaterMonster, spawnLocation, spawnRotation, spawnParam);
		spawnMonster->sessionID = sc_monster_info_packet->sessionID;
		spawnMonster->hp = sc_monster_info_packet->hp;
		spawnMonster->max_hp = 400;
		if (spawnMonster->hp <= 0)
		{
			spawnMonster->Destroy();
		}
		break;
	}
	case MONSTER_TYPE::F_FISH:
	{
		TArray<AActor*> AllMonster;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Afirst_swimming_monster::StaticClass(), AllMonster);
		for (auto& monster : AllMonster) {
			Afirst_swimming_monster* thisMonster = Cast<Afirst_swimming_monster>(monster);
			if (thisMonster->sessionID == sc_monster_info_packet->sessionID) {
				thisMonster->Destroy();
			}
		}
		Afirst_swimming_monster* spawnMonster = GetWorld()->SpawnActor<Afirst_swimming_monster>(SpawnToFirstFishMonster, spawnLocation, spawnRotation, spawnParam);
		spawnMonster->sessionID = sc_monster_info_packet->sessionID;
		spawnMonster->hp = sc_monster_info_packet->hp;
		spawnMonster->max_hp = 100;
		if (spawnMonster->hp <= 0)
		{
			spawnMonster->Destroy();
		}
		break;
	}
	case MONSTER_TYPE::S_FISH:
	{
		TArray<AActor*> AllMonster;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Asecond_swimming_monster::StaticClass(), AllMonster);
		for (auto& monster : AllMonster) {
			Asecond_swimming_monster* thisMonster = Cast<Asecond_swimming_monster>(monster);
			if (thisMonster->sessionID == sc_monster_info_packet->sessionID) {
				thisMonster->Destroy();
			}
		}
		Asecond_swimming_monster* spawnMonster = GetWorld()->SpawnActor<Asecond_swimming_monster>(SpawnToSecondFishMonster, spawnLocation, spawnRotation, spawnParam);
		spawnMonster->sessionID = sc_monster_info_packet->sessionID;
		spawnMonster->hp = sc_monster_info_packet->hp;
		spawnMonster->max_hp = 200;
		if (spawnMonster->hp <= 0)
		{
			spawnMonster->Destroy();
		}
		break;
	}
	case MONSTER_TYPE::T_FISH:
	{
		TArray<AActor*> AllMonster;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Athird_swimming_monster::StaticClass(), AllMonster);
		for (auto& monster : AllMonster) {
			Athird_swimming_monster* thisMonster = Cast<Athird_swimming_monster>(monster);
			if (thisMonster->sessionID == sc_monster_info_packet->sessionID) {
				thisMonster->Destroy();
			}
		}
		Athird_swimming_monster* spawnMonster = GetWorld()->SpawnActor<Athird_swimming_monster>(SpawnToThirdFishMonster, spawnLocation, spawnRotation, spawnParam);
		spawnMonster->sessionID = sc_monster_info_packet->sessionID;
		spawnMonster->hp = sc_monster_info_packet->hp;
		spawnMonster->max_hp = 400;
		if (spawnMonster->hp <= 0)
		{
			spawnMonster->Destroy();
		}
		break;
	}
	default:
		break;
	}
	delete sc_monster_info_packet;
	sc_monster_info_state = false;
}

void AMainGamePlayerController::MonsterMoveProcess()
{
	FVector spawnLocation;
	spawnLocation.X = sc_move_monster_packet->x;
	spawnLocation.Y = sc_move_monster_packet->y;
	spawnLocation.Z = sc_move_monster_packet->z;

	FRotator spawnRotation;
	spawnRotation.Pitch = sc_move_monster_packet->pitch;
	spawnRotation.Yaw = sc_move_monster_packet->yaw;
	spawnRotation.Roll = sc_move_monster_packet->roll;

	FActorSpawnParameters spawnParam;
	spawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	switch (sc_move_monster_packet->monsterType)
	{
	case MONSTER_TYPE::F_ICE:
	{
		bool bexist = false;
		TArray<AActor*> AllMonster;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Afirst_ice_monster::StaticClass(), AllMonster);
		for (auto& monster : AllMonster) {
			Afirst_ice_monster* thisMonster = Cast<Afirst_ice_monster>(monster);
			if (sc_move_monster_packet->sessionID != thisMonster->sessionID) continue;
			thisMonster->MoveToLocation(FVector(sc_move_monster_packet->x, sc_move_monster_packet->y, sc_move_monster_packet->z), sc_move_monster_packet->yaw);
			bexist = true;
			break;
		}
		if(false == bexist){
			Afirst_ice_monster* spawnMonster = GetWorld()->SpawnActor<Afirst_ice_monster>(SpawnToFirstIceMonster, spawnLocation, spawnRotation, spawnParam);
			spawnMonster->sessionID = sc_move_monster_packet->sessionID;
			spawnMonster->hp = sc_move_monster_packet->hp;
			spawnMonster->max_hp = 100;
			if (spawnMonster->hp <= 0)
			{
				spawnMonster->Destroy();
			}
			else {
				spawnMonster->MoveToLocation(FVector(sc_move_monster_packet->x, sc_move_monster_packet->y, sc_move_monster_packet->z), sc_move_monster_packet->yaw);
			}
		}
		break;
	}
	case MONSTER_TYPE::S_ICE:
	{
		bool bexist = false;
		TArray<AActor*> AllMonster;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Asecond_ice_monster::StaticClass(), AllMonster);
		for (auto& monster : AllMonster) {
			Asecond_ice_monster* thisMonster = Cast<Asecond_ice_monster>(monster);
			if (sc_move_monster_packet->sessionID != thisMonster->sessionID) continue;
			thisMonster->MoveToLocation(FVector(sc_move_monster_packet->x, sc_move_monster_packet->y, sc_move_monster_packet->z), sc_move_monster_packet->yaw);
			bexist = true;
			break;
		}
		if (false == bexist) {
			Asecond_ice_monster* spawnMonster = GetWorld()->SpawnActor<Asecond_ice_monster>(SpawnToSecondIceMonster, spawnLocation, spawnRotation, spawnParam);
			spawnMonster->sessionID = sc_move_monster_packet->sessionID;
			spawnMonster->hp = sc_move_monster_packet->hp;
			spawnMonster->max_hp = 200;
			if (spawnMonster->hp <= 0)
			{
				spawnMonster->Destroy();
			}
			else {
				spawnMonster->MoveToLocation(FVector(sc_move_monster_packet->x, sc_move_monster_packet->y, sc_move_monster_packet->z), sc_move_monster_packet->yaw);
			}
		}
		break;
	}
	case MONSTER_TYPE::T_ICE:
	{
		bool bexist = false;
		TArray<AActor*> AllMonster;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Athird_ice_monster::StaticClass(), AllMonster);
		for (auto& monster : AllMonster) {
			Athird_ice_monster* thisMonster = Cast<Athird_ice_monster>(monster);
			if (sc_move_monster_packet->sessionID != thisMonster->sessionID) continue;
			thisMonster->MoveToLocation(FVector(sc_move_monster_packet->x, sc_move_monster_packet->y, sc_move_monster_packet->z), sc_move_monster_packet->yaw);
			bexist = true;
			break;
		}
		if (false == bexist) {
			Athird_ice_monster* spawnMonster = GetWorld()->SpawnActor<Athird_ice_monster>(SpawnToThirdIceMonster, spawnLocation, spawnRotation, spawnParam);
			spawnMonster->sessionID = sc_move_monster_packet->sessionID;
			spawnMonster->hp = sc_move_monster_packet->hp;
			spawnMonster->max_hp = 400;
			if (spawnMonster->hp <= 0)
			{
				spawnMonster->Destroy();
			}
			else {
				spawnMonster->MoveToLocation(FVector(sc_move_monster_packet->x, sc_move_monster_packet->y, sc_move_monster_packet->z), sc_move_monster_packet->yaw);
			}
		}
		break;
	}
	case MONSTER_TYPE::F_SAND:
	{
		bool bexist = false;
		TArray<AActor*> AllMonster;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Afirst_sand_monster::StaticClass(), AllMonster);
		for (auto& monster : AllMonster) {
			Afirst_sand_monster* thisMonster = Cast<Afirst_sand_monster>(monster);
			if (sc_move_monster_packet->sessionID != thisMonster->sessionID) continue;
			thisMonster->MoveToLocation(FVector(sc_move_monster_packet->x, sc_move_monster_packet->y, sc_move_monster_packet->z), sc_move_monster_packet->yaw);
			bexist = true;
			break;
		}
		if (false == bexist) {
			Afirst_sand_monster* spawnMonster = GetWorld()->SpawnActor<Afirst_sand_monster>(SpawnToFirstSandMonster, spawnLocation, spawnRotation, spawnParam);
			spawnMonster->sessionID = sc_move_monster_packet->sessionID;
			spawnMonster->hp = sc_move_monster_packet->hp;
			spawnMonster->max_hp = 100;
			if (spawnMonster->hp <= 0)
			{
				spawnMonster->Destroy();
			}
			else {
				spawnMonster->MoveToLocation(FVector(sc_move_monster_packet->x, sc_move_monster_packet->y, sc_move_monster_packet->z), sc_move_monster_packet->yaw);
			}
		}
		break;
	}
	case MONSTER_TYPE::S_SAND:
	{
		bool bexist = false;
		TArray<AActor*> AllMonster;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Asecond_sand_monster::StaticClass(), AllMonster);
		for (auto& monster : AllMonster) {
			Asecond_sand_monster* thisMonster = Cast<Asecond_sand_monster>(monster);
			if (sc_move_monster_packet->sessionID != thisMonster->sessionID) continue;
			thisMonster->MoveToLocation(FVector(sc_move_monster_packet->x, sc_move_monster_packet->y, sc_move_monster_packet->z), sc_move_monster_packet->yaw);
			bexist = true;
			break;
		}
		if (false == bexist) {
			Asecond_sand_monster* spawnMonster = GetWorld()->SpawnActor<Asecond_sand_monster>(SpawnToSecondSandMonster, spawnLocation, spawnRotation, spawnParam);
			spawnMonster->sessionID = sc_move_monster_packet->sessionID;
			spawnMonster->hp = sc_move_monster_packet->hp;
			spawnMonster->max_hp = 200;
			if (spawnMonster->hp <= 0)
			{
				spawnMonster->Destroy();
			}
			else {
				spawnMonster->MoveToLocation(FVector(sc_move_monster_packet->x, sc_move_monster_packet->y, sc_move_monster_packet->z), sc_move_monster_packet->yaw);
			}
		}
		break;
	}
	case MONSTER_TYPE::T_SAND:
	{
		bool bexist = false;
		TArray<AActor*> AllMonster;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Athird_sand_monster::StaticClass(), AllMonster);
		for (auto& monster : AllMonster) {
			Athird_sand_monster* thisMonster = Cast<Athird_sand_monster>(monster);
			if (sc_move_monster_packet->sessionID != thisMonster->sessionID) continue;
			thisMonster->MoveToLocation(FVector(sc_move_monster_packet->x, sc_move_monster_packet->y, sc_move_monster_packet->z), sc_move_monster_packet->yaw);
			bexist = true;
			break;
		}
		if (false == bexist) {
			Athird_sand_monster* spawnMonster = GetWorld()->SpawnActor<Athird_sand_monster>(SpawnToThirdSandMonster, spawnLocation, spawnRotation, spawnParam);
			spawnMonster->sessionID = sc_move_monster_packet->sessionID;
			spawnMonster->hp = sc_move_monster_packet->hp;
			spawnMonster->max_hp = 400;
			if (spawnMonster->hp <= 0)
			{
				spawnMonster->Destroy();
			}
			else {
				spawnMonster->MoveToLocation(FVector(sc_move_monster_packet->x, sc_move_monster_packet->y, sc_move_monster_packet->z), sc_move_monster_packet->yaw);
			}
		}
		break;
	}
	case MONSTER_TYPE::F_WATER:
	{
		bool bexist = false;
		TArray<AActor*> AllMonster;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Afirst_water_monster::StaticClass(), AllMonster);
		for (auto& monster : AllMonster) {
			Afirst_water_monster* thisMonster = Cast<Afirst_water_monster>(monster);
			if (sc_move_monster_packet->sessionID != thisMonster->sessionID) continue;
			thisMonster->MoveToLocation(FVector(sc_move_monster_packet->x, sc_move_monster_packet->y, sc_move_monster_packet->z), sc_move_monster_packet->yaw);
			bexist = true;
			break;
		}
		if (false == bexist) {
			Afirst_water_monster* spawnMonster = GetWorld()->SpawnActor<Afirst_water_monster>(SpawnToFirstWaterMonster, spawnLocation, spawnRotation, spawnParam);
			spawnMonster->sessionID = sc_move_monster_packet->sessionID;
			spawnMonster->hp = sc_move_monster_packet->hp;
			spawnMonster->max_hp = 100;
			if (spawnMonster->hp <= 0)
			{
				spawnMonster->Destroy();
			}
			else {
				spawnMonster->MoveToLocation(FVector(sc_move_monster_packet->x, sc_move_monster_packet->y, sc_move_monster_packet->z), sc_move_monster_packet->yaw);
			}
		}
		break;
	}
	case MONSTER_TYPE::S_WATER:
	{
		bool bexist = false;
		TArray<AActor*> AllMonster;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Asecond_water_monster::StaticClass(), AllMonster);
		for (auto& monster : AllMonster) {
			Asecond_water_monster* thisMonster = Cast<Asecond_water_monster>(monster);
			if (sc_move_monster_packet->sessionID != thisMonster->sessionID) continue;
			thisMonster->MoveToLocation(FVector(sc_move_monster_packet->x, sc_move_monster_packet->y, sc_move_monster_packet->z), sc_move_monster_packet->yaw);
			bexist = true;
			break;
		}
		if (false == bexist) {
			Asecond_water_monster* spawnMonster = GetWorld()->SpawnActor<Asecond_water_monster>(SpawnToSecondWaterMonster, spawnLocation, spawnRotation, spawnParam);
			spawnMonster->sessionID = sc_move_monster_packet->sessionID;
			spawnMonster->hp = sc_move_monster_packet->hp;
			spawnMonster->max_hp = 200;
			if (spawnMonster->hp <= 0)
			{
				spawnMonster->Destroy();
			}
			else {
				spawnMonster->MoveToLocation(FVector(sc_move_monster_packet->x, sc_move_monster_packet->y, sc_move_monster_packet->z), sc_move_monster_packet->yaw);
			}
		}
		break;
	}
	case MONSTER_TYPE::T_WATER:
	{
		bool bexist = false;
		TArray<AActor*> AllMonster;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Athird_water_monster::StaticClass(), AllMonster);
		for (auto& monster : AllMonster) {
			Athird_water_monster* thisMonster = Cast<Athird_water_monster>(monster);
			if (sc_move_monster_packet->sessionID != thisMonster->sessionID) continue;
			thisMonster->MoveToLocation(FVector(sc_move_monster_packet->x, sc_move_monster_packet->y, sc_move_monster_packet->z), sc_move_monster_packet->yaw);
			bexist = true;
			break;
		}
		if (false == bexist) {
			Athird_water_monster* spawnMonster = GetWorld()->SpawnActor<Athird_water_monster>(SpawnToThirdWaterMonster, spawnLocation, spawnRotation, spawnParam);
			spawnMonster->sessionID = sc_move_monster_packet->sessionID;
			spawnMonster->hp = sc_move_monster_packet->hp;
			spawnMonster->max_hp = 400;
			if (spawnMonster->hp <= 0)
			{
				spawnMonster->Destroy();
			}
			else {
				spawnMonster->MoveToLocation(FVector(sc_move_monster_packet->x, sc_move_monster_packet->y, sc_move_monster_packet->z), sc_move_monster_packet->yaw);
			}
		}
		break;
	}
	case MONSTER_TYPE::F_FISH:
	{
		bool bexist = false;
		TArray<AActor*> AllMonster;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Afirst_swimming_monster::StaticClass(), AllMonster);
		for (auto& monster : AllMonster) {
			Afirst_swimming_monster* thisMonster = Cast<Afirst_swimming_monster>(monster);
			if (sc_move_monster_packet->sessionID != thisMonster->sessionID) continue;
			thisMonster->MoveToLocation(FVector(sc_move_monster_packet->x, sc_move_monster_packet->y, sc_move_monster_packet->z), spawnRotation);
			bexist = true;
			break;
		}
		if (false == bexist) {
			Afirst_swimming_monster* spawnMonster = GetWorld()->SpawnActor<Afirst_swimming_monster>(SpawnToFirstFishMonster, spawnLocation, spawnRotation, spawnParam);
			spawnMonster->sessionID = sc_move_monster_packet->sessionID;
			spawnMonster->hp = sc_move_monster_packet->hp;
			spawnMonster->max_hp = 100;
			if (spawnMonster->hp <= 0)
			{
				spawnMonster->Destroy();
			}
			else {
				spawnMonster->MoveToLocation(FVector(sc_move_monster_packet->x, sc_move_monster_packet->y, sc_move_monster_packet->z), spawnRotation);
			}
		}
		break;
	}
	case MONSTER_TYPE::S_FISH:
	{
		bool bexist = false;
		TArray<AActor*> AllMonster;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Asecond_swimming_monster::StaticClass(), AllMonster);
		for (auto& monster : AllMonster) {
			Asecond_swimming_monster* thisMonster = Cast<Asecond_swimming_monster>(monster);
			if (sc_move_monster_packet->sessionID != thisMonster->sessionID) continue;
			thisMonster->MoveToLocation(FVector(sc_move_monster_packet->x, sc_move_monster_packet->y, sc_move_monster_packet->z), spawnRotation);
			bexist = true;
			break;
		}
		if (false == bexist) {
			Asecond_swimming_monster* spawnMonster = GetWorld()->SpawnActor<Asecond_swimming_monster>(SpawnToSecondFishMonster, spawnLocation, spawnRotation, spawnParam);
			spawnMonster->sessionID = sc_move_monster_packet->sessionID;
			spawnMonster->hp = sc_move_monster_packet->hp;
			spawnMonster->max_hp = 200;
			if (spawnMonster->hp <= 0)
			{
				spawnMonster->Destroy();
			}
			else {
				spawnMonster->MoveToLocation(FVector(sc_move_monster_packet->x, sc_move_monster_packet->y, sc_move_monster_packet->z), spawnRotation);
			}
		}
		break;
	}
	case MONSTER_TYPE::T_FISH:
	{
		bool bexist = false;
		TArray<AActor*> AllMonster;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Athird_swimming_monster::StaticClass(), AllMonster);
		for (auto& monster : AllMonster) {
			Athird_swimming_monster* thisMonster = Cast<Athird_swimming_monster>(monster);
			if (sc_move_monster_packet->sessionID != thisMonster->sessionID) continue;
			thisMonster->MoveToLocation(FVector(sc_move_monster_packet->x, sc_move_monster_packet->y, sc_move_monster_packet->z), spawnRotation);
			bexist = true;
			break;
		}
		if (false == bexist) {
			Athird_swimming_monster* spawnMonster = GetWorld()->SpawnActor<Athird_swimming_monster>(SpawnToThirdFishMonster, spawnLocation, spawnRotation, spawnParam);
			spawnMonster->sessionID = sc_move_monster_packet->sessionID;
			spawnMonster->hp = sc_move_monster_packet->hp;
			spawnMonster->max_hp = 400;
			if (spawnMonster->hp <= 0)
			{
				spawnMonster->Destroy();
			}
			else {
				spawnMonster->MoveToLocation(FVector(sc_move_monster_packet->x, sc_move_monster_packet->y, sc_move_monster_packet->z), spawnRotation);
			}
		}
		break;
	}
	default:
		break;
	}
	delete sc_move_monster_packet;
	sc_move_monster_state = false;
}

void AMainGamePlayerController::RemoveMonsterProcess()
{
	TArray<AActor*> AllMonsters;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), Amonster::StaticClass(), AllMonsters);
	for (auto& monster : AllMonsters) {
		Amonster* thisMonster = Cast<Amonster>(monster);
		if (sc_remove_monster_packet->sessionID != thisMonster->sessionID) continue;
		thisMonster->Destroy();
		break;
	}
	delete sc_remove_monster_packet;
	sc_remove_monster_state = false;
}

void AMainGamePlayerController::AttackMonsterProcess()
{
	FVector spawnLocation;
	spawnLocation.X = sc_attack_monster_packet->x;
	spawnLocation.Y = sc_attack_monster_packet->y;
	spawnLocation.Z = sc_attack_monster_packet->z;

	FRotator spawnRotation;
	spawnRotation.Pitch = 0;
	spawnRotation.Yaw = 0;
	spawnRotation.Roll = 0;

	FActorSpawnParameters spawnParam;
	spawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	switch (sc_attack_monster_packet->monsterType)
	{
	case MONSTER_TYPE::F_ICE:
	{
		bool bexist = false;
		TArray<AActor*> AllMonster;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Afirst_ice_monster::StaticClass(), AllMonster);
		for (auto& monster : AllMonster) {
			Afirst_ice_monster* thisMonster = Cast<Afirst_ice_monster>(monster);
			if (sc_attack_monster_packet->sessionID != thisMonster->sessionID) continue;
			short target = sc_attack_monster_packet->targetID;
			FVector target_loc = FVector(sc_attack_monster_packet->x, sc_attack_monster_packet->y, sc_attack_monster_packet->z);
			switch (sc_attack_monster_packet->attack_type)
			{
			case MONSTER_ATTACK_TYPE::NORMAL:
				thisMonster->PlayAttack(target, target_loc);
				break;
			case MONSTER_ATTACK_TYPE::SKILL:
				break;
			}
			bexist = true;
			break;
		}
		if (false == bexist) {
			Afirst_ice_monster* spawnMonster = GetWorld()->SpawnActor<Afirst_ice_monster>(SpawnToFirstIceMonster, spawnLocation, spawnRotation, spawnParam);
			spawnMonster->sessionID = sc_attack_monster_packet->sessionID;
			spawnMonster->hp = sc_attack_monster_packet->hp;
			spawnMonster->max_hp = 100;
			if (spawnMonster->hp <= 0)
			{
				spawnMonster->Destroy();
			}
			else {
				short target = sc_attack_monster_packet->targetID;
				FVector target_loc = FVector(sc_attack_monster_packet->x, sc_attack_monster_packet->y, sc_attack_monster_packet->z);
				switch (sc_attack_monster_packet->attack_type)
				{
				case MONSTER_ATTACK_TYPE::NORMAL:
					spawnMonster->PlayAttack(target, target_loc);
					break;
				case MONSTER_ATTACK_TYPE::SKILL:
					break;
				}
			}
		}
		break;
	}
	case MONSTER_TYPE::S_ICE:
	{
		bool bexist = false;
		TArray<AActor*> AllMonster;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Asecond_ice_monster::StaticClass(), AllMonster);
		for (auto& monster : AllMonster) {
			Asecond_ice_monster* thisMonster = Cast<Asecond_ice_monster>(monster);
			if (sc_attack_monster_packet->sessionID != thisMonster->sessionID) continue;
			short target = sc_attack_monster_packet->targetID;
			FVector target_loc = FVector(sc_attack_monster_packet->x, sc_attack_monster_packet->y, sc_attack_monster_packet->z);
			switch (sc_attack_monster_packet->attack_type)
			{
			case MONSTER_ATTACK_TYPE::NORMAL:
				thisMonster->PlayAttack(target, target_loc);
				break;
			case MONSTER_ATTACK_TYPE::SKILL:
				break;
			}
			bexist = true;
			break;
		}
		if (false == bexist) {
			Asecond_ice_monster* spawnMonster = GetWorld()->SpawnActor<Asecond_ice_monster>(SpawnToSecondIceMonster, spawnLocation, spawnRotation, spawnParam);
			spawnMonster->sessionID = sc_attack_monster_packet->sessionID;
			spawnMonster->hp = sc_attack_monster_packet->hp;
			spawnMonster->max_hp = 200;
			if (spawnMonster->hp <= 0)
			{
				spawnMonster->Destroy();
			}
			else {
				short target = sc_attack_monster_packet->targetID;
				FVector target_loc = FVector(sc_attack_monster_packet->x, sc_attack_monster_packet->y, sc_attack_monster_packet->z);
				switch (sc_attack_monster_packet->attack_type)
				{
				case MONSTER_ATTACK_TYPE::NORMAL:
					spawnMonster->PlayAttack(target, target_loc);
					break;
				case MONSTER_ATTACK_TYPE::SKILL:
					break;
				}
			}
		}
		break;
	}
	case MONSTER_TYPE::T_ICE:
	{
		bool bexist = false;
		TArray<AActor*> AllMonster;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Athird_ice_monster::StaticClass(), AllMonster);
		for (auto& monster : AllMonster) {
			Athird_ice_monster* thisMonster = Cast<Athird_ice_monster>(monster);
			if (sc_attack_monster_packet->sessionID != thisMonster->sessionID) continue;
			short target = sc_attack_monster_packet->targetID;
			FVector target_loc = FVector(sc_attack_monster_packet->x, sc_attack_monster_packet->y, sc_attack_monster_packet->z);
			switch (sc_attack_monster_packet->attack_type)
			{
			case MONSTER_ATTACK_TYPE::NORMAL:
				thisMonster->PlayAttack(target, target_loc);
				break;
			case MONSTER_ATTACK_TYPE::SKILL:
				thisMonster->PlaySkill(target, target_loc);
				break;
			}
			bexist = true;
			break;
		}
		if (false == bexist) {
			Athird_ice_monster* spawnMonster = GetWorld()->SpawnActor<Athird_ice_monster>(SpawnToThirdIceMonster, spawnLocation, spawnRotation, spawnParam);
			spawnMonster->sessionID = sc_attack_monster_packet->sessionID;
			spawnMonster->hp = sc_attack_monster_packet->hp;
			spawnMonster->max_hp = 400;
			if (spawnMonster->hp <= 0)
			{
				spawnMonster->Destroy();
			}
			else {
				short target = sc_attack_monster_packet->targetID;
				FVector target_loc = FVector(sc_attack_monster_packet->x, sc_attack_monster_packet->y, sc_attack_monster_packet->z);
				switch (sc_attack_monster_packet->attack_type)
				{
				case MONSTER_ATTACK_TYPE::NORMAL:
					spawnMonster->PlayAttack(target, target_loc);
					break;
				case MONSTER_ATTACK_TYPE::SKILL:
					spawnMonster->PlaySkill(target, target_loc);
					break;
				}
			}
		}
		break;
	}
	case MONSTER_TYPE::F_SAND:
	{
		bool bexist = false;
		TArray<AActor*> AllMonster;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Afirst_sand_monster::StaticClass(), AllMonster);
		for (auto& monster : AllMonster) {
			Afirst_sand_monster* thisMonster = Cast<Afirst_sand_monster>(monster);
			if (sc_attack_monster_packet->sessionID != thisMonster->sessionID) continue; 
			short target = sc_attack_monster_packet->targetID;
			FVector target_loc = FVector(sc_attack_monster_packet->x, sc_attack_monster_packet->y, sc_attack_monster_packet->z);
			switch (sc_attack_monster_packet->attack_type)
			{
			case MONSTER_ATTACK_TYPE::NORMAL:
				thisMonster->PlayAttack(target, target_loc);
				break;
			case MONSTER_ATTACK_TYPE::SKILL:
				break;
			}
			bexist = true;
			break;
		}
		if (false == bexist) {
			Afirst_sand_monster* spawnMonster = GetWorld()->SpawnActor<Afirst_sand_monster>(SpawnToFirstSandMonster, spawnLocation, spawnRotation, spawnParam);
			spawnMonster->sessionID = sc_attack_monster_packet->sessionID;
			spawnMonster->hp = sc_attack_monster_packet->hp;
			spawnMonster->max_hp = 100;
			if (spawnMonster->hp <= 0)
			{
				spawnMonster->Destroy();
			}
			else {
				short target = sc_attack_monster_packet->targetID;
				FVector target_loc = FVector(sc_attack_monster_packet->x, sc_attack_monster_packet->y, sc_attack_monster_packet->z);
				switch (sc_attack_monster_packet->attack_type)
				{
				case MONSTER_ATTACK_TYPE::NORMAL:
					spawnMonster->PlayAttack(target, target_loc);
					break;
				case MONSTER_ATTACK_TYPE::SKILL:
					break;
				}
			}
		}
		break;
	}
	case MONSTER_TYPE::S_SAND:
	{
		bool bexist = false;
		TArray<AActor*> AllMonster;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Asecond_sand_monster::StaticClass(), AllMonster);
		for (auto& monster : AllMonster) {
			Asecond_sand_monster* thisMonster = Cast<Asecond_sand_monster>(monster);
			if (sc_attack_monster_packet->sessionID != thisMonster->sessionID) break;
			short target = sc_attack_monster_packet->targetID;
			FVector target_loc = FVector(sc_attack_monster_packet->x, sc_attack_monster_packet->y, sc_attack_monster_packet->z);
			switch (sc_attack_monster_packet->attack_type)
			{
			case MONSTER_ATTACK_TYPE::NORMAL:
				thisMonster->PlayAttack(target, target_loc);
				break;
			case MONSTER_ATTACK_TYPE::SKILL:
				break;
			}
			bexist = true;
			break;
		}
		if (false == bexist) {
			Asecond_sand_monster* spawnMonster = GetWorld()->SpawnActor<Asecond_sand_monster>(SpawnToSecondSandMonster, spawnLocation, spawnRotation, spawnParam);
			spawnMonster->sessionID = sc_attack_monster_packet->sessionID;
			spawnMonster->hp = sc_attack_monster_packet->hp;
			spawnMonster->max_hp = 200;
			if (spawnMonster->hp <= 0)
			{
				spawnMonster->Destroy();
			}
			else {
				short target = sc_attack_monster_packet->targetID;
				FVector target_loc = FVector(sc_attack_monster_packet->x, sc_attack_monster_packet->y, sc_attack_monster_packet->z);
				switch (sc_attack_monster_packet->attack_type)
				{
				case MONSTER_ATTACK_TYPE::NORMAL:
					spawnMonster->PlayAttack(target, target_loc);
					break;
				case MONSTER_ATTACK_TYPE::SKILL:
					break;
				}
			}
		}
		break;
	}
	case MONSTER_TYPE::T_SAND:
	{
		bool bexist = false;
		TArray<AActor*> AllMonster;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Athird_sand_monster::StaticClass(), AllMonster);
		for (auto& monster : AllMonster) {
			Athird_sand_monster* thisMonster = Cast<Athird_sand_monster>(monster);
			if (sc_attack_monster_packet->sessionID != thisMonster->sessionID) continue;
			short target = sc_attack_monster_packet->targetID;
			FVector target_loc = FVector(sc_attack_monster_packet->x, sc_attack_monster_packet->y, sc_attack_monster_packet->z);
			switch (sc_attack_monster_packet->attack_type)
			{
			case MONSTER_ATTACK_TYPE::NORMAL:
				thisMonster->PlayAttack(target, target_loc);
				break;
			case MONSTER_ATTACK_TYPE::SKILL:
				thisMonster->PlaySkill(target, target_loc);
				break;
			}
			bexist = true;
			break;
		}
		if (false == bexist) {
			Athird_sand_monster* spawnMonster = GetWorld()->SpawnActor<Athird_sand_monster>(SpawnToThirdSandMonster, spawnLocation, spawnRotation, spawnParam);
			spawnMonster->sessionID = sc_attack_monster_packet->sessionID;
			spawnMonster->hp = sc_attack_monster_packet->hp;
			spawnMonster->max_hp = 400;
			if (spawnMonster->hp <= 0)
			{
				spawnMonster->Destroy();
			}
			else {
				short target = sc_attack_monster_packet->targetID;
				FVector target_loc = FVector(sc_attack_monster_packet->x, sc_attack_monster_packet->y, sc_attack_monster_packet->z);
				switch (sc_attack_monster_packet->attack_type)
				{
				case MONSTER_ATTACK_TYPE::NORMAL:
					spawnMonster->PlayAttack(target, target_loc);
					break;
				case MONSTER_ATTACK_TYPE::SKILL:
					spawnMonster->PlaySkill(target, target_loc);
					break;
				}
			}
		}
		break;
	}
	case MONSTER_TYPE::F_WATER:
	{
		bool bexist = false;
		TArray<AActor*> AllMonster;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Afirst_water_monster::StaticClass(), AllMonster);
		for (auto& monster : AllMonster) {
			Afirst_water_monster* thisMonster = Cast<Afirst_water_monster>(monster);
			if (sc_attack_monster_packet->sessionID != thisMonster->sessionID) continue;
			short target = sc_attack_monster_packet->targetID;
			FVector target_loc = FVector(sc_attack_monster_packet->x, sc_attack_monster_packet->y, sc_attack_monster_packet->z);
			switch (sc_attack_monster_packet->attack_type)
			{
			case MONSTER_ATTACK_TYPE::NORMAL:
				thisMonster->PlayAttack(target, target_loc);
				break;
			case MONSTER_ATTACK_TYPE::SKILL:
				break;
			}
			bexist = true;
			break;
		}
		if (false == bexist) {
			Afirst_water_monster* spawnMonster = GetWorld()->SpawnActor<Afirst_water_monster>(SpawnToFirstWaterMonster, spawnLocation, spawnRotation, spawnParam);
			spawnMonster->sessionID = sc_attack_monster_packet->sessionID;
			spawnMonster->hp = sc_attack_monster_packet->hp;
			spawnMonster->max_hp = 100;
			if (spawnMonster->hp <= 0)
			{
				spawnMonster->Destroy();
			}
			else {
				short target = sc_attack_monster_packet->targetID;
				FVector target_loc = FVector(sc_attack_monster_packet->x, sc_attack_monster_packet->y, sc_attack_monster_packet->z);
				switch (sc_attack_monster_packet->attack_type)
				{
				case MONSTER_ATTACK_TYPE::NORMAL:
					spawnMonster->PlayAttack(target, target_loc);
					break;
				case MONSTER_ATTACK_TYPE::SKILL:
					break;
				}
			}
		}
		break;
	}
	case MONSTER_TYPE::S_WATER:
	{
		bool bexist = false;
		TArray<AActor*> AllMonster;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Asecond_water_monster::StaticClass(), AllMonster);
		for (auto& monster : AllMonster) {
			Asecond_water_monster* thisMonster = Cast<Asecond_water_monster>(monster);
			if (sc_attack_monster_packet->sessionID != thisMonster->sessionID) continue;
			short target = sc_attack_monster_packet->targetID;
			FVector target_loc = FVector(sc_attack_monster_packet->x, sc_attack_monster_packet->y, sc_attack_monster_packet->z);
			switch (sc_attack_monster_packet->attack_type)
			{
			case MONSTER_ATTACK_TYPE::NORMAL:
				thisMonster->PlayAttack(target, target_loc);
				break;
			case MONSTER_ATTACK_TYPE::SKILL:
				break;
			}
			bexist = true;
			break;
		}
		if (false == bexist) {
			Asecond_water_monster* spawnMonster = GetWorld()->SpawnActor<Asecond_water_monster>(SpawnToSecondWaterMonster, spawnLocation, spawnRotation, spawnParam);
			spawnMonster->sessionID = sc_attack_monster_packet->sessionID;
			spawnMonster->hp = sc_attack_monster_packet->hp;
			spawnMonster->max_hp = 200;
			if (spawnMonster->hp <= 0)
			{
				spawnMonster->Destroy();
			}
			else {
				short target = sc_attack_monster_packet->targetID;
				FVector target_loc = FVector(sc_attack_monster_packet->x, sc_attack_monster_packet->y, sc_attack_monster_packet->z);
				switch (sc_attack_monster_packet->attack_type)
				{
				case MONSTER_ATTACK_TYPE::NORMAL:
					spawnMonster->PlayAttack(target, target_loc);
					break;
				case MONSTER_ATTACK_TYPE::SKILL:
					break;
				}
			}
		}
		break;
	}
	case MONSTER_TYPE::T_WATER:
	{
		bool bexist = false;
		TArray<AActor*> AllMonster;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Athird_water_monster::StaticClass(), AllMonster);
		for (auto& monster : AllMonster) {
			Athird_water_monster* thisMonster = Cast<Athird_water_monster>(monster);
			if (sc_attack_monster_packet->sessionID != thisMonster->sessionID) continue;
			short target = sc_attack_monster_packet->targetID;
			FVector target_loc = FVector(sc_attack_monster_packet->x, sc_attack_monster_packet->y, sc_attack_monster_packet->z);
			switch (sc_attack_monster_packet->attack_type)
			{
			case MONSTER_ATTACK_TYPE::NORMAL:
				thisMonster->PlayAttack(target, target_loc);
				break;
			case MONSTER_ATTACK_TYPE::SKILL:
				thisMonster->PlaySkill(target, target_loc);
				break;
			}
			bexist = true;
			break;
		}
		if (false == bexist) {
			Athird_water_monster* spawnMonster = GetWorld()->SpawnActor<Athird_water_monster>(SpawnToThirdWaterMonster, spawnLocation, spawnRotation, spawnParam);
			spawnMonster->sessionID = sc_attack_monster_packet->sessionID;
			spawnMonster->hp = sc_attack_monster_packet->hp;
			spawnMonster->max_hp = 400;
			if (spawnMonster->hp <= 0)
			{
				spawnMonster->Destroy();
			}
			else {
				short target = sc_attack_monster_packet->targetID;
				FVector target_loc = FVector(sc_attack_monster_packet->x, sc_attack_monster_packet->y, sc_attack_monster_packet->z);
				switch (sc_attack_monster_packet->attack_type)
				{
				case MONSTER_ATTACK_TYPE::NORMAL:
					spawnMonster->PlayAttack(target, target_loc);
					break;
				case MONSTER_ATTACK_TYPE::SKILL:
					spawnMonster->PlaySkill(target, target_loc);
					break;
				}
			}
		}
		break;
	}
	case MONSTER_TYPE::F_FISH:
	{
		bool bexist = false;
		TArray<AActor*> AllMonster;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Afirst_swimming_monster::StaticClass(), AllMonster);
		for (auto& monster : AllMonster) {
			Afirst_swimming_monster* thisMonster = Cast<Afirst_swimming_monster>(monster);
			if (sc_attack_monster_packet->sessionID != thisMonster->sessionID) continue;
			short target = sc_attack_monster_packet->targetID;
			FVector target_loc = FVector(sc_attack_monster_packet->x, sc_attack_monster_packet->y, sc_attack_monster_packet->z);
			switch (sc_attack_monster_packet->attack_type)
			{
			case MONSTER_ATTACK_TYPE::NORMAL:
				thisMonster->PlayAttack(target, target_loc);
				break;
			case MONSTER_ATTACK_TYPE::SKILL:
				break;
			}
			bexist = true;
			break;
		}
		if (false == bexist) {
			Afirst_swimming_monster* spawnMonster = GetWorld()->SpawnActor<Afirst_swimming_monster>(SpawnToFirstFishMonster, spawnLocation, spawnRotation, spawnParam);
			spawnMonster->sessionID = sc_attack_monster_packet->sessionID;
			spawnMonster->hp = sc_attack_monster_packet->hp;
			spawnMonster->max_hp = 100;
			if (spawnMonster->hp <= 0)
			{
				spawnMonster->Destroy();
			}
			else {
				short target = sc_attack_monster_packet->targetID;
				FVector target_loc = FVector(sc_attack_monster_packet->x, sc_attack_monster_packet->y, sc_attack_monster_packet->z);
				switch (sc_attack_monster_packet->attack_type)
				{
				case MONSTER_ATTACK_TYPE::NORMAL:
					spawnMonster->PlayAttack(target, target_loc);
					break;
				case MONSTER_ATTACK_TYPE::SKILL:
					break;
				}
			}
		}
		break;
	}
	case MONSTER_TYPE::S_FISH:
	{
		bool bexist = false;
		TArray<AActor*> AllMonster;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Asecond_swimming_monster::StaticClass(), AllMonster);
		for (auto& monster : AllMonster) {
			Asecond_swimming_monster* thisMonster = Cast<Asecond_swimming_monster>(monster);
			if (sc_attack_monster_packet->sessionID != thisMonster->sessionID) continue;
			short target = sc_attack_monster_packet->targetID;
			FVector target_loc = FVector(sc_attack_monster_packet->x, sc_attack_monster_packet->y, sc_attack_monster_packet->z);
			switch (sc_attack_monster_packet->attack_type)
			{
			case MONSTER_ATTACK_TYPE::NORMAL:
				thisMonster->PlayAttack(target, target_loc);
				break;
			case MONSTER_ATTACK_TYPE::SKILL:
				break;
			}
			bexist = true;
			break;
		}
		if (false == bexist) {
			Asecond_swimming_monster* spawnMonster = GetWorld()->SpawnActor<Asecond_swimming_monster>(SpawnToSecondFishMonster, spawnLocation, spawnRotation, spawnParam);
			spawnMonster->sessionID = sc_attack_monster_packet->sessionID;
			spawnMonster->hp = sc_attack_monster_packet->hp;
			spawnMonster->max_hp = 200;
			if (spawnMonster->hp <= 0)
			{
				spawnMonster->Destroy();
			}
			else {
				short target = sc_attack_monster_packet->targetID;
				FVector target_loc = FVector(sc_attack_monster_packet->x, sc_attack_monster_packet->y, sc_attack_monster_packet->z);
				switch (sc_attack_monster_packet->attack_type)
				{
				case MONSTER_ATTACK_TYPE::NORMAL:
					spawnMonster->PlayAttack(target, target_loc);
					break;
				case MONSTER_ATTACK_TYPE::SKILL:
					break;
				}
			}
		}
		break;
	}
	case MONSTER_TYPE::T_FISH:
	{
		bool bexist = false;
		TArray<AActor*> AllMonster;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Athird_swimming_monster::StaticClass(), AllMonster);
		for (auto& monster : AllMonster) {
			Athird_swimming_monster* thisMonster = Cast<Athird_swimming_monster>(monster);
			if (sc_attack_monster_packet->sessionID != thisMonster->sessionID) continue;
			short target = sc_attack_monster_packet->targetID;
			FVector target_loc = FVector(sc_attack_monster_packet->x, sc_attack_monster_packet->y, sc_attack_monster_packet->z);
			switch (sc_attack_monster_packet->attack_type)
			{
			case MONSTER_ATTACK_TYPE::NORMAL:
				thisMonster->PlayAttack(target, target_loc);
				break;
			case MONSTER_ATTACK_TYPE::SKILL:
				thisMonster->PlaySkill(target, target_loc);
				break;
			}
			bexist = true;
			break;
		}
		if (false == bexist) {
			Athird_swimming_monster* spawnMonster = GetWorld()->SpawnActor<Athird_swimming_monster>(SpawnToThirdFishMonster, spawnLocation, spawnRotation, spawnParam);
			spawnMonster->sessionID = sc_attack_monster_packet->sessionID;
			spawnMonster->hp = sc_attack_monster_packet->hp;
			spawnMonster->max_hp = 400;
			if (spawnMonster->hp <= 0)
			{
				spawnMonster->Destroy();
			}
			else {
				short target = sc_attack_monster_packet->targetID;
				FVector target_loc = FVector(sc_attack_monster_packet->x, sc_attack_monster_packet->y, sc_attack_monster_packet->z);
				switch (sc_attack_monster_packet->attack_type)
				{
				case MONSTER_ATTACK_TYPE::NORMAL:
					spawnMonster->PlayAttack(target, target_loc);
					break;
				case MONSTER_ATTACK_TYPE::SKILL:
					spawnMonster->PlaySkill(target, target_loc);
					break;
				}
			}
		}
		break;
	}
	default:
		break;
	}
	delete sc_attack_monster_packet;
	sc_attack_monster_state = false;
}

void AMainGamePlayerController::ChangeCharaterProcess()
{
	switch (sc_change_character_packet->character_type)
	{
	case CHARACTER_TYPE::HUMAN:
	{
		bool was_ship_added = false;
		TArray<AActor*> ALLShip;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Aspace_ship::StaticClass(), ALLShip);
		for (auto& player : ALLShip) {
			Aspace_ship* thisShip = Cast<Aspace_ship>(player);
			if (sc_change_character_packet->sessionID != thisShip->owner_session_id) continue;
			was_ship_added = true;
			break;
		}
		if (was_ship_added == false)
		{
			FVector spawnLocation;
			spawnLocation.X = sc_change_character_packet->x;
			spawnLocation.Y = sc_change_character_packet->y;
			spawnLocation.Z = sc_change_character_packet->z;

			FRotator spawnRotation;
			spawnRotation.Pitch = sc_change_character_packet->pitch;
			spawnRotation.Yaw = sc_change_character_packet->yaw;
			spawnRotation.Roll = sc_change_character_packet->roll;

			FActorSpawnParameters spawnParam;

			AMyCharacter* spawnPlayer = GetWorld()->SpawnActor<AMyCharacter>(SpawnToOtherPlayer, spawnLocation, spawnRotation, spawnParam);
			spawnPlayer->is_othercharacter = true;
			spawnPlayer->mySessionID = sc_change_character_packet->sessionID;
			spawnPlayer->myName = sc_change_character_packet->name;
			FText name = FText::FromName(spawnPlayer->myName);
			spawnPlayer->ui_player_name_ui->player_name->SetText(name);
			spawnPlayer->use = true;

			spawnPlayer->GetCharacterMovement()->StopMovementImmediately();
			spawnPlayer->SetActorEnableCollision(false);
			spawnPlayer->SetActorHiddenInGame(true);


			Aspace_ship* spawnSpaceShip = GetWorld()->SpawnActor<Aspace_ship>(SpawnToOtherSpaceShip, spawnLocation, spawnRotation, spawnParam);

			if (spawnSpaceShip)
			{
				spawnSpaceShip->SetId(sc_change_character_packet->sessionID);
				spawnSpaceShip->owner_character = spawnPlayer;
				spawnPlayer->spaceship = spawnSpaceShip;
			}
		}
		break;
	}
	case CHARACTER_TYPE::SPACESHIP:
	{
		bool was_added = false;
		TArray<AActor*> AllPlayers;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyCharacter::StaticClass(), AllPlayers);
		for (auto& player : AllPlayers) {
			AMyCharacter* thisPlayer = Cast<AMyCharacter>(player);
			if (sc_change_character_packet->sessionID != thisPlayer->mySessionID) continue;
			was_added = true;
			break;
		}
		if (was_added == false)
		{
			FVector spawnLocation;
			spawnLocation.X = sc_change_character_packet->x;
			spawnLocation.Y = sc_change_character_packet->y;
			spawnLocation.Z = sc_change_character_packet->z;

			FRotator spawnRotation;
			spawnRotation.Pitch = sc_change_character_packet->pitch;
			spawnRotation.Yaw = sc_change_character_packet->yaw;
			spawnRotation.Roll = sc_change_character_packet->roll;

			FActorSpawnParameters spawnParam;

			switch (sc_change_character_packet->weapon_type)
			{
			case WEAPON_TYPE::SWORD:
			{
				AMyCharacter* spawnPlayer = GetWorld()->SpawnActor<AMyCharacter>(SpawnToOtherPlayer, spawnLocation, spawnRotation, spawnParam);
				spawnPlayer->is_othercharacter = true;
				spawnPlayer->mySessionID = sc_change_character_packet->sessionID;
				spawnPlayer->myName = sc_change_character_packet->name;
				FText name = FText::FromName(spawnPlayer->myName);
				spawnPlayer->ui_player_name_ui->player_name->SetText(name);
				spawnPlayer->use = true;
				spawnPlayer->OnChangeSword();
				break;
			}
			case WEAPON_TYPE::GUN:
			{
				AMyCharacter* spawnPlayer = GetWorld()->SpawnActor<AMyCharacter>(SpawnToOtherPlayer, spawnLocation, spawnRotation, spawnParam);
				spawnPlayer->is_othercharacter = true;
				spawnPlayer->mySessionID = sc_change_character_packet->sessionID;
				spawnPlayer->myName = sc_change_character_packet->name;
				FText name = FText::FromName(spawnPlayer->myName);
				spawnPlayer->ui_player_name_ui->player_name->SetText(name);
				spawnPlayer->use = true;
				spawnPlayer->OnChangeGun();
				break;
			}
			default:
				break;
			}
		}
		break;
	}
	}
	switch (sc_change_character_packet->character_type)
	{
	case CHARACTER_TYPE::HUMAN:
	{
		TArray<AActor*> AllPlayers;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Aspace_ship::StaticClass(), AllPlayers);
		for (auto& player : AllPlayers) {
			Aspace_ship* thiShip = Cast<Aspace_ship>(player);
			if (sc_change_character_packet->sessionID != thiShip->owner_session_id) continue;
			FHitResult HitResult;
			thiShip->SetActorRotation(FRotator(0, thiShip->GetActorRotation().Yaw, 0));
			FVector start = thiShip->GetActorLocation();
			FVector end = FVector(thiShip->GetActorLocation().X, thiShip->GetActorLocation().Y, thiShip->GetActorLocation().Z - 1000000);
			FCollisionQueryParams CollisionParams;
			GetWorld()->UWorld::LineTraceSingleByChannel(HitResult, start, end, ECollisionChannel::ECC_Visibility);
			thiShip->owner_character->SetActorEnableCollision(true);
			thiShip->owner_character->SetActorLocation(FVector(HitResult.Location.X, HitResult.Location.Y, HitResult.Location.Z + 100));
			thiShip->owner_character->SetActorRotation(FRotator(0, thiShip->follow_camera->GetComponentRotation().Yaw, 0));
			
			if (thiShip->owner_character->InWater)
			{
				thiShip->owner_character->waterZ = 1627;
				thiShip->owner_character->is_swimming = true;
			}

			thiShip->owner_character->enter = 0;
			
			switch (sc_change_character_packet->weapon_type)
			{
			case WEAPON_TYPE::GUN:
			{
				thiShip->owner_character->OnChangeGun(); 
				break;
			}
			case WEAPON_TYPE::SWORD:
			{
				thiShip->owner_character->OnChangeSword();
				break;
			}
			default:
				break;
			}	
			if (IsValid(thiShip->owner_character))
			{
				thiShip->owner_character->LandEffect();
			}
			FTimerHandle handle2;
			GetWorld()->GetTimerManager().SetTimer(handle2, thiShip, &Aspace_ship::ExitUnHidden, 1.15f, false);
		}
		break;
	}
	case CHARACTER_TYPE::SPACESHIP:
	{
		TArray<AActor*> AllPlayers;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyCharacter::StaticClass(), AllPlayers);
		for (auto& player : AllPlayers) {
			AMyCharacter* thisPlayer = Cast<AMyCharacter>(player);
			if (sc_change_character_packet->sessionID != thisPlayer->mySessionID) continue;
			TArray<AActor*> AllShip;
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), Aspace_ship::StaticClass(), AllShip);
			for (auto& ship : AllShip) {
				Aspace_ship* thisShip = Cast<Aspace_ship>(ship);
				if (thisShip) {
					if (sc_change_character_packet->sessionID != thisShip->owner_session_id) continue;
					thisPlayer->spaceship = thisShip;
					thisPlayer->current_weapon->OnUnEquip();
					thisPlayer->enter = 1;
					thisPlayer->is_swimming = false;
					thisPlayer->GetCharacterMovement()->GetPhysicsVolume()->bWaterVolume = false;
					thisPlayer->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
					thisPlayer->run = false;
					thisShip->EnterCharacter(thisPlayer);
				}
			}

		}
		break;
	}
	default:
		break;
	}

	delete sc_change_character_packet;
	sc_character_state = false;
}

void AMainGamePlayerController::ChangeWeaponProcess()
{
	bool was_added = false;
	TArray<AActor*> FindPlayers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyCharacter::StaticClass(), FindPlayers);
	for (auto& player : FindPlayers) {
		AMyCharacter* thisPlayer = Cast<AMyCharacter>(player);
		if (sc_change_character_packet->sessionID != thisPlayer->mySessionID) continue;
		was_added = true;
		break;
	}
	if (was_added == false)
	{
		FVector spawnLocation;
		spawnLocation.X = sc_change_character_packet->x;
		spawnLocation.Y = sc_change_character_packet->y;
		spawnLocation.Z = sc_change_character_packet->z;

		FRotator spawnRotation;
		spawnRotation.Pitch = sc_change_character_packet->pitch;
		spawnRotation.Yaw = sc_change_character_packet->yaw;
		spawnRotation.Roll = sc_change_character_packet->roll;

		FActorSpawnParameters spawnParam;

		switch (sc_change_character_packet->weapon_type)
		{
		case WEAPON_TYPE::SWORD:
		{
			AMyCharacter* spawnPlayer = GetWorld()->SpawnActor<AMyCharacter>(SpawnToOtherPlayer, spawnLocation, spawnRotation, spawnParam);
			spawnPlayer->is_othercharacter = true;
			spawnPlayer->mySessionID = sc_change_character_packet->sessionID;
			spawnPlayer->myName = sc_change_character_packet->name;
			FText name = FText::FromName(spawnPlayer->myName);
			spawnPlayer->ui_player_name_ui->player_name->SetText(name);
			spawnPlayer->use = true;
			spawnPlayer->OnChangeSword();
			break;
		}
		case WEAPON_TYPE::GUN:
		{
			AMyCharacter* spawnPlayer = GetWorld()->SpawnActor<AMyCharacter>(SpawnToOtherPlayer, spawnLocation, spawnRotation, spawnParam);
			spawnPlayer->is_othercharacter = true;
			spawnPlayer->mySessionID = sc_change_character_packet->sessionID;
			spawnPlayer->myName = sc_change_character_packet->name;
			FText name = FText::FromName(spawnPlayer->myName);
			spawnPlayer->ui_player_name_ui->player_name->SetText(name);
			spawnPlayer->use = true;
			spawnPlayer->OnChangeGun();
			break;
		}
		default:
			break;
		}
	}

	TArray<AActor*> AllPlayers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyCharacter::StaticClass(), AllPlayers);
	for (auto& player : AllPlayers) {
		AMyCharacter* thisPlayer = Cast<AMyCharacter>(player);
		if (sc_change_character_packet->sessionID != thisPlayer->mySessionID) continue;
		// 무기(총, 칼) 변경 to do...
		switch (sc_change_character_packet->weapon_type)
		{
		case WEAPON_TYPE::GUN:
			thisPlayer->OnChangeGun();
			thisPlayer->cur_weapon = 1;
			break;
		case WEAPON_TYPE::SWORD:
			thisPlayer->OnChangeSword();
			thisPlayer->cur_weapon = 0;
			break;
		}
	}
	delete sc_change_character_packet;
	sc_weapon_state = false;
}

void AMainGamePlayerController::AttackSkillProcess()
{
	bool was_added = false;
	TArray<AActor*> FindPlayers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyCharacter::StaticClass(), FindPlayers);
	for (auto& player : FindPlayers) {
		AMyCharacter* thisPlayer = Cast<AMyCharacter>(player);
		if (sc_attack_skill_packet->sessionID != thisPlayer->mySessionID) continue;
		was_added = true;
		break;
	}
	if (was_added == false)
	{
		FVector spawnLocation;
		spawnLocation.X = sc_attack_skill_packet->x;
		spawnLocation.Y = sc_attack_skill_packet->y;
		spawnLocation.Z = sc_attack_skill_packet->z;

		FRotator spawnRotation;
		spawnRotation.Pitch = sc_attack_skill_packet->pitch;
		spawnRotation.Yaw = sc_attack_skill_packet->yaw;
		spawnRotation.Roll = sc_attack_skill_packet->roll;

		FActorSpawnParameters spawnParam;

		switch (sc_attack_skill_packet->weapon_type)
		{
		case WEAPON_TYPE::SWORD:
		{
			AMyCharacter* spawnPlayer = GetWorld()->SpawnActor<AMyCharacter>(SpawnToOtherPlayer, spawnLocation, spawnRotation, spawnParam);
			spawnPlayer->is_othercharacter = true;
			spawnPlayer->mySessionID = sc_attack_skill_packet->sessionID;
			spawnPlayer->myName = sc_attack_skill_packet->name;
			FText name = FText::FromName(spawnPlayer->myName);
			spawnPlayer->ui_player_name_ui->player_name->SetText(name);
			spawnPlayer->use = true;
			spawnPlayer->OnChangeSword();
			break;
		}
		case WEAPON_TYPE::GUN:
		{
			AMyCharacter* spawnPlayer = GetWorld()->SpawnActor<AMyCharacter>(SpawnToOtherPlayer, spawnLocation, spawnRotation, spawnParam);
			spawnPlayer->is_othercharacter = true;
			spawnPlayer->mySessionID = sc_attack_skill_packet->sessionID;
			spawnPlayer->myName = sc_attack_skill_packet->name;
			FText name = FText::FromName(spawnPlayer->myName);
			spawnPlayer->ui_player_name_ui->player_name->SetText(name);
			spawnPlayer->use = true;
			spawnPlayer->OnChangeGun();
			break;
		}
		default:
			break;
		}
	}
	TArray<AActor*> AllPlayers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyCharacter::StaticClass(), AllPlayers);
	for (auto& player : AllPlayers) {
		AMyCharacter* thisPlayer = Cast<AMyCharacter>(player);
		if (sc_attack_skill_packet->sessionID != thisPlayer->mySessionID) continue;
		switch (sc_attack_skill_packet->attack_skill_type)
		{
		case ATTACK_SKILL_TYPE::NORMAL:
			if (thisPlayer->cur_weapon == 0)
				thisPlayer->WeaponAttack();
			else
				thisPlayer->OnFireGun(FRotator(sc_attack_skill_packet->cpitch, sc_attack_skill_packet->cyaw, sc_attack_skill_packet->croll));
			break;
		case ATTACK_SKILL_TYPE::DASHING:
		{
			thisPlayer->is_dashing = true;
			thisPlayer->spawn_trail = UNiagaraFunctionLibrary::SpawnSystemAttached(thisPlayer->dash_trail,
				thisPlayer->fx_loc, TEXT("None"),
				thisPlayer->fx_loc->GetComponentLocation(),
				FRotator(0, 0, UKismetMathLibrary::MakeRotFromX(thisPlayer->GetActorForwardVector()).Vector().Z),
				EAttachLocation::KeepWorldPosition, false, true, ENCPoolMethod::None, true);
			break; 
		}
		case ATTACK_SKILL_TYPE::LAUNCHER:
			thisPlayer->launcher_particle_radius = sc_attack_skill_packet->launcher_particle_radius;
			thisPlayer->OnLauncherProjectile(FRotator(sc_attack_skill_packet->cpitch, sc_attack_skill_packet->cyaw, sc_attack_skill_packet->croll));
			break;
		case ATTACK_SKILL_TYPE::SNIPING:
		{
			UNiagaraComponent* shoot_spark = UNiagaraFunctionLibrary::SpawnSystemAttached(thisPlayer->sniper_spark, thisPlayer->GetMesh(),
				TEXT("muzzlepoint"), FVector::ZeroVector,
				FRotator::ZeroRotator, EAttachLocation::SnapToTarget, false, true, ENCPoolMethod::None, true);
			thisPlayer->OnFireSniper(FRotator(sc_attack_skill_packet->cpitch, sc_attack_skill_packet->cyaw, sc_attack_skill_packet->croll));
			break; 
		}
		case ATTACK_SKILL_TYPE::MISSILE:
			thisPlayer->FindMonster();
			break;
		case ATTACK_SKILL_TYPE::ULTIMATE:
		{
			thisPlayer->PlayAnimMontage(thisPlayer->ultimate_montage, 1, NAME_None);
			thisPlayer->is_ultimate_anim = true;
			FTimerHandle handle;
			GetWorld()->GetTimerManager().SetTimer(handle, thisPlayer, &AMyCharacter::EndUltimateAnim, 1, false);
			break;
		}
		case ATTACK_SKILL_TYPE::DEFENSE:
		{
			thisPlayer->DefenseAnim();
			break;
		}
		case ATTACK_SKILL_TYPE::SLASH:
		{
			thisPlayer->slash_size = sc_attack_skill_packet->slash_size;
			thisPlayer->SlashAnim(FRotator(sc_attack_skill_packet->cpitch, sc_attack_skill_packet->cyaw, sc_attack_skill_packet->croll));
			break;
		}
		case ATTACK_SKILL_TYPE::JUMP:
		{
			thisPlayer->GetCharacterMovement()->JumpZVelocity = sc_attack_skill_packet->jump_velocity;
			thisPlayer->is_jumping = true;
			break;
		}
		}
		break;
	}

	delete sc_attack_skill_packet;
	sc_attack_skill_state = false;
}

void AMainGamePlayerController::SpawnShipProcess()
{
	bool was_added = false;
	TArray<AActor*> FindPlayers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyCharacter::StaticClass(), FindPlayers);
	for (auto& player : FindPlayers) {
		AMyCharacter* thisPlayer = Cast<AMyCharacter>(player);
		if (sc_spawn_spaceship_packet->owner_sessionID != thisPlayer->mySessionID) continue;
		was_added = true;
		break;
	}
	if (was_added == false)
	{
		FVector spawnLocation;
		spawnLocation.X = sc_spawn_spaceship_packet->player_x;
		spawnLocation.Y = sc_spawn_spaceship_packet->player_y;
		spawnLocation.Z = sc_spawn_spaceship_packet->player_z;

		FRotator spawnRotation;
		spawnRotation.Pitch = sc_spawn_spaceship_packet->player_pitch;
		spawnRotation.Yaw = sc_spawn_spaceship_packet->player_yaw;
		spawnRotation.Roll = sc_spawn_spaceship_packet->player_roll;

		FActorSpawnParameters spawnParam;

		switch (sc_spawn_spaceship_packet->weapon_type)
		{
		case WEAPON_TYPE::SWORD:
		{
			AMyCharacter* spawnPlayer = GetWorld()->SpawnActor<AMyCharacter>(SpawnToOtherPlayer, spawnLocation, spawnRotation, spawnParam);
			spawnPlayer->is_othercharacter = true;
			spawnPlayer->mySessionID = sc_spawn_spaceship_packet->owner_sessionID;
			spawnPlayer->myName = sc_spawn_spaceship_packet->name;
			FText name = FText::FromName(spawnPlayer->myName);
			spawnPlayer->ui_player_name_ui->player_name->SetText(name);
			spawnPlayer->use = true;
			spawnPlayer->OnChangeSword();
			break;
		}
		case WEAPON_TYPE::GUN:
		{
			AMyCharacter* spawnPlayer = GetWorld()->SpawnActor<AMyCharacter>(SpawnToOtherPlayer, spawnLocation, spawnRotation, spawnParam);
			spawnPlayer->is_othercharacter = true;
			spawnPlayer->mySessionID = sc_spawn_spaceship_packet->owner_sessionID;
			spawnPlayer->myName = sc_spawn_spaceship_packet->name;
			FText name = FText::FromName(spawnPlayer->myName);
			spawnPlayer->ui_player_name_ui->player_name->SetText(name);
			spawnPlayer->use = true;
			spawnPlayer->OnChangeGun();
			break;
		}
		default:
			break;
		}
	}
	
	bool was_ship_added = false;
	Aspace_ship* findShip = NULL;
	TArray<AActor*> ALLShip;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), Aspace_ship::StaticClass(), ALLShip);
	for (auto& player : ALLShip) {
		Aspace_ship* thisShip = Cast<Aspace_ship>(player);
		if (sc_spawn_spaceship_packet->owner_sessionID != thisShip->owner_session_id) continue;
		findShip = thisShip;
		was_ship_added = true;
		break;
	}
	if (was_ship_added)
	{
		if (findShip)
			findShip->Destroy();
	}
	// 우주선 소환
	FVector spawnLocation;
	spawnLocation.X = sc_spawn_spaceship_packet->x;
	spawnLocation.Y = sc_spawn_spaceship_packet->y;
	spawnLocation.Z = sc_spawn_spaceship_packet->z;

	FRotator spawnRotation;
	spawnRotation.Pitch = sc_spawn_spaceship_packet->pitch;
	spawnRotation.Yaw = sc_spawn_spaceship_packet->yaw;
	spawnRotation.Roll = sc_spawn_spaceship_packet->roll;

	FActorSpawnParameters spawnParam;
	Aspace_ship* spawnSpaceShip = GetWorld()->SpawnActor<Aspace_ship>(SpawnToOtherSpaceShip, spawnLocation, spawnRotation, spawnParam);
	
	TArray<AActor*> AllPlayers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyCharacter::StaticClass(), AllPlayers);
	for (auto& player : AllPlayers) {
		AMyCharacter* thisPlayer = Cast<AMyCharacter>(player);
		if (sc_spawn_spaceship_packet->owner_sessionID != thisPlayer->mySessionID) continue;
		spawnSpaceShip->SetId(thisPlayer->mySessionID);
		break;
	}
	

	delete sc_spawn_spaceship_packet;
	sc_spawn_spaceship_state = false;
}

void AMainGamePlayerController::ChangeMapProcess()
{
	Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));

	GameInstanceRef->change_map = true;

	delete sc_change_map_packet;
	sc_change_map_state = false;
}

void AMainGamePlayerController::MonsterDamageProcess()
{
	FVector spawnLocationM;
	spawnLocationM.X = sc_damage_monster_packet->x;
	spawnLocationM.Y = sc_damage_monster_packet->y;
	spawnLocationM.Z = sc_damage_monster_packet->z;

	FRotator spawnRotationM;
	spawnRotationM.Pitch = sc_damage_monster_packet->pitch;
	spawnRotationM.Yaw = sc_damage_monster_packet->yaw;
	spawnRotationM.Roll = sc_damage_monster_packet->roll;

	FActorSpawnParameters spawnParamM;
	spawnParamM.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	switch (sc_damage_monster_packet->monsterType)
	{
	case MONSTER_TYPE::F_ICE:
	{
		bool bexist = false;
		TArray<AActor*> AllMonster;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Afirst_ice_monster::StaticClass(), AllMonster);
		for (auto& monster : AllMonster) {
			Afirst_ice_monster* thisMonster = Cast<Afirst_ice_monster>(monster);
			if (sc_damage_monster_packet->sessionID != thisMonster->sessionID) continue;
			thisMonster->PlayHit();
			thisMonster->hp = sc_damage_monster_packet->hp;
			if (thisMonster->hp <= 0)
			{
				FActorSpawnParameters spawnParam;
				FVector start = thisMonster->GetActorLocation();
				FVector end = FVector(thisMonster->GetActorLocation().X, thisMonster->GetActorLocation().Y, thisMonster->GetActorLocation().Z - 1000000);
				thisMonster->Destroy();
				FCollisionQueryParams CollisionParams;
				FHitResult HitResult;
				GetWorld()->UWorld::LineTraceSingleByChannel(HitResult, start, end, ECollisionChannel::ECC_Visibility);
				FVector spawnLocation = FVector(HitResult.Location.X, HitResult.Location.Y, HitResult.Location.Z + 50);
				myCharacter->is_target_locked = false;
				if (myCharacter->target_maker_object->IsValidLowLevel())
				{
					myCharacter->target_maker_object->Destroy();
					myCharacter->target_maker_object = NULL;
				}
				if (myCharacter->mySessionID == sc_damage_monster_packet->attack_sessionID)
				{
					switch (sc_damage_monster_packet->item)
					{
					case DROP_ITEM::A_COIN:
					{
						Aa_coin* spawned_a_coin = GetWorld()->SpawnActor<Aa_coin>(spawn_a_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_a_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					case DROP_ITEM::B_COIN:
					{
						Ab_coin* spawned_b_coin = GetWorld()->SpawnActor<Ab_coin>(spawn_b_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_b_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					case DROP_ITEM::C_COIN:
					{
						Ac_coin* spawned_c_coin = GetWorld()->SpawnActor<Ac_coin>(spawn_c_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_c_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					default:
						break;
					}
				}
			}
			bexist = true;
			break;
		}
		if (false == bexist) {
			Afirst_ice_monster* spawnMonster = GetWorld()->SpawnActor<Afirst_ice_monster>(SpawnToFirstIceMonster, spawnLocationM, spawnRotationM, spawnParamM);
			spawnMonster->sessionID = sc_damage_monster_packet->sessionID;
			spawnMonster->hp = sc_damage_monster_packet->hp;
			spawnMonster->max_hp = 100;
			if (spawnMonster->hp <= 0)
			{
				FActorSpawnParameters spawnParam;
				FVector spawnLocation = spawnMonster->GetActorLocation();
				spawnMonster->Destroy();
				myCharacter->is_target_locked = false;
				if (myCharacter->target_maker_object->IsValidLowLevel())
				{
					myCharacter->target_maker_object->Destroy();
					myCharacter->target_maker_object = NULL;
				}
				if (myCharacter->mySessionID == sc_damage_monster_packet->attack_sessionID)
				{
					switch (sc_damage_monster_packet->item)
					{
					case DROP_ITEM::A_COIN:
					{
						Aa_coin* spawned_a_coin = GetWorld()->SpawnActor<Aa_coin>(spawn_a_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_a_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					case DROP_ITEM::B_COIN:
					{
						Ab_coin* spawned_b_coin = GetWorld()->SpawnActor<Ab_coin>(spawn_b_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_b_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					case DROP_ITEM::C_COIN:
					{
						Ac_coin* spawned_c_coin = GetWorld()->SpawnActor<Ac_coin>(spawn_c_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_c_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					default:
						break;
					}
				}
			}
		}
		break;
	}
	case MONSTER_TYPE::S_ICE:
	{
		bool bexist = false;
		TArray<AActor*> AllMonster;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Asecond_ice_monster::StaticClass(), AllMonster);
		for (auto& monster : AllMonster) {
			Asecond_ice_monster* thisMonster = Cast<Asecond_ice_monster>(monster);
			if (sc_damage_monster_packet->sessionID != thisMonster->sessionID) continue;
			thisMonster->PlayHit();
			thisMonster->hp = sc_damage_monster_packet->hp;
			if (thisMonster->hp <= 0)
			{
				FActorSpawnParameters spawnParam;
				FVector start = thisMonster->GetActorLocation();
				FVector end = FVector(thisMonster->GetActorLocation().X, thisMonster->GetActorLocation().Y, thisMonster->GetActorLocation().Z - 1000000);
				thisMonster->Destroy();
				FCollisionQueryParams CollisionParams;
				FHitResult HitResult;
				GetWorld()->UWorld::LineTraceSingleByChannel(HitResult, start, end, ECollisionChannel::ECC_Visibility);
				FVector spawnLocation = FVector(HitResult.Location.X, HitResult.Location.Y, HitResult.Location.Z + 50);
				myCharacter->is_target_locked = false;
				if (myCharacter->target_maker_object->IsValidLowLevel())
				{
					myCharacter->target_maker_object->Destroy();
					myCharacter->target_maker_object = NULL;
				}
				if (myCharacter->mySessionID == sc_damage_monster_packet->attack_sessionID)
				{

					switch (sc_damage_monster_packet->item)
					{
					case DROP_ITEM::A_COIN:
					{
						Aa_coin* spawned_a_coin = GetWorld()->SpawnActor<Aa_coin>(spawn_a_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_a_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					case DROP_ITEM::B_COIN:
					{
						Ab_coin* spawned_b_coin = GetWorld()->SpawnActor<Ab_coin>(spawn_b_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_b_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					case DROP_ITEM::C_COIN:
					{
						Ac_coin* spawned_c_coin = GetWorld()->SpawnActor<Ac_coin>(spawn_c_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_c_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					default:
						break;
					}
				}
			}
			bexist = true;
			break;
		}
		if (false == bexist) {
			Asecond_ice_monster* spawnMonster = GetWorld()->SpawnActor<Asecond_ice_monster>(SpawnToSecondIceMonster, spawnLocationM, spawnRotationM, spawnParamM);
			spawnMonster->sessionID = sc_damage_monster_packet->sessionID;
			spawnMonster->hp = sc_damage_monster_packet->hp;
			spawnMonster->max_hp = 200;
			if (spawnMonster->hp <= 0)
			{
				FActorSpawnParameters spawnParam;
				FVector spawnLocation = spawnMonster->GetActorLocation();
				spawnMonster->Destroy();
				myCharacter->is_target_locked = false;
				if (myCharacter->target_maker_object->IsValidLowLevel())
				{
					myCharacter->target_maker_object->Destroy();
					myCharacter->target_maker_object = NULL;
				}
				if (myCharacter->mySessionID == sc_damage_monster_packet->attack_sessionID)
				{
					switch (sc_damage_monster_packet->item)
					{
					case DROP_ITEM::A_COIN:
					{
						Aa_coin* spawned_a_coin = GetWorld()->SpawnActor<Aa_coin>(spawn_a_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_a_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					case DROP_ITEM::B_COIN:
					{
						Ab_coin* spawned_b_coin = GetWorld()->SpawnActor<Ab_coin>(spawn_b_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_b_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					case DROP_ITEM::C_COIN:
					{
						Ac_coin* spawned_c_coin = GetWorld()->SpawnActor<Ac_coin>(spawn_c_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_c_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					default:
						break;
					}
				}
			}
		}
		break;
	}
	case MONSTER_TYPE::T_ICE:
	{
		bool bexist = false;
		TArray<AActor*> AllMonster;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Athird_ice_monster::StaticClass(), AllMonster);
		for (auto& monster : AllMonster) {
			Athird_ice_monster* thisMonster = Cast<Athird_ice_monster>(monster);
			if (sc_damage_monster_packet->sessionID != thisMonster->sessionID) continue;
			thisMonster->PlayHit();
			thisMonster->hp = sc_damage_monster_packet->hp;
			if (thisMonster->hp <= 0)
			{
				FActorSpawnParameters spawnParam;
				FVector start = thisMonster->GetActorLocation();
				FVector end = FVector(thisMonster->GetActorLocation().X, thisMonster->GetActorLocation().Y, thisMonster->GetActorLocation().Z - 1000000);
				thisMonster->Destroy();
				FCollisionQueryParams CollisionParams;
				FHitResult HitResult;
				GetWorld()->UWorld::LineTraceSingleByChannel(HitResult, start, end, ECollisionChannel::ECC_Visibility);
				FVector spawnLocation = FVector(HitResult.Location.X, HitResult.Location.Y, HitResult.Location.Z + 50);
				myCharacter->is_target_locked = false;
				if (myCharacter->target_maker_object->IsValidLowLevel())
				{
					myCharacter->target_maker_object->Destroy();
					myCharacter->target_maker_object = NULL;
				}
				if (myCharacter->mySessionID == sc_damage_monster_packet->attack_sessionID)
				{
					switch (sc_damage_monster_packet->item)
					{
					case DROP_ITEM::A_COIN:
					{
						Aa_coin* spawned_a_coin = GetWorld()->SpawnActor<Aa_coin>(spawn_a_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_a_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					case DROP_ITEM::B_COIN:
					{
						Ab_coin* spawned_b_coin = GetWorld()->SpawnActor<Ab_coin>(spawn_b_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_b_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					case DROP_ITEM::C_COIN:
					{
						Ac_coin* spawned_c_coin = GetWorld()->SpawnActor<Ac_coin>(spawn_c_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_c_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					default:
						break;
					}
				}
			}
			bexist = true;
			break;
		}
		if (false == bexist) {
			Athird_ice_monster* spawnMonster = GetWorld()->SpawnActor<Athird_ice_monster>(SpawnToThirdIceMonster, spawnLocationM, spawnRotationM, spawnParamM);
			spawnMonster->sessionID = sc_damage_monster_packet->sessionID;
			spawnMonster->hp = sc_damage_monster_packet->hp;
			spawnMonster->max_hp = 400;
			if (spawnMonster->hp <= 0)
			{
				FActorSpawnParameters spawnParam;
				FVector spawnLocation = spawnMonster->GetActorLocation();
				spawnMonster->Destroy();
				myCharacter->is_target_locked = false;
				if (myCharacter->target_maker_object->IsValidLowLevel())
				{
					myCharacter->target_maker_object->Destroy();
					myCharacter->target_maker_object = NULL;
				}
				if (myCharacter->mySessionID == sc_damage_monster_packet->attack_sessionID)
				{
					switch (sc_damage_monster_packet->item)
					{
					case DROP_ITEM::A_COIN:
					{
						Aa_coin* spawned_a_coin = GetWorld()->SpawnActor<Aa_coin>(spawn_a_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_a_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					case DROP_ITEM::B_COIN:
					{
						Ab_coin* spawned_b_coin = GetWorld()->SpawnActor<Ab_coin>(spawn_b_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_b_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					case DROP_ITEM::C_COIN:
					{
						Ac_coin* spawned_c_coin = GetWorld()->SpawnActor<Ac_coin>(spawn_c_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_c_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					default:
						break;
					}
				}
			}
		}
		break;
	}
	case MONSTER_TYPE::F_SAND:
	{
		bool bexist = false;
		TArray<AActor*> AllMonster;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Afirst_sand_monster::StaticClass(), AllMonster);
		for (auto& monster : AllMonster) {
			Afirst_sand_monster* thisMonster = Cast<Afirst_sand_monster>(monster);
			if (sc_damage_monster_packet->sessionID != thisMonster->sessionID) continue;
			thisMonster->PlayHit();
			thisMonster->hp = sc_damage_monster_packet->hp;
			if (thisMonster->hp <= 0)
			{
				FActorSpawnParameters spawnParam;
				FVector start = thisMonster->GetActorLocation();
				FVector end = FVector(thisMonster->GetActorLocation().X, thisMonster->GetActorLocation().Y, thisMonster->GetActorLocation().Z - 1000000);
				thisMonster->Destroy();
				FCollisionQueryParams CollisionParams;
				FHitResult HitResult;
				GetWorld()->UWorld::LineTraceSingleByChannel(HitResult, start, end, ECollisionChannel::ECC_Visibility);
				FVector spawnLocation = FVector(HitResult.Location.X, HitResult.Location.Y, HitResult.Location.Z + 50);
				myCharacter->is_target_locked = false;
				if (myCharacter->target_maker_object->IsValidLowLevel())
				{
					myCharacter->target_maker_object->Destroy();
					myCharacter->target_maker_object = NULL;
				}
				if (myCharacter->mySessionID == sc_damage_monster_packet->attack_sessionID)
				{

					switch (sc_damage_monster_packet->item)
					{
					case DROP_ITEM::A_COIN:
					{
						Aa_coin* spawned_a_coin = GetWorld()->SpawnActor<Aa_coin>(spawn_a_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_a_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					case DROP_ITEM::B_COIN:
					{
						Ab_coin* spawned_b_coin = GetWorld()->SpawnActor<Ab_coin>(spawn_b_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_b_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					case DROP_ITEM::C_COIN:
					{
						Ac_coin* spawned_c_coin = GetWorld()->SpawnActor<Ac_coin>(spawn_c_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_c_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					default:
						break;
					}
				}
			}
			bexist = true;
			break;
		}
		if (false == bexist) {
			Afirst_sand_monster* spawnMonster = GetWorld()->SpawnActor<Afirst_sand_monster>(SpawnToFirstSandMonster, spawnLocationM, spawnRotationM, spawnParamM);
			spawnMonster->sessionID = sc_damage_monster_packet->sessionID;
			spawnMonster->hp = sc_damage_monster_packet->hp;
			spawnMonster->max_hp = 100;
			if (spawnMonster->hp <= 0)
			{
				FActorSpawnParameters spawnParam;
				FVector spawnLocation = spawnMonster->GetActorLocation();
				spawnMonster->Destroy();
				myCharacter->is_target_locked = false;
				if (myCharacter->target_maker_object->IsValidLowLevel())
				{
					myCharacter->target_maker_object->Destroy();
					myCharacter->target_maker_object = NULL;
				}
				if (myCharacter->mySessionID == sc_damage_monster_packet->attack_sessionID)
				{
					switch (sc_damage_monster_packet->item)
					{
					case DROP_ITEM::A_COIN:
					{
						Aa_coin* spawned_a_coin = GetWorld()->SpawnActor<Aa_coin>(spawn_a_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_a_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					case DROP_ITEM::B_COIN:
					{
						Ab_coin* spawned_b_coin = GetWorld()->SpawnActor<Ab_coin>(spawn_b_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_b_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					case DROP_ITEM::C_COIN:
					{
						Ac_coin* spawned_c_coin = GetWorld()->SpawnActor<Ac_coin>(spawn_c_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_c_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					default:
						break;
					}
				}
			}
		}
		break;
	}
	case MONSTER_TYPE::S_SAND:
	{
		bool bexist = false;
		TArray<AActor*> AllMonster;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Asecond_sand_monster::StaticClass(), AllMonster);
		for (auto& monster : AllMonster) {
			Asecond_sand_monster* thisMonster = Cast<Asecond_sand_monster>(monster);
			if (sc_damage_monster_packet->sessionID != thisMonster->sessionID) continue;
			thisMonster->PlayHit();
			thisMonster->hp = sc_damage_monster_packet->hp;
			if (thisMonster->hp <= 0)
			{
				FActorSpawnParameters spawnParam;
				FVector start = thisMonster->GetActorLocation();
				FVector end = FVector(thisMonster->GetActorLocation().X, thisMonster->GetActorLocation().Y, thisMonster->GetActorLocation().Z - 1000000);
				thisMonster->Destroy();
				FCollisionQueryParams CollisionParams;
				FHitResult HitResult;
				GetWorld()->UWorld::LineTraceSingleByChannel(HitResult, start, end, ECollisionChannel::ECC_Visibility);
				FVector spawnLocation = FVector(HitResult.Location.X, HitResult.Location.Y, HitResult.Location.Z + 50);
				myCharacter->is_target_locked = false;
				if (myCharacter->target_maker_object->IsValidLowLevel())
				{
					myCharacter->target_maker_object->Destroy();
					myCharacter->target_maker_object = NULL;
				}
				if (myCharacter->mySessionID == sc_damage_monster_packet->attack_sessionID)
				{

					switch (sc_damage_monster_packet->item)
					{
					case DROP_ITEM::A_COIN:
					{
						Aa_coin* spawned_a_coin = GetWorld()->SpawnActor<Aa_coin>(spawn_a_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_a_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					case DROP_ITEM::B_COIN:
					{
						Ab_coin* spawned_b_coin = GetWorld()->SpawnActor<Ab_coin>(spawn_b_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_b_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					case DROP_ITEM::C_COIN:
					{
						Ac_coin* spawned_c_coin = GetWorld()->SpawnActor<Ac_coin>(spawn_c_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_c_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					default:
						break;
					}
				}
			}
			bexist = true;
			break;
		}
		if (false == bexist) {
			Asecond_sand_monster* spawnMonster = GetWorld()->SpawnActor<Asecond_sand_monster>(SpawnToSecondSandMonster, spawnLocationM, spawnRotationM, spawnParamM);
			spawnMonster->sessionID = sc_damage_monster_packet->sessionID;
			spawnMonster->hp = sc_damage_monster_packet->hp;
			spawnMonster->max_hp = 200;
			if (spawnMonster->hp <= 0)
			{
				FActorSpawnParameters spawnParam;
				FVector spawnLocation = spawnMonster->GetActorLocation();
				spawnMonster->Destroy();
				myCharacter->is_target_locked = false;
				if (myCharacter->target_maker_object->IsValidLowLevel())
				{
					myCharacter->target_maker_object->Destroy();
					myCharacter->target_maker_object = NULL;
				}
				if (myCharacter->mySessionID == sc_damage_monster_packet->attack_sessionID)
				{
					switch (sc_damage_monster_packet->item)
					{
					case DROP_ITEM::A_COIN:
					{
						Aa_coin* spawned_a_coin = GetWorld()->SpawnActor<Aa_coin>(spawn_a_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_a_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					case DROP_ITEM::B_COIN:
					{
						Ab_coin* spawned_b_coin = GetWorld()->SpawnActor<Ab_coin>(spawn_b_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_b_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					case DROP_ITEM::C_COIN:
					{
						Ac_coin* spawned_c_coin = GetWorld()->SpawnActor<Ac_coin>(spawn_c_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_c_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					default:
						break;
					}
				}
			}
		}
		break;
	}
	case MONSTER_TYPE::T_SAND:
	{
		bool bexist = false;
		TArray<AActor*> AllMonster;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Athird_sand_monster::StaticClass(), AllMonster);
		for (auto& monster : AllMonster) {
			Athird_sand_monster* thisMonster = Cast<Athird_sand_monster>(monster);
			if (sc_damage_monster_packet->sessionID != thisMonster->sessionID) continue;
			thisMonster->PlayHit();
			thisMonster->hp = sc_damage_monster_packet->hp;
			if (thisMonster->hp <= 0)
			{
				FActorSpawnParameters spawnParam;
				FVector start = thisMonster->GetActorLocation();
				FVector end = FVector(thisMonster->GetActorLocation().X, thisMonster->GetActorLocation().Y, thisMonster->GetActorLocation().Z - 1000000);
				thisMonster->Destroy();
				FCollisionQueryParams CollisionParams;
				FHitResult HitResult;
				GetWorld()->UWorld::LineTraceSingleByChannel(HitResult, start, end, ECollisionChannel::ECC_Visibility);
				FVector spawnLocation = FVector(HitResult.Location.X, HitResult.Location.Y, HitResult.Location.Z + 50);
				myCharacter->is_target_locked = false;
				if (myCharacter->target_maker_object->IsValidLowLevel())
				{
					myCharacter->target_maker_object->Destroy();
					myCharacter->target_maker_object = NULL;
				}
				if (myCharacter->mySessionID == sc_damage_monster_packet->attack_sessionID)
				{

					switch (sc_damage_monster_packet->item)
					{
					case DROP_ITEM::A_COIN:
					{
						Aa_coin* spawned_a_coin = GetWorld()->SpawnActor<Aa_coin>(spawn_a_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_a_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					case DROP_ITEM::B_COIN:
					{
						Ab_coin* spawned_b_coin = GetWorld()->SpawnActor<Ab_coin>(spawn_b_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_b_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					case DROP_ITEM::C_COIN:
					{
						Ac_coin* spawned_c_coin = GetWorld()->SpawnActor<Ac_coin>(spawn_c_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_c_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					default:
						break;
					}
				}
			}
			bexist = true;
			break;
		}
		if (false == bexist) {
			Athird_sand_monster* spawnMonster = GetWorld()->SpawnActor<Athird_sand_monster>(SpawnToThirdSandMonster, spawnLocationM, spawnRotationM, spawnParamM);
			spawnMonster->sessionID = sc_damage_monster_packet->sessionID;
			spawnMonster->hp = sc_damage_monster_packet->hp;
			spawnMonster->max_hp = 400;
			if (spawnMonster->hp <= 0)
			{
				FActorSpawnParameters spawnParam;
				FVector spawnLocation = spawnMonster->GetActorLocation();
				spawnMonster->Destroy();
				myCharacter->is_target_locked = false;
				if (myCharacter->target_maker_object->IsValidLowLevel())
				{
					myCharacter->target_maker_object->Destroy();
					myCharacter->target_maker_object = NULL;
				}
				if (myCharacter->mySessionID == sc_damage_monster_packet->attack_sessionID)
				{
					switch (sc_damage_monster_packet->item)
					{
					case DROP_ITEM::A_COIN:
					{
						Aa_coin* spawned_a_coin = GetWorld()->SpawnActor<Aa_coin>(spawn_a_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_a_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					case DROP_ITEM::B_COIN:
					{
						Ab_coin* spawned_b_coin = GetWorld()->SpawnActor<Ab_coin>(spawn_b_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_b_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					case DROP_ITEM::C_COIN:
					{
						Ac_coin* spawned_c_coin = GetWorld()->SpawnActor<Ac_coin>(spawn_c_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_c_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					default:
						break;
					}
				}
			}
		}
		break;
	}
	case MONSTER_TYPE::F_WATER:
	{
		bool bexist = false;
		TArray<AActor*> AllMonster;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Afirst_water_monster::StaticClass(), AllMonster);
		for (auto& monster : AllMonster) {
			Afirst_water_monster* thisMonster = Cast<Afirst_water_monster>(monster);
			if (sc_damage_monster_packet->sessionID != thisMonster->sessionID) continue;
			thisMonster->PlayHit();
			thisMonster->hp = sc_damage_monster_packet->hp;
			if (thisMonster->hp <= 0)
			{
				FActorSpawnParameters spawnParam;
				FVector start = thisMonster->GetActorLocation();
				FVector end = FVector(thisMonster->GetActorLocation().X, thisMonster->GetActorLocation().Y, thisMonster->GetActorLocation().Z - 1000000);
				thisMonster->Destroy();
				FCollisionQueryParams CollisionParams;
				FHitResult HitResult;
				GetWorld()->UWorld::LineTraceSingleByChannel(HitResult, start, end, ECollisionChannel::ECC_Visibility);
				FVector spawnLocation = FVector(HitResult.Location.X, HitResult.Location.Y, HitResult.Location.Z + 50);
				myCharacter->is_target_locked = false;
				if (myCharacter->target_maker_object->IsValidLowLevel())
				{
					myCharacter->target_maker_object->Destroy();
					myCharacter->target_maker_object = NULL;
				}
				if (myCharacter->mySessionID == sc_damage_monster_packet->attack_sessionID)
				{

					switch (sc_damage_monster_packet->item)
					{
					case DROP_ITEM::A_COIN:
					{
						Aa_coin* spawned_a_coin = GetWorld()->SpawnActor<Aa_coin>(spawn_a_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_a_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					case DROP_ITEM::B_COIN:
					{
						Ab_coin* spawned_b_coin = GetWorld()->SpawnActor<Ab_coin>(spawn_b_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_b_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					case DROP_ITEM::C_COIN:
					{
						Ac_coin* spawned_c_coin = GetWorld()->SpawnActor<Ac_coin>(spawn_c_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_c_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					default:
						break;
					}
				}
			}
			bexist = true;
			break;
		}
		if (false == bexist) {
			Afirst_water_monster* spawnMonster = GetWorld()->SpawnActor<Afirst_water_monster>(SpawnToFirstWaterMonster, spawnLocationM, spawnRotationM, spawnParamM);
			spawnMonster->sessionID = sc_damage_monster_packet->sessionID;
			spawnMonster->hp = sc_damage_monster_packet->hp;
			spawnMonster->max_hp = 100;
			if (spawnMonster->hp <= 0)
			{
				FActorSpawnParameters spawnParam;
				FVector spawnLocation = spawnMonster->GetActorLocation();
				spawnMonster->Destroy();
				myCharacter->is_target_locked = false;
				if (myCharacter->target_maker_object->IsValidLowLevel())
				{
					myCharacter->target_maker_object->Destroy();
					myCharacter->target_maker_object = NULL;
				}
				if (myCharacter->mySessionID == sc_damage_monster_packet->attack_sessionID)
				{
					switch (sc_damage_monster_packet->item)
					{
					case DROP_ITEM::A_COIN:
					{
						Aa_coin* spawned_a_coin = GetWorld()->SpawnActor<Aa_coin>(spawn_a_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_a_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					case DROP_ITEM::B_COIN:
					{
						Ab_coin* spawned_b_coin = GetWorld()->SpawnActor<Ab_coin>(spawn_b_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_b_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					case DROP_ITEM::C_COIN:
					{
						Ac_coin* spawned_c_coin = GetWorld()->SpawnActor<Ac_coin>(spawn_c_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_c_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					default:
						break;
					}
				}
			}
		}
		break;
	}
	case MONSTER_TYPE::S_WATER:
	{
		bool bexist = false;
		TArray<AActor*> AllMonster;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Asecond_water_monster::StaticClass(), AllMonster);
		for (auto& monster : AllMonster) {
			Asecond_water_monster* thisMonster = Cast<Asecond_water_monster>(monster);
			if (sc_damage_monster_packet->sessionID != thisMonster->sessionID) continue;
			thisMonster->PlayHit();
			thisMonster->hp = sc_damage_monster_packet->hp;
			if (thisMonster->hp <= 0)
			{
				FActorSpawnParameters spawnParam;
				FVector start = thisMonster->GetActorLocation();
				FVector end = FVector(thisMonster->GetActorLocation().X, thisMonster->GetActorLocation().Y, thisMonster->GetActorLocation().Z - 1000000);
				thisMonster->Destroy();
				FCollisionQueryParams CollisionParams;
				FHitResult HitResult;
				GetWorld()->UWorld::LineTraceSingleByChannel(HitResult, start, end, ECollisionChannel::ECC_Visibility);
				FVector spawnLocation = FVector(HitResult.Location.X, HitResult.Location.Y, HitResult.Location.Z + 20);
				myCharacter->is_target_locked = false;
				if (myCharacter->target_maker_object->IsValidLowLevel())
				{
					myCharacter->target_maker_object->Destroy();
					myCharacter->target_maker_object = NULL;
				}
				if (myCharacter->mySessionID == sc_damage_monster_packet->attack_sessionID)
				{

					switch (sc_damage_monster_packet->item)
					{
					case DROP_ITEM::A_COIN:
					{
						Aa_coin* spawned_a_coin = GetWorld()->SpawnActor<Aa_coin>(spawn_a_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_a_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					case DROP_ITEM::B_COIN:
					{
						Ab_coin* spawned_b_coin = GetWorld()->SpawnActor<Ab_coin>(spawn_b_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_b_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					case DROP_ITEM::C_COIN:
					{
						Ac_coin* spawned_c_coin = GetWorld()->SpawnActor<Ac_coin>(spawn_c_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_c_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					default:
						break;
					}
				}
			}
			bexist = true;
			break;
		}
		if (false == bexist) {
			Asecond_water_monster* spawnMonster = GetWorld()->SpawnActor<Asecond_water_monster>(SpawnToSecondWaterMonster, spawnLocationM, spawnRotationM, spawnParamM);
			spawnMonster->sessionID = sc_damage_monster_packet->sessionID;
			spawnMonster->hp = sc_damage_monster_packet->hp;
			spawnMonster->max_hp = 200;
			if (spawnMonster->hp <= 0)
			{
				FActorSpawnParameters spawnParam;
				FVector spawnLocation = spawnMonster->GetActorLocation();
				spawnMonster->Destroy();
				myCharacter->is_target_locked = false;
				if (myCharacter->target_maker_object->IsValidLowLevel())
				{
					myCharacter->target_maker_object->Destroy();
					myCharacter->target_maker_object = NULL;
				}
				if (myCharacter->mySessionID == sc_damage_monster_packet->attack_sessionID)
				{
					switch (sc_damage_monster_packet->item)
					{
					case DROP_ITEM::A_COIN:
					{
						Aa_coin* spawned_a_coin = GetWorld()->SpawnActor<Aa_coin>(spawn_a_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_a_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					case DROP_ITEM::B_COIN:
					{
						Ab_coin* spawned_b_coin = GetWorld()->SpawnActor<Ab_coin>(spawn_b_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_b_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					case DROP_ITEM::C_COIN:
					{
						Ac_coin* spawned_c_coin = GetWorld()->SpawnActor<Ac_coin>(spawn_c_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_c_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					default:
						break;
					}
				}
			}
		}
		break;
	}
	case MONSTER_TYPE::T_WATER:
	{
		bool bexist = false;
		TArray<AActor*> AllMonster;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Athird_water_monster::StaticClass(), AllMonster);
		for (auto& monster : AllMonster) {
			Athird_water_monster* thisMonster = Cast<Athird_water_monster>(monster);
			if (sc_damage_monster_packet->sessionID != thisMonster->sessionID) continue;
			thisMonster->PlayHit();
			thisMonster->hp = sc_damage_monster_packet->hp;
			if (thisMonster->hp <= 0)
			{
				FActorSpawnParameters spawnParam;
				FVector start = thisMonster->GetActorLocation();
				FVector end = FVector(thisMonster->GetActorLocation().X, thisMonster->GetActorLocation().Y, thisMonster->GetActorLocation().Z - 1000000);
				thisMonster->Destroy();
				FCollisionQueryParams CollisionParams;
				FHitResult HitResult;
				GetWorld()->UWorld::LineTraceSingleByChannel(HitResult, start, end, ECollisionChannel::ECC_Visibility);
				FVector spawnLocation = FVector(HitResult.Location.X, HitResult.Location.Y, HitResult.Location.Z + 50);
				myCharacter->is_target_locked = false;
				if (myCharacter->target_maker_object->IsValidLowLevel())
				{
					myCharacter->target_maker_object->Destroy();
					myCharacter->target_maker_object = NULL;
				}
				if (myCharacter->mySessionID == sc_damage_monster_packet->attack_sessionID)
				{

					switch (sc_damage_monster_packet->item)
					{
					case DROP_ITEM::A_COIN:
					{
						Aa_coin* spawned_a_coin = GetWorld()->SpawnActor<Aa_coin>(spawn_a_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_a_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					case DROP_ITEM::B_COIN:
					{
						Ab_coin* spawned_b_coin = GetWorld()->SpawnActor<Ab_coin>(spawn_b_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_b_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					case DROP_ITEM::C_COIN:
					{
						Ac_coin* spawned_c_coin = GetWorld()->SpawnActor<Ac_coin>(spawn_c_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_c_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					default:
						break;
					}
				}
			}
			bexist = true;
			break;
		}
		if (false == bexist) {
			Athird_water_monster* spawnMonster = GetWorld()->SpawnActor<Athird_water_monster>(SpawnToThirdWaterMonster, spawnLocationM, spawnRotationM, spawnParamM);
			spawnMonster->sessionID = sc_damage_monster_packet->sessionID;
			spawnMonster->hp = sc_damage_monster_packet->hp;
			spawnMonster->max_hp = 400;
			if (spawnMonster->hp <= 0)
			{
				FActorSpawnParameters spawnParam;
				FVector spawnLocation = spawnMonster->GetActorLocation();
				spawnMonster->Destroy();
				myCharacter->is_target_locked = false;
				if (myCharacter->target_maker_object->IsValidLowLevel())
				{
					myCharacter->target_maker_object->Destroy();
					myCharacter->target_maker_object = NULL;
				}
				if (myCharacter->mySessionID == sc_damage_monster_packet->attack_sessionID)
				{
					switch (sc_damage_monster_packet->item)
					{
					case DROP_ITEM::A_COIN:
					{
						Aa_coin* spawned_a_coin = GetWorld()->SpawnActor<Aa_coin>(spawn_a_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_a_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					case DROP_ITEM::B_COIN:
					{
						Ab_coin* spawned_b_coin = GetWorld()->SpawnActor<Ab_coin>(spawn_b_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_b_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					case DROP_ITEM::C_COIN:
					{
						Ac_coin* spawned_c_coin = GetWorld()->SpawnActor<Ac_coin>(spawn_c_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_c_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					default:
						break;
					}
				}
			}
		}
		break;
	}
	case MONSTER_TYPE::F_FISH:
	{
		bool bexist = false;
		TArray<AActor*> AllMonster;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Afirst_swimming_monster::StaticClass(), AllMonster);
		for (auto& monster : AllMonster) {
			Afirst_swimming_monster* thisMonster = Cast<Afirst_swimming_monster>(monster);
			if (sc_damage_monster_packet->sessionID != thisMonster->sessionID) continue;
			thisMonster->hp = sc_damage_monster_packet->hp;
			if (thisMonster->hp <= 0)
			{
				FActorSpawnParameters spawnParam;
				FVector start = thisMonster->GetActorLocation();
				FVector end = FVector(thisMonster->GetActorLocation().X, thisMonster->GetActorLocation().Y, thisMonster->GetActorLocation().Z - 1000000);
				FVector spawnLocation = thisMonster->GetActorLocation();
				thisMonster->Destroy();
				myCharacter->is_target_locked = false;
				if (myCharacter->target_maker_object->IsValidLowLevel())
				{
					myCharacter->target_maker_object->Destroy();
					myCharacter->target_maker_object = NULL;
				}
				if (myCharacter->mySessionID == sc_damage_monster_packet->attack_sessionID)
				{

					switch (sc_damage_monster_packet->item)
					{
					case DROP_ITEM::A_COIN:
					{
						Aa_coin* spawned_a_coin = GetWorld()->SpawnActor<Aa_coin>(spawn_a_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_a_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					case DROP_ITEM::B_COIN:
					{
						Ab_coin* spawned_b_coin = GetWorld()->SpawnActor<Ab_coin>(spawn_b_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_b_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					case DROP_ITEM::C_COIN:
					{
						Ac_coin* spawned_c_coin = GetWorld()->SpawnActor<Ac_coin>(spawn_c_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_c_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					default:
						break;
					}
				}
			}
			bexist = true;
			break;
		}
		if (false == bexist) {
			Afirst_swimming_monster* spawnMonster = GetWorld()->SpawnActor<Afirst_swimming_monster>(SpawnToFirstFishMonster, spawnLocationM, spawnRotationM, spawnParamM);
			spawnMonster->sessionID = sc_damage_monster_packet->sessionID;
			spawnMonster->hp = sc_damage_monster_packet->hp;
			spawnMonster->max_hp = 100;
			if (spawnMonster->hp <= 0)
			{
				FActorSpawnParameters spawnParam;
				FVector spawnLocation = spawnMonster->GetActorLocation();
				spawnMonster->Destroy();
				myCharacter->is_target_locked = false;
				if (myCharacter->target_maker_object->IsValidLowLevel())
				{
					myCharacter->target_maker_object->Destroy();
					myCharacter->target_maker_object = NULL;
				}
				if (myCharacter->mySessionID == sc_damage_monster_packet->attack_sessionID)
				{
					switch (sc_damage_monster_packet->item)
					{
					case DROP_ITEM::A_COIN:
					{
						Aa_coin* spawned_a_coin = GetWorld()->SpawnActor<Aa_coin>(spawn_a_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_a_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					case DROP_ITEM::B_COIN:
					{
						Ab_coin* spawned_b_coin = GetWorld()->SpawnActor<Ab_coin>(spawn_b_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_b_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					case DROP_ITEM::C_COIN:
					{
						Ac_coin* spawned_c_coin = GetWorld()->SpawnActor<Ac_coin>(spawn_c_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_c_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					default:
						break;
					}
				}
			}
		}
		break;
	}
	case MONSTER_TYPE::S_FISH:
	{
		bool bexist = false;
		TArray<AActor*> AllMonster;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Asecond_swimming_monster::StaticClass(), AllMonster);
		for (auto& monster : AllMonster) {
			Asecond_swimming_monster* thisMonster = Cast<Asecond_swimming_monster>(monster);
			if (sc_damage_monster_packet->sessionID != thisMonster->sessionID) continue;
			thisMonster->hp = sc_damage_monster_packet->hp;
			if (thisMonster->hp <= 0)
			{
				FActorSpawnParameters spawnParam;
				FVector start = thisMonster->GetActorLocation();
				FVector end = FVector(thisMonster->GetActorLocation().X, thisMonster->GetActorLocation().Y, thisMonster->GetActorLocation().Z - 1000000);
				FVector spawnLocation = thisMonster->GetActorLocation();
				thisMonster->Destroy();
				myCharacter->is_target_locked = false;
				if (myCharacter->target_maker_object->IsValidLowLevel())
				{
					myCharacter->target_maker_object->Destroy();
					myCharacter->target_maker_object = NULL;
				}
				if (myCharacter->mySessionID == sc_damage_monster_packet->attack_sessionID)
				{
					switch (sc_damage_monster_packet->item)
					{
					case DROP_ITEM::A_COIN:
					{
						Aa_coin* spawned_a_coin = GetWorld()->SpawnActor<Aa_coin>(spawn_a_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_a_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					case DROP_ITEM::B_COIN:
					{
						Ab_coin* spawned_b_coin = GetWorld()->SpawnActor<Ab_coin>(spawn_b_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_b_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					case DROP_ITEM::C_COIN:
					{
						Ac_coin* spawned_c_coin = GetWorld()->SpawnActor<Ac_coin>(spawn_c_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_c_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					default:
						break;
					}
				}
			}
			bexist = true;
			break;
		}
		if (false == bexist) {
			Asecond_swimming_monster* spawnMonster = GetWorld()->SpawnActor<Asecond_swimming_monster>(SpawnToSecondFishMonster, spawnLocationM, spawnRotationM, spawnParamM);
			spawnMonster->sessionID = sc_damage_monster_packet->sessionID;
			spawnMonster->hp = sc_damage_monster_packet->hp;
			spawnMonster->max_hp = 200;
			if (spawnMonster->hp <= 0)
			{
				FActorSpawnParameters spawnParam;
				FVector spawnLocation = spawnMonster->GetActorLocation();
				spawnMonster->Destroy();
				myCharacter->is_target_locked = false;
				if (myCharacter->target_maker_object->IsValidLowLevel())
				{
					myCharacter->target_maker_object->Destroy();
					myCharacter->target_maker_object = NULL;
				}
				if (myCharacter->mySessionID == sc_damage_monster_packet->attack_sessionID)
				{
					switch (sc_damage_monster_packet->item)
					{
					case DROP_ITEM::A_COIN:
					{
						Aa_coin* spawned_a_coin = GetWorld()->SpawnActor<Aa_coin>(spawn_a_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_a_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					case DROP_ITEM::B_COIN:
					{
						Ab_coin* spawned_b_coin = GetWorld()->SpawnActor<Ab_coin>(spawn_b_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_b_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					case DROP_ITEM::C_COIN:
					{
						Ac_coin* spawned_c_coin = GetWorld()->SpawnActor<Ac_coin>(spawn_c_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_c_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					default:
						break;
					}
				}
			}
		}
		break;
	}
	case MONSTER_TYPE::T_FISH:
	{
		bool bexist = false;
		TArray<AActor*> AllMonster;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Athird_swimming_monster::StaticClass(), AllMonster);
		for (auto& monster : AllMonster) {
			Athird_swimming_monster* thisMonster = Cast<Athird_swimming_monster>(monster);
			if (sc_damage_monster_packet->sessionID != thisMonster->sessionID) continue;
			thisMonster->hp = sc_damage_monster_packet->hp;
			if (thisMonster->hp <= 0)
			{
				FActorSpawnParameters spawnParam;
				FVector start = thisMonster->GetActorLocation();
				FVector end = FVector(thisMonster->GetActorLocation().X, thisMonster->GetActorLocation().Y, thisMonster->GetActorLocation().Z - 1000000);
				FVector spawnLocation = thisMonster->GetActorLocation();
				thisMonster->Destroy();
				myCharacter->is_target_locked = false;
				if (myCharacter->target_maker_object->IsValidLowLevel())
				{
					myCharacter->target_maker_object->Destroy();
					myCharacter->target_maker_object = NULL;
				}
				if (myCharacter->mySessionID == sc_damage_monster_packet->attack_sessionID)
				{
					switch (sc_damage_monster_packet->item)
					{
					case DROP_ITEM::A_COIN:
					{
						Aa_coin* spawned_a_coin = GetWorld()->SpawnActor<Aa_coin>(spawn_a_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_a_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					case DROP_ITEM::B_COIN:
					{
						Ab_coin* spawned_b_coin = GetWorld()->SpawnActor<Ab_coin>(spawn_b_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_b_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					case DROP_ITEM::C_COIN:
					{
						Ac_coin* spawned_c_coin = GetWorld()->SpawnActor<Ac_coin>(spawn_c_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_c_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					default:
						break;
					}
				}
			}
			bexist = true;
			break;
		}
		if (false == bexist) {
			Athird_swimming_monster* spawnMonster = GetWorld()->SpawnActor<Athird_swimming_monster>(SpawnToThirdFishMonster, spawnLocationM, spawnRotationM, spawnParamM);
			spawnMonster->sessionID = sc_damage_monster_packet->sessionID;
			spawnMonster->hp = sc_damage_monster_packet->hp;
			spawnMonster->max_hp = 400;
			if (spawnMonster->hp <= 0)
			{
				FActorSpawnParameters spawnParam;
				FVector spawnLocation = spawnMonster->GetActorLocation();
				spawnMonster->Destroy();
				myCharacter->is_target_locked = false;
				if (myCharacter->target_maker_object->IsValidLowLevel())
				{
					myCharacter->target_maker_object->Destroy();
					myCharacter->target_maker_object = NULL;
				}
				if (myCharacter->mySessionID == sc_damage_monster_packet->attack_sessionID)
				{
					switch (sc_damage_monster_packet->item)
					{
					case DROP_ITEM::A_COIN:
					{
						Aa_coin* spawned_a_coin = GetWorld()->SpawnActor<Aa_coin>(spawn_a_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_a_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					case DROP_ITEM::B_COIN:
					{
						Ab_coin* spawned_b_coin = GetWorld()->SpawnActor<Ab_coin>(spawn_b_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_b_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					case DROP_ITEM::C_COIN:
					{
						Ac_coin* spawned_c_coin = GetWorld()->SpawnActor<Ac_coin>(spawn_c_coin, spawnLocation, FRotator::ZeroRotator, spawnParam);
						spawned_c_coin->session_id = sc_damage_monster_packet->attack_sessionID;
						break;
					}
					default:
						break;
					}
				}
			}
		}
		break;
	}
	default:
		break;
	}
	delete sc_damage_monster_packet;
	sc_damage_monster_state = false;
}

void AMainGamePlayerController::GetItemProcess()
{
	TArray<AActor*> AllPlayers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyCharacter::StaticClass(), AllPlayers);
	for (auto& player : AllPlayers) {
		AMyCharacter* thisPlayer = Cast<AMyCharacter>(player);
		if (sc_get_item_packet->sessionID != thisPlayer->mySessionID) continue;
		thisPlayer->EquipCoinAnim();
		thisPlayer->a_coin = sc_get_item_packet->a_coin;
		thisPlayer->b_coin = sc_get_item_packet->b_coin;
		thisPlayer->c_coin = sc_get_item_packet->c_coin;
		break;
	}
	delete sc_get_item_packet;
	sc_get_item_state = false;
}

void AMainGamePlayerController::GetCoinPriceProcess()
{
	char* ptr = strtok(sc_coin_price_packet->coin_data, ",");

	string a_coin_name_str(ptr);
	a_coin.coin_name = *FString(a_coin_name_str.c_str());  // 자산

	ptr = strtok(NULL, ",");
	string a_coin_price_str(ptr);
	a_coin.closing_price = stoi(a_coin_price_str);  // 현재가

	ptr = strtok(NULL, ",");
	string a_coin_min_price_str(ptr);
	a_coin.min_price = stoi(a_coin_min_price_str);  // 저가(당일)

	ptr = strtok(NULL, ",");
	string a_coin_max_price_str(ptr);
	a_coin.max_price = stoi(a_coin_max_price_str);  // 고가(당일)

	ptr = strtok(NULL, ",");
	string a_coin_prev_closing_price_str(ptr);
	float a_coin_prev_closing_price_str_f = stof(a_coin_prev_closing_price_str);
	a_coin.prev_closing_price = a_coin_prev_closing_price_str_f;  // 전일 종가

	ptr = strtok(NULL, ",");
	string a_coin_units_traded_24H_str(ptr);
	float a_coin_units_traded_24H_f = stof(a_coin_units_traded_24H_str);
	a_coin.units_traded_24H = a_coin_units_traded_24H_f;  // 거래량(24h)

	ptr = strtok(NULL, ",");
	string a_coin_acc_trade_value_24H_str(ptr);
	float a_coin_acc_trade_value_24H_f = stof(a_coin_acc_trade_value_24H_str);
	a_coin.acc_trade_value_24H = a_coin_acc_trade_value_24H_f / 1000000;  // 거래금액(24h)

	ptr = strtok(NULL, ",");
	string a_coin_fluctate_str(ptr);
	a_coin.fluctate_24H = stoi(a_coin_fluctate_str);  // 변동금액(24h)

	ptr = strtok(NULL, ",");
	string a_coin_fluctate_rate_24H_str(ptr);
	a_coin.fluctate_rate_24H = stof(a_coin_fluctate_rate_24H_str);  // 변동률(24h)

	/* b coin */
	ptr = strtok(NULL, ",");
	string b_coin_name_str(ptr);
	b_coin.coin_name = *FString(b_coin_name_str.c_str());  // 자산

	ptr = strtok(NULL, ",");
	string b_coin_price_str(ptr);
	b_coin.closing_price = stoi(b_coin_price_str);  // 현재가

	ptr = strtok(NULL, ",");
	string b_coin_min_price_str(ptr);
	b_coin.min_price = stoi(b_coin_min_price_str);  // 저가(당일)

	ptr = strtok(NULL, ",");
	string b_coin_max_price_str(ptr);
	b_coin.max_price = stoi(b_coin_max_price_str);  // 고가(당일)

	ptr = strtok(NULL, ",");
	string b_coin_prev_closing_price_str(ptr);
	float b_coin_prev_closing_price_str_f = stof(b_coin_prev_closing_price_str);
	b_coin.prev_closing_price = b_coin_prev_closing_price_str_f;  // 전일 종가

	ptr = strtok(NULL, ",");
	string b_coin_units_traded_24H_str(ptr);
	float b_coin_units_traded_24H_f = stof(b_coin_units_traded_24H_str);
	b_coin.units_traded_24H = b_coin_units_traded_24H_f;  // 거래량(24h)

	ptr = strtok(NULL, ",");
	string b_coin_acc_trade_value_24H_str(ptr);
	float b_coin_acc_trade_value_24H_f = stof(b_coin_acc_trade_value_24H_str);
	b_coin.acc_trade_value_24H = b_coin_acc_trade_value_24H_f / 1000000;  // 거래금액(24h)

	ptr = strtok(NULL, ",");
	string b_coin_fluctate_str(ptr);
	b_coin.fluctate_24H = stoi(b_coin_fluctate_str);  // 변동금액(24h)

	ptr = strtok(NULL, ",");
	string b_coin_fluctate_rate_24H_str(ptr);
	b_coin.fluctate_rate_24H = stof(b_coin_fluctate_rate_24H_str);  // 변동률(24h)

	/* c coin */
	ptr = strtok(NULL, ",");
	string c_coin_name_str(ptr);
	c_coin.coin_name = *FString(c_coin_name_str.c_str());  // 자산

	ptr = strtok(NULL, ",");
	string c_coin_price_str(ptr);
	c_coin.closing_price = stoi(c_coin_price_str);  // 현재가

	ptr = strtok(NULL, ",");
	string c_coin_min_price_str(ptr);
	c_coin.min_price = stoi(c_coin_min_price_str);  // 저가(당일)

	ptr = strtok(NULL, ",");
	string c_coin_max_price_str(ptr);
	c_coin.max_price = stoi(c_coin_max_price_str);  // 고가(당일)

	ptr = strtok(NULL, ",");
	string c_coin_prev_closing_price_str(ptr);
	float c_coin_prev_closing_price_str_f = stof(c_coin_prev_closing_price_str);
	c_coin.prev_closing_price = c_coin_prev_closing_price_str_f;  // 전일 종가

	ptr = strtok(NULL, ",");
	string c_coin_units_traded_24H_str(ptr);
	float c_coin_units_traded_24H_f = stof(c_coin_units_traded_24H_str);
	c_coin.units_traded_24H = c_coin_units_traded_24H_f;  // 거래량(24h)

	ptr = strtok(NULL, ",");
	string c_coin_acc_trade_value_24H_str(ptr);
	float c_coin_acc_trade_value_24H_f = stof(c_coin_acc_trade_value_24H_str);
	c_coin.acc_trade_value_24H = c_coin_acc_trade_value_24H_f / 1000000;  // 거래금액(24h)

	ptr = strtok(NULL, ",");
	string c_coin_fluctate_str(ptr);
	c_coin.fluctate_24H = stoi(c_coin_fluctate_str);  // 변동금액(24h)

	ptr = strtok(NULL, ",");
	string c_coin_fluctate_rate_24H_str(ptr);
	c_coin.fluctate_rate_24H = stof(c_coin_fluctate_rate_24H_str);  // 변동률(24h)

	

	coin_map_ui_object->get_data = true;

	delete sc_coin_price_packet;
	sc_get_coin_price_state = false;
}

void AMainGamePlayerController::ItemBuyProcess()
{
	if (myCharacter->mySessionID == sc_item_buy_packet->sessionID) {
		switch (sc_item_buy_packet->item_type)
		{
		case ITEM_TYPE::CRITICAL_UP:
		{
			myCharacter->inventory_component->AddtoInventory(0, 1);
			break;
		}
		case ITEM_TYPE::SPEED_UP:
		{
			myCharacter->inventory_component->AddtoInventory(1, 1);
			break;
		}
		case ITEM_TYPE::ATTACK_UP:
		{
			myCharacter->inventory_component->AddtoInventory(2, 1);
			break;
		}
		case ITEM_TYPE::HP_UP:
		{
			myCharacter->inventory_component->AddtoInventory(3, 1);
			break;
		}
		case ITEM_TYPE::RECOVER_UP:
		{
			myCharacter->inventory_component->AddtoInventory(4, 1);
			break;
		}
		case ITEM_TYPE::SNIPER_UP:
		{
			myCharacter->inventory_component->AddtoInventory(5, 1);
			break;
		}
		case ITEM_TYPE::ATTACK_HP_UP:
		{
			myCharacter->inventory_component->AddtoInventory(6, 1);
			break;
		}
		case ITEM_TYPE::LAUNCHER_UP:
		{
			myCharacter->inventory_component->AddtoInventory(7, 1);
			break;
		}
		case ITEM_TYPE::LAUNCHER_RANGE_UP:
		{
			myCharacter->inventory_component->AddtoInventory(8, 1);
			break;
		}
		case ITEM_TYPE::JUMP_UP:
		{
			myCharacter->inventory_component->AddtoInventory(9, 1);
			break;
		}
		case ITEM_TYPE::MISSILE_UP:
		{
			myCharacter->inventory_component->AddtoInventory(10, 1);
			break;
		}
		case ITEM_TYPE::SLASH_UP:
		{
			myCharacter->inventory_component->AddtoInventory(11, 1);
			break;
		}
		case ITEM_TYPE::SLASH_SIZE_UP:
		{
			myCharacter->inventory_component->AddtoInventory(12, 1);
			break;
		}
		case ITEM_TYPE::ULTIMATE_UP:
		{
			myCharacter->inventory_component->AddtoInventory(13, 1);
			break;
		}
		default:
			break;
		}
		myCharacter->money = sc_item_buy_packet->gold;

		Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
		GameInstanceRef->player_money = myCharacter->money;

		GameInstanceRef->money_set = true;
		
		play_shop_ui_object->UpdatePlayerWallet();
	}
	delete sc_item_buy_packet;
	sc_item_buy_state = false;
}

void AMainGamePlayerController::BuySellProcess()
{
	if (myCharacter->mySessionID == sc_buy_sell_packet->sessionID) {
		myCharacter->a_coin = sc_buy_sell_packet->a_coin;
		myCharacter->b_coin = sc_buy_sell_packet->b_coin;
		myCharacter->c_coin = sc_buy_sell_packet->c_coin;
		myCharacter->money = sc_buy_sell_packet->gold;

		Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
		GameInstanceRef->money_set = true;
	}
			
	delete sc_buy_sell_packet;
	sc_buy_sell_state = false;
}

void AMainGamePlayerController::MonsterAttackProcess()
{
	if (!myCharacter->is_respawning) 
	{
		myCharacter->health -= sc_monster_attack_packet->damage;

		Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
		GameInstanceRef->hp_set = true;

		FTimerHandle handle;
		GetWorld()->GetTimerManager().SetTimer(handle, myCharacter, &AMyCharacter::BeHit, 0.25f, false);
	}

	delete sc_monster_attack_packet;
	sc_monster_attack_state = false;
}

void AMainGamePlayerController::QuestProcess()
{
	Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if ((0 <= sc_quest_packet->quest_level && sc_quest_packet->quest_level <= 5) && (GameInstanceRef->quest_level + 1 == sc_quest_packet->quest_level)) {
		play_map_ui_object->QuestAlarm();
	}

	GameInstanceRef->quest_level = sc_quest_packet->quest_level;
	GameInstanceRef->quest_goal_rate = sc_quest_packet->goal_rate;
	GameInstanceRef->quest_now_rate = sc_quest_packet->now_rate;

	delete sc_quest_packet;
	sc_quest_state = false;
}

// 그 외 함수
void AMainGamePlayerController::SendPlayerInfo()
{
	if (true == myCharacter->use)
	{
		Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
		switch (GameInstanceRef->mycharacter_type)
		{
		case CHARACTER_TYPE::HUMAN:
		{
			client->SendToMove(myCharacter);
			break; 
		}
		case CHARACTER_TYPE::SPACESHIP:
			move_map_name = GetWorld()->GetMapName();
			if (myCharacter->spaceship != NULL)
				client->SendToMove(myCharacter->spaceship);
			break;
		default:
		
			break;
		}
	}
}

void AMainGamePlayerController::SendGetCoinPriceInfo()
{
	if (true == myCharacter->use)
	{

		CS_COIN_PRICE_PACKET coin_price_packet;
		coin_price_packet.size = sizeof(CS_COIN_PRICE_PACKET);
		coin_price_packet.type = CS_COIN_PRICE;

		Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
		switch (GameInstanceRef->mycharacter_type)
		{
		case CHARACTER_TYPE::HUMAN:
		{
			AMyCharacter* player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			coin_price_packet.sessionID = player->mySessionID;
			break;
		}
		case CHARACTER_TYPE::SPACESHIP:
		{
			Aspace_ship* ship = Cast<Aspace_ship>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			coin_price_packet.sessionID = ship->owner_session_id;
			break;
		}
		default:
			break;
		}

		client->SendToGetCoinPirce(coin_price_packet);
	}
}

int AMainGamePlayerController::ReturnSessionID()
{
	return myCharacter->mySessionID;
}

void AMainGamePlayerController::SetLoadingUI()
{
	play_map_ui_object->LoadingUI();
}
