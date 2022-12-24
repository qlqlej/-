// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyCharacter.h"
#include "..\..\..\SpaceCoin_Server\SpaceCoin_Server\protocol.h"
#include "MainGamePlayerController.generated.h"

/**
 *
 */
UCLASS()
class SPACE_COIN_API AMainGamePlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	FTimerHandle PlayerInfoHandle;
	FTimerHandle CoinMapUIHandle;
	FVector DestLocation;

	AMainGamePlayerController();
	virtual void OnPossess(APawn* aPawn) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class ACharacter> SpawnToOtherPlayer;
	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class Aspace_ship> SpawnToOtherSpaceShip;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class ACharacter> SpawnToFirstIceMonster;
	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class ACharacter> SpawnToSecondIceMonster;
	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class ACharacter> SpawnToThirdIceMonster;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class ACharacter> SpawnToFirstSandMonster;
	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class ACharacter> SpawnToSecondSandMonster;
	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class ACharacter> SpawnToThirdSandMonster;

	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class ACharacter> SpawnToFirstWaterMonster;
	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class ACharacter> SpawnToSecondWaterMonster;
	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class ACharacter> SpawnToThirdWaterMonster;

	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class ACharacter> SpawnToFirstFishMonster;
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class ACharacter> SpawnToSecondFishMonster;
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class ACharacter> SpawnToThirdFishMonster;

	// ��Ŷ������ ����� �Լ�
	void SetLoginInfo(SC_LOGIN_INFO_PACKET* packet);
	void SetAddPlayer(SC_ADD_PLAYER_PACKET* packet);
	void UpdatePlayerToMove(SC_MOVE_PLAYER_PACKET* packet);
	void RemovePlayer(SC_REMOVE_PLAYER_PACKET* packet);
	void SetAddMonster(SC_MONSTER_INFO_PACKET* packet);
	void UpdateMonsterToMove(SC_MOVE_MONSTER_PACKET* packet);
	void RemoveMonster(SC_REMOVE_MONSTER_PACKET* packet);
	void AttackMonster(SC_ATTACK_MONSTER_PACKET* packet);
	void ChangeCharacterState(SC_CHANGE_CHARACTER_PACKET* packet);
	void AttackSkill(SC_ATTACK_SKILL_PACKET* packet);
	void SpawnSpaceship(SC_SPAWN_SPACESHIP_PACKET* packet);
	void CHangeMap(SC_CHANGE_MAP_PACKET* packet);
	void MonsterDamage(SC_DAMAGE_MONSTER_PACKET* packet);
	void GetItem(SC_GET_ITEM_PACKET* packet);
	void GetCoinPrice(SC_COIN_PRICE_PACKET* packet);
	void ItemBuy(SC_ITEM_BUY_PACKET* packet);
	void BuySell(SC_BUY_SELL_PACKET* packet);
	void MonsterAttack(SC_MONSTER_ATTACK_PACKET* packet);
	void Quest(SC_QUEST_PACKET* packet);

	// ����� ��Ŷ ������ Ȱ�� �Լ�
	void LoginProcess();
	void AddPlayerProcess();
	void PlayerMoveProcess();
	void RemovePlayerProcess();
	void AddMonsterProcess();
	void MonsterMoveProcess();
	void RemoveMonsterProcess();
	void AttackMonsterProcess();
	void ChangeCharaterProcess();
	void ChangeWeaponProcess();
	void AttackSkillProcess();
	void SpawnShipProcess();
	void ChangeMapProcess();
	void MonsterDamageProcess();
	void GetItemProcess();
	void GetCoinPriceProcess();
	void ItemBuyProcess();
	void BuySellProcess();
	void MonsterAttackProcess();
	void QuestProcess();

	bool sc_monster_info_state = false;
	FVector speed_second;
	FRotator rotation_second;
	float update_time;
	bool sc_dash_state = false;
	bool inventory_visible = false;
	bool shop_visible = false;

	bool coin_map_ui_visible = false;
	bool setting_ui_visible = false;
	bool quest_ui_visible = false;

	FString map_name = "WaterPlanet";
	FString move_map_name;
	bool not_equal;
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class Uui_play_map> play_map_ui_class;

	class Uui_play_map* play_map_ui_object;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class Uui_coin_map> coin_map_ui_class;

	class Uui_coin_map* coin_map_ui_object;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class Uui_setting> setting_ui_class;

	class Uui_setting* setting_ui_object;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class Uui_quest_map> quest_map_ui_class;

	class Uui_quest_map* quest_map_ui_object;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class Uskillui> play_skill_class;

	class Uskillui* play_skill_ui_object;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class Ucrosshair_ui> crosshair_class;

	class Ucrosshair_ui* crosshair_ui_object;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class Ushop_ui> play_shop_class;

	class Ushop_ui* play_shop_ui_object;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class Uinventory_ui> play_inventory_class;

	class Uinventory_ui* play_inventory_ui_object;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class Udamage_number_ui> damage_number_class;

	class Udamage_number_ui* damage_number_ui_object;
	
	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class Aa_coin> spawn_a_coin;
	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class Ab_coin> spawn_b_coin;
	UPROPERTY(EditAnywhere, Category = "Spawning")
		TSubclassOf<class Ac_coin> spawn_c_coin;
	
	//class UDataTable* item_data_table;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Sound)
	TSubclassOf<class USoundMix> bgm_sound_mix;

	USoundMix* bgm_sound_mix_c;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Sound)
	TSubclassOf<class USoundClass> bgm_sound_class;

	USoundClass* bgm_sound_class_c;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Sound)
	TSubclassOf<class USoundMix> sfx_sound_mix;

	USoundMix* sfx_sound_mix_c;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Sound)
	TSubclassOf<class USoundClass> sfx_sound_class;

	USoundClass* sfx_sound_class_c;


private:
	bool sc_login_info_state = false;
	bool sc_add_player_state = false;
	bool sc_move_player_state = false;
	bool sc_remove_player_state = false;
	bool sc_move_monster_state = false;
	bool sc_remove_monster_state = false;
	bool sc_attack_monster_state = false;
	bool sc_character_state = false;
	bool sc_weapon_state = false;
	bool sc_attack_skill_state = false;
	bool sc_spawn_spaceship_state = false;
	bool sc_change_map_state = false;
	bool sc_damage_monster_state = false;
	bool sc_get_item_state = false;
	bool sc_get_coin_price_state = false;
	bool sc_item_buy_state = false;
	bool sc_buy_sell_state = false;
	bool sc_monster_attack_state = false;
	bool sc_quest_state = false;

	SC_LOGIN_INFO_PACKET* sc_login_info_packet;
	SC_ADD_PLAYER_PACKET* sc_add_player_packet;
	SC_MOVE_PLAYER_PACKET* sc_move_player_packet;
	SC_REMOVE_PLAYER_PACKET* sc_remove_player_packet;
	SC_MONSTER_INFO_PACKET* sc_monster_info_packet;
	SC_MOVE_MONSTER_PACKET* sc_move_monster_packet;
	SC_REMOVE_MONSTER_PACKET* sc_remove_monster_packet;
	SC_ATTACK_MONSTER_PACKET* sc_attack_monster_packet;
	SC_CHANGE_CHARACTER_PACKET* sc_change_character_packet;
	SC_ATTACK_SKILL_PACKET* sc_attack_skill_packet;
	SC_SPAWN_SPACESHIP_PACKET* sc_spawn_spaceship_packet;
	SC_CHANGE_MAP_PACKET* sc_change_map_packet;
	SC_DAMAGE_MONSTER_PACKET* sc_damage_monster_packet;
	SC_GET_ITEM_PACKET* sc_get_item_packet;
	SC_COIN_PRICE_PACKET* sc_coin_price_packet;
	SC_ITEM_BUY_PACKET* sc_item_buy_packet;
	SC_BUY_SELL_PACKET* sc_buy_sell_packet;
	SC_MONSTER_ATTACK_PACKET* sc_monster_attack_packet;
	SC_QUEST_PACKET* sc_quest_packet;

	AMyCharacter* myCharacter;
	void SendPlayerInfo();

	void SendGetCoinPriceInfo();

public:
	struct COIN_INFO {
		FString			coin_name;  // 이름
		int32			opening_price;  // 시가 00시 기준
		int32			closing_price;  // 종가 00시 기준
		int32			min_price;  // 저가 00시 기준
		int32			max_price;  // 고가 00시 기준
		float			units_traded;  // 거래량 00시 기준
		int32			acc_trade_value;  // 전일종가
		float			prev_closing_price;  // 거래금액 00시 기준
		float			units_traded_24H;  // 최근 24시간 거래량 
		float			acc_trade_value_24H;  // 최근 24시간 거래금액
		int32			fluctate_24H;  // 최근 24시간 변동가
		float			fluctate_rate_24H;  // 최근 24시간 변동률

	};

public:
	COIN_INFO a_coin;
	COIN_INFO b_coin;
	COIN_INFO c_coin;

	bool get_coin_api_first_time = false;

public:
	int ReturnSessionID();

	void SetLoadingUI();

};
