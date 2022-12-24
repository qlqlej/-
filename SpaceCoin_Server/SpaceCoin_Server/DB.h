#pragma once
#include <windows.h>  
#include <stdio.h> 
#include <sqlext.h>
#include <string>
#include <iostream>
#include "protocol.h"

using namespace std;

//#define UNICODE

class DB {
private:
	SQLHENV			henv;
	SQLHDBC			hdbc;
	SQLHSTMT		hstmt;
	SQLRETURN		retcode;

public:
	DB();
	~DB();

	void HandleDiagnosticRecord(SQLHANDLE hHandle, SQLSMALLINT hType, RETCODE RetCode);
	void Initialize();
	bool ExistAccount(const char* id);
	bool SearchAccount(const char* id, const char* pw, SC_LOGIN_INFO_PACKET& p, QUEST_DATA& q);
	bool SignupAccount(const char* nickname, const char* id, const char* pw);
	bool SavePlayerInfo(const char* id, float hp, int a_coin, int b_coin, int c_coin, int gold, float x, float y, float z,
		float pitch, float yaw, float roll, int character_type, int map_type, int critical_up, int speed_up, int attack_up, int hp_up, int recover_hp_up,
		int sniper_up, int attack_hp_up, int launcher_up, int launcher_range_up, int jump_up,
		int missile_up, int slash_up, int slash_size_up, int ultimate_up,
		int quest_level, int goal_rate, int now_rate, int qa_coin, int qb_coin, int qc_coin,
		float a_cost, float b_cost, float c_cost);
};