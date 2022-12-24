#pragma once
#include <vector>
#include <string>
using namespace std;

constexpr int PORT_NUM = 4000;
constexpr int BUF_SIZE = 256;
constexpr int RBUF_SIZE = 1024;
constexpr int MAX_ID_LEN = 20;
constexpr int MAX_PW_LEN = 20;
constexpr int MAX_NAME_LEN = 20;
constexpr int MAX_USER = 1000;
constexpr int MAX_MONSTER = 189;
constexpr int THREADS_NUM = 8;

// Packet ID
constexpr char CS_LOGIN					= 0;
constexpr char CS_MOVE					= 1;
constexpr char CS_SIGNUP				= 2;
constexpr char CS_CHARACTER_CHANGE		= 3;
constexpr char CS_WEAPON_CHANGE			= 4;
constexpr char CS_ATTACK_SKILL			= 5;
constexpr char CS_CHANGE_MAP			= 6;
constexpr char CS_SPAWN_SPACESHIP		= 7;
constexpr char CS_DAMAGE_MONSTER		= 8;
constexpr char CS_GET_ITEM				= 9;
constexpr char CS_BUY_SELL				= 10;
constexpr char CS_ITEM_BUY				= 11;
constexpr char CS_COIN_PRICE			= 12;
constexpr char CS_TEST_LOGIN			= 13;
constexpr char CS_TEST_MOVE				= 14;

constexpr char SC_LOGIN_INFO			= 50;
constexpr char SC_ADD_PLAYER			= 51;
constexpr char SC_REMOVE_PLAYER			= 52;
constexpr char SC_MOVE_PLAYER			= 53;
constexpr char SC_MONSTER_INFO			= 54;
constexpr char SC_MOVE_MONSTER			= 55;
constexpr char SC_CHANGE_MAP			= 56;
constexpr char SC_CHARACTER_CHANGE		= 57;
constexpr char SC_WEAPON_CHANGE			= 58;
constexpr char SC_ATTACK_SKILL			= 59;
constexpr char SC_SPAWN_SPACESHIP		= 60;
constexpr char SC_REMOVE_MONSTER		= 61;
constexpr char SC_DAMAGE_MONSTER		= 62;
constexpr char SC_ATTACK_MONSTER		= 63;
constexpr char SC_GET_ITEM				= 64;
constexpr char SC_ITEM_BUY				= 65;
constexpr char SC_BUY_SELL				= 66;
constexpr char SC_COIN_PRICE			= 67;
constexpr char SC_MONSTER_ATTACK		= 68;
constexpr char SC_QUEST					= 69;

constexpr char ALL_STATE				= 100;

enum class OVER_TYPE { ACCEPT, RECV, SEND, 
	MONSTER_MOVE, MONSTER_ATTACK, MONSTER_RESPAWN};
enum class SESSION_STATE {FREE, WAIT, ACTIVE};
enum class PACKET_STATE {SUCCESS, SIGNUPFAIL, LOGINFAIL};
enum class MONSTER_TYPE { F_ICE, S_ICE, T_ICE, F_SAND, S_SAND, T_SAND, F_WATER, S_WATER, T_WATER, F_FISH, S_FISH, T_FISH };
enum class MAP_TYPE { SPACE, ICE, SAND, WATER, NOT_MAP };
enum class ATTACK_SKILL_TYPE { NORMAL, SNIPING, LAUNCHER, DASHING, MISSILE, ULTIMATE, DEFENSE, SLASH, JUMP };
enum class WEAPON_TYPE { SWORD, GUN };
enum class CHARACTER_TYPE { HUMAN, SPACESHIP };
enum class DROP_ITEM { A_COIN, B_COIN, C_COIN };
enum class MONSTER_ATTACK_TYPE { NORMAL, SKILL };
enum class BUY_SELL { BUY, SELL };
enum class ITEM_TYPE { CRITICAL_UP, SPEED_UP, ATTACK_UP, HP_UP, RECOVER_UP,
SNIPER_UP, ATTACK_HP_UP, LAUNCHER_UP, LAUNCHER_RANGE_UP, JUMP_UP,
MISSILE_UP, SLASH_UP, SLASH_SIZE_UP, ULTIMATE_UP};
enum class MONSTER_ACTION {MOVE, INITMOVE};

#pragma pack(push, 1)
struct ALL_STATE_PACKET {
	unsigned char			size;
	char					type;
	PACKET_STATE			state;
};

struct COIN_DATA {
	char			coin_name[BUF_SIZE];  // 이름
	char			opening_price[BUF_SIZE];  // 시가 00시 기준
	char			closing_price[BUF_SIZE];  // 종가 00시 기준
	char			min_price[BUF_SIZE];  // 저가 00시 기준
	char			max_price[BUF_SIZE];  // 고가 00시 기준z
	char			units_traded[BUF_SIZE];  // 거래량 00시 기준
	char			prev_closing_price[BUF_SIZE];  // 거래금액 00시 기준
	char			acc_trade_value[BUF_SIZE];  // 전일종가
	char			units_traded_24H[BUF_SIZE];  // 최근 24시간 거래량 
	char			acc_trade_value_24H[BUF_SIZE];  // 최근 24시간 거래금액
	char			fluctate_24H[BUF_SIZE];  // 최근 24시간 변동가
	char			fluctate_rate_24H[BUF_SIZE];  // 최근 24시간 변동률

};

struct QUEST_DATA {
	int				quest_level;
	int				goal_rate, now_rate;
	int				a_coin, b_coin, c_coin;
	float			a_purchase_cost, b_purchase_cost, c_purchase_cost;
};

// CS
struct CS_LOGIN_PACKET {
	unsigned char			size;
	char					type;
	char					id[MAX_ID_LEN];
	char					pw[MAX_PW_LEN];
};

struct CS_MOVE_PACKET {
	unsigned char			size;
	char					type;
	CHARACTER_TYPE			character_type;
	short					sessionID;
	float					hp;
	float					x, y, z;
	float					pitch, yaw, roll;
	float					cpitch, cyaw, croll;
	float					vx, vy, vz;
	float					ship_speed;
};

struct CS_SIGNUP_PACKET {
	unsigned char			size;
	char					type;
	char					name[MAX_NAME_LEN];
	char					id[MAX_ID_LEN];
	char					pw[MAX_PW_LEN];
};

struct CS_CHANGE_CHARACTER_PACKET {
	unsigned char			size;
	char					type;
	short					sessionID;
	WEAPON_TYPE				weapon_type;
	CHARACTER_TYPE			character_type;
};

struct CS_ATTACK_SKILL_PACKET {
	unsigned char			size;
	char					type;
	short					sessionID;
	float					cpitch, cyaw, croll;
	ATTACK_SKILL_TYPE		attack_skill_type;
	float					jump_velocity;
	float					slash_size;
	float					launcher_particle_radius;
};

struct CS_CHANGE_MAP_PACKET {
	unsigned char			size;
	char					type;
	short					sessionID;
	MAP_TYPE				map_type;
	unsigned int			client_time;
};

struct CS_SPAWN_SPACESHIP_PACKET {
	unsigned char			size;
	char					type;
	short					owner_sessionID;
	float					x, y, z;
	float					pitch, yaw, roll;
};

struct CS_DAMAGE_MONSTER_PACKET {
	unsigned char			size;
	char					type;
	short					sessionID;
	short					attack_sessionID;
	float					damage;
	MONSTER_TYPE			monsterType;
};

struct CS_GET_ITEM_PACKET {
	unsigned char			size;
	char					type;
	short					sessionID;
	DROP_ITEM				item;
};

struct CS_BUY_SELL_PACKET {
	unsigned char			size;
	char					type;
	short					sessionID;
	BUY_SELL				buy_sell_type;
	DROP_ITEM				coin_type;
	int						count, price;	
};

struct CS_ITEM_BUY_PACKET {
	unsigned char			size;
	char					type;
	short					sessionID;
	ITEM_TYPE				item_type;
	int						price;
	int						gold;
};

struct CS_COIN_PRICE_PACKET {
	unsigned char			size;
	char					type;
	short					sessionID;
};

// SC
struct SC_LOGIN_INFO_PACKET {
	unsigned char			size;
	char					type;
	short					sessionID;
	CHARACTER_TYPE			character_type;
	MAP_TYPE				map_type;
	char					name[MAX_NAME_LEN];
	float					hp;
	int						a_coin, b_coin, c_coin, gold;
	float					x, y, z;
	float					pitch, yaw, roll;
	int						critical_up, speed_up, attack_up, hp_up, recover_hp_up;
	int						sniper_up, attack_hp_up, launcher_up, launcher_range_up, jump_up;
	int						missile_up, slash_up, slash_size_up, ultimate_up;
};

struct SC_ADD_PLAYER_PACKET {
	unsigned char			size;
	char					type;
	short					sessionID;
	float					hp;
	CHARACTER_TYPE			character_type;
	WEAPON_TYPE				weapon_type;
	char					name[MAX_NAME_LEN];
	float					x, y, z;
	float					pitch, yaw, roll;
	float					cpitch, cyaw, croll;
	float					ship_speed;
};

struct SC_REMOVE_PLAYER_PACKET {
	unsigned char			size;
	char					type;
	short					sessionID;
};

struct SC_MOVE_PLAYER_PACKET {
	unsigned char			size;
	char					type;
	CHARACTER_TYPE			character_type;
	short					sessionID;
	float					hp;
	float					x, y, z;
	float					pitch, yaw, roll;
	float					cpitch, cyaw, croll;
	float					vx, vy, vz;
	float					ship_speed;
	WEAPON_TYPE				weapon_type;
	unsigned				client_time;
	char					name[MAX_NAME_LEN];
};

struct SC_MONSTER_INFO_PACKET {
	unsigned char			size;
	char					type;
	short					sessionID;
	MONSTER_TYPE			monsterType;
	float					hp;
	float					x, y, z;
	float					pitch, yaw, roll;
};

struct SC_MOVE_MONSTER_PACKET {
	unsigned char			size;
	char					type;
	short					sessionID;
	MONSTER_TYPE			monsterType;
	float					hp;
	float					x, y, z;
	float					pitch, yaw, roll;	
};

struct SC_CHANGE_MAP_PACKET {
	unsigned char			size;
	char					type;
	float					x, y, z;
	unsigned int			client_time;
};

struct SC_CHANGE_CHARACTER_PACKET {
	unsigned char			size;
	char					type;
	short					sessionID;
	WEAPON_TYPE				weapon_type;
	CHARACTER_TYPE			character_type;
	float					x, y, z;
	float					pitch, yaw, roll;
	char					name[MAX_NAME_LEN];
};

struct SC_ATTACK_SKILL_PACKET {
	unsigned char			size;
	char					type;
	short					sessionID;
	float					cpitch, cyaw, croll;
	ATTACK_SKILL_TYPE		attack_skill_type;
	float					x, y, z;
	float					pitch, yaw, roll;
	float					jump_velocity;
	float					slash_size;
	float					launcher_particle_radius;
	WEAPON_TYPE				weapon_type;
	char					name[MAX_NAME_LEN];
};

struct SC_SPAWN_SPACESHIP_PACKET {
	unsigned char			size;
	char					type;
	short					owner_sessionID;
	float					x, y, z;
	float					pitch, yaw, roll;
	float					player_x, player_y, player_z;
	float					player_pitch, player_yaw, player_roll;
	WEAPON_TYPE				weapon_type;
	char					name[MAX_NAME_LEN];
};

struct SC_REMOVE_MONSTER_PACKET {
	unsigned char			size;
	char					type;
	short					sessionID;
};

struct SC_DAMAGE_MONSTER_PACKET {
	unsigned char			size;
	char					type;
	short					sessionID;
	short					attack_sessionID;
	DROP_ITEM				item;
	float					hp;
	MONSTER_TYPE			monsterType;
	float					x, y, z;
	float					pitch, yaw, roll;
};

struct SC_ATTACK_MONSTER_PACKET {
	unsigned char			size;
	char					type;
	short					sessionID;
	short					targetID;
	float					x, y, z;
	float					hp;
	MONSTER_ATTACK_TYPE		attack_type;
	MONSTER_TYPE			monsterType;
};

struct SC_GET_ITEM_PACKET {
	unsigned char			size;
	char					type;
	short					sessionID;
	int						a_coin, b_coin, c_coin;
};

struct SC_ITEM_BUY_PACKET {
	unsigned char			size;
	char					type;
	short					sessionID;
	ITEM_TYPE				item_type;
	int						gold;
};

struct SC_BUY_SELL_PACKET {
	unsigned char			size;
	char					type;
	short					sessionID;
	int						a_coin, b_coin, c_coin;
	int						gold;
};

struct SC_COIN_PRICE_PACKET {
	unsigned char         size;
	char               type;
	char               coin_data[BUF_SIZE * 2];
};

struct SC_MONSTER_ATTACK_PACKET {
	unsigned char			size;
	char					type;
	float					damage;
};

struct SC_QUEST_PACKET {
	unsigned char			size;
	char					type;
	int						quest_level;				// 퀘스트 단계
	int						goal_rate, now_rate;		// 목표수치, 현재수치
	int						a_coin, b_coin, c_coin;		// 특정 퀘스트에 쓰일 코인 갯수 변수
	float					a_purchase_cost, b_purchase_cost, c_purchase_cost;		// 특정 퀘스트에 쓰일 코인 매수 평균비용
};

// Test Packet
struct CS_TEST_LOGIN_PACKET {
	unsigned char size;
	char	type;
	char	name[MAX_NAME_LEN];
};

struct CS_TEST_MOVE_PACKET {
	unsigned char size;
	char	type;
	short					sessionID;
	char	direction;  // 0 : UP, 1 : DOWN, 2 : LEFT, 3 : RIGHT
	unsigned  client_time;
};
#pragma pack (pop)