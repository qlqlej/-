#pragma once
#include "protocol.h"
#include "stdafx.h"

class MONSETR {
private:
	MONSTER_TYPE		type;
	MAP_TYPE			mapType;
	int					sessionID;
	float				init_hp;
	float				init_x, init_y, init_z;
	float				hp;
	float				x, y, z;
	float				pitch, yaw, roll;
	float				vx, vy, vz;
	float				ex;

public:
	MONSETR() : sessionID(-1), hp(100){}
	~MONSETR() {}
	
	// юс╫ц
	lua_State*			L;
	mutex				vm_l;
	int					targetID = -1;
	int					bossID = -1;
	int					mob_num = 0;
	bool				bdamaged = false;	
	mutex				hp_l;
	mutex				ex_l;
	system_clock::time_point act_time;
	system_clock::time_point respawn_time;
	bool death = false;	

	MONSTER_TYPE GetMonsterType() { return type; }
	MAP_TYPE GetMapType() { return mapType; }
	int GetSessionID() { return sessionID; }
	float GetHP() { return hp; }
	float GetInitHP() { return init_hp; }
	float GetX() { return x; }
	float GetY() { return y; }
	float GetZ() { return z; }
	float GetInitX() { return init_x; }
	float GetInitY() { return init_y; }
	float GetInitZ() { return init_z; }
	float GetPitch() { return pitch; }
	float GetYaw() { return yaw; }
	float GetRoll() { return roll; }
	float GetVX() { return vx; }
	float GetVY() { return vy; }
	float GetVZ() { return vz; }
	float GetEX() { return ex; }

	void SetMonseterType(MONSTER_TYPE _type) { type = _type; }
	void SetMapType(MAP_TYPE _type) { mapType = _type; }
	void SetSessionID(int id) { sessionID = id; }
	void SetHP(float _hp) { hp = _hp; }
	void SetInitHP(float _hp) { init_hp = _hp; }
	void SetPosition(float _x, float _y, float _z) { x = _x; y = _y; z = _z; }
	void SetInitPosition(float _x, float _y, float _z) { init_x = _x; init_y = _y; init_z = _z; }
	void SetX(float _x) { x = _x; }
	void SetY(float _y) { y = _y; }
	void SetZ(float _z) { z = _z; }
	void SetRotation(float _pitch, float _yaw, float _roll) { pitch = _pitch; yaw = _yaw; roll = _roll; }
	void SetPitch(float _pitch) { pitch = _pitch; }
	void SetYaw(float _yaw) { yaw = _yaw; }
	void SetRoll(float _roll) { roll = _roll; }
	void SetVelocity(float _vx, float _vy, float _vz) { vx = _vx; vy = _vy; vz = _vz; }
	void SetVX(float _vx) { vx = _vx; }
	void SetVY(float _vy) { vy = _vy; }
	void SetVZ(float _vz) { vz = _vz; }
	void SetEX(float _ex) { ex = _ex; }
};

