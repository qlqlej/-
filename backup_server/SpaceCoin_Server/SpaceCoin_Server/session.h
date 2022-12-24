#pragma once
#include "extended_overlapped.h"
#include "monster.h"
#include "protocol.h"

#define DELAY_TIME 50

class SESSION {
private:
	EXT_OVER			ext_over;
	SOCKET				socket;
	bool				use_check;
	int					sessionID;
	int					prev_remain_data;
	char				ID[MAX_ID_LEN];
	char				name[MAX_NAME_LEN];
	CHARACTER_TYPE		characterType;
	MAP_TYPE			map;
	WEAPON_TYPE			weapon_type;
	float				x, y, z;
	float				pitch, yaw, roll;
	float				cpitch, cyaw, croll;
	float				vx, vy, vz;
	float				ship_speed;
	SESSION_STATE		sessionState;
public:
	SESSION() : socket(0), map(MAP_TYPE::NOT_MAP), use_check(false), sessionID(-1), prev_remain_data(0), sessionState(SESSION_STATE::FREE){}
	~SESSION() {}


	// юс╫ц
	int				critical_up = 0, speed_up = 0, attack_up = 0, hp_up = 0, recover_hp_up = 0;
	int				sniper_up = 0, attack_hp_up = 0, launcher_up = 0, launcher_range_up = 0, jump_up = 0;
	float			hp;
	int				a_coin, b_coin, c_coin, gold;
	mutex				ml;
	mutex				sl;
	unordered_set<int>	view_list;
	mutex				vl;
	unordered_set<int>	monster_view_list;
	mutex				mvl;
	mutex				il;
	system_clock::time_point shield_time;

	EXT_OVER* GetExtOver() { return &ext_over; }
	SOCKET GetSocket() { return socket; }
	bool GetUseCheck() { return use_check; }
	int GetSessionID() { return sessionID; }
	int GetPrevRemainData() { return prev_remain_data; }
	char* GetID() { return ID; }
	char* GetName() { return name; }
	CHARACTER_TYPE GetCharacterType() { return characterType; }
	MAP_TYPE GetMap() { return map; }
	WEAPON_TYPE GetWeaponType() { return weapon_type; }
	float GetX() { return x; }
	float GetY() { return y; }
	float GetZ() { return z; }
	float GetPitch() { return pitch; }
	float GetYaw() { return yaw; }
	float GetRoll() { return roll; }
	float GetCPitch() { return cpitch; }
	float GetCYaw() { return cyaw; }
	float GetCRoll() { return croll; }
	float GetVX() { return vx; }
	float GetVY() { return vy; }
	float GetVZ() { return vz; }
	float GetShipSpeed() { return ship_speed; }
	SESSION_STATE GetSessionState() { return sessionState; }

	void SetSocket(SOCKET s) { socket = s; }
	void SetUseCheck(bool value) { use_check = value; }
	void SetSessionID(int _sessionID);
	void SetPrevRemainData(int amount);
	void SetID(char* _id) { strcpy_s(ID, _id); }
	void SetName(char* _name) { strcpy_s(name, _name); }
	void SetCharacterType(CHARACTER_TYPE type) { characterType = type; }
	void SetMap(MAP_TYPE _map) { map = _map; }
	void SetWeaponType(WEAPON_TYPE type) { weapon_type = type; }
	void SetPosition(float _x, float _y, float _z) { x = _x; y = _y; z = _z; }
	void SetX(float _x) { x = _x; }
	void SetY(float _y) { y = _y; }
	void SetZ(float _z) { z = _z; }
	void SetRotation(float _pitch, float _yaw, float _roll) { pitch = _pitch; yaw = _yaw; roll = _roll; }
	void SetPitch(float _pitch) { pitch = _pitch; }
	void SetYaw(float _yaw) { yaw = _yaw; }
	void SetRoll(float _roll) { roll = _roll; }
	void SetCRotation(float _cpitch, float _cyaw, float _croll) { cpitch = _cpitch; cyaw = _cyaw; croll = _croll; }
	void SetCPitch(float _cpitch) { cpitch = _cpitch; }
	void SetCYaw(float _cyaw) { cyaw = _cyaw; }
	void SetCRoll(float _croll) { croll = _croll; }
	void SetVelocity(float _vx, float _vy, float _vz) { vx = _vx; vy = _vy; vz = _vz; }
	void SetVX(float _vx) { vx = _vx; }
	void SetVY(float _vy) { vy = _vy; }
	void SetVZ(float _vz) { vz = _vz; }
	void SetShipSpeed(float _ship_speed) { ship_speed = _ship_speed; }
	void SetSessionState(SESSION_STATE st) { sessionState = st; }

	void SetAcceptInit(OVER_TYPE over_type, SOCKET s, bool value, int _sessionID, int amount);

	void InitLogin(SC_LOGIN_INFO_PACKET& info_packet, CS_LOGIN_PACKET* login_packet);

	void recving();
	void sending(void* packet);
	void SendToRemovePlayer(int target_id);
	void SendToLoginInfo(SC_LOGIN_INFO_PACKET& info_packet, int sessionID);
	void SendToAddPlayer(SESSION& target);
	void SendToAddMonster(MONSETR& target);
	void SendToMovePlayer(SESSION& target);
	void SendToChangeCharacter(SESSION& target);
	void SendToChangeWeapon(SESSION& target);
	void SendToAttackSkill(CS_ATTACK_SKILL_PACKET* packet);
	void SendToSpawnShip(CS_SPAWN_SPACESHIP_PACKET* packet);
	void SendToRemoveMonster(int target_id);
	void SendToGetItem();
	void SendToBuySell();
	void SendToItemBuy(CS_ITEM_BUY_PACKET* packet);
	void SendToMoveMonster(MONSETR& target);
	void SendToAttackMonster(MONSETR& monster, SESSION& target, MONSTER_ATTACK_TYPE _type);
};

