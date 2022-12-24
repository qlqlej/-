#pragma once

#include "game_info.h"
#include "Engine/GameInstance.h"
#include "Client.h"
#include "game_instance.generated.h"

USTRUCT(BlueprintType)
struct FMonsterInfo : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	float attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	float skill;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	float armor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	int32 hp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	int32 max_hp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	int32 mp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	int32 max_mp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	float trace_range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	float attack_range;
};

UCLASS()
class SPACE_COIN_API Ugame_instance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	Ugame_instance();
	~Ugame_instance();

public:
	bool bLoginInfo = false;
	bool bLogin = false;
	bool bChangeMap = false;
	int mySessionID = -1;
	bool testlogin = false;
	bool map_checking = false;
	FVector test;
	MAP_TYPE test_map;

	Client* client;
	SC_LOGIN_INFO_PACKET sc_login_info_packet;
	SC_CHANGE_MAP_PACKET sc_change_map;

	CHARACTER_TYPE mycharacter_type;

	int quest_level;
	int quest_now_rate = 0;
	int quest_goal_rate = 0;


private:
	UPROPERTY()
	UDataTable* monster_info_table;

	UPROPERTY()
	UDataTable* player_info_table;

public:
	float x;
	float y;
	float z;
	short player_sessionID;
	FString player_name;
	WEAPON_TYPE player_weapon_type;
	float player_health;
	int32 player_money;
	int32 player_a_coin;
	int32 player_b_coin;
	int32 player_c_coin;
	int32 critical_up;
	int32 attack_up;
	int32 speed_up;
	int32 hp_up;
	int32 recover_hp_up;
	int32 sniper_up;
	int32 attack_hp_up;
	int32 launcher_up;
	int32 launcher_range_up;
	int32 jump_up;
	int32 missile_up;
	int32 slash_up;
	int32 slash_size_up;
	int32 ultimate_up;
	float bgm_vloume;
	float sfx_vloume;

public:
	bool name_set = false;
	bool money_set = false;
	bool hp_set = false;

	bool change_map = false;

	FString map_name;
protected:
	virtual void Init();
	virtual void Shutdown() override;

public:
	const FMonsterInfo* FindMonsterInfo(const FName& key) const;
	void SetLoginInfoData(SC_LOGIN_INFO_PACKET* packet);
	void SendToChangeCharacterState(CS_CHANGE_CHARACTER_PACKET packet);
	void SendToAttackSkill(CS_ATTACK_SKILL_PACKET packet);

	short GetPlayerSessionID();
	FString GetPlayerName();

};
