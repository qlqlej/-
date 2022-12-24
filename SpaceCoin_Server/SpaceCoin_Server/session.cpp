#include "session.h"

void SESSION::SetSessionID(int _sesssionID)
{
	if (_sesssionID < 0 && _sesssionID != -1) { cout << "Wrong ID value!\n"; }
	else sessionID = _sesssionID;
}

void SESSION::SetPrevRemainData(int amount)
{
	if (amount < 0) { cout << "Wrong prev_remain_data value!\n"; }
	else prev_remain_data = amount;
}

void SESSION::SetAcceptInit(OVER_TYPE over_type, SOCKET s, bool value, int _sessionID, int amount)
{
	ext_over.SetOverType(over_type);
	SetSocket(s);
	SetUseCheck(value);
	SetSessionID(_sessionID);
	SetPrevRemainData(amount);
}

void SESSION::InitLogin(SC_LOGIN_INFO_PACKET& info_packet, QUEST_DATA& quest_data, CS_LOGIN_PACKET* login_packet)
{
	hp = info_packet.hp;
	a_coin = info_packet.a_coin;
	b_coin = info_packet.b_coin;
	c_coin = info_packet.c_coin;
	gold = info_packet.gold;
	critical_up = info_packet.critical_up;
	speed_up = info_packet.speed_up;
	attack_up = info_packet.attack_up;
	hp_up = info_packet.hp_up;
	recover_hp_up = info_packet.recover_hp_up;
	sniper_up = info_packet.sniper_up;
	attack_hp_up = info_packet.attack_hp_up;
	launcher_up = info_packet.launcher_up;
	launcher_range_up = info_packet.launcher_range_up;
	jump_up = info_packet.jump_up;
	missile_up = info_packet.missile_up;
	slash_up = info_packet.slash_up;
	slash_size_up = info_packet.slash_size_up;
	ultimate_up = info_packet.ultimate_up;

	client_quest_data = quest_data;
	bTest = false;
	SetID(login_packet->id);
	SetName(info_packet.name);
	SetCharacterType(info_packet.character_type);
	SetPosition(info_packet.x, info_packet.y, info_packet.z);
	SetRotation(info_packet.pitch, info_packet.yaw, info_packet.roll);
	SetWeaponType(WEAPON_TYPE::SWORD);
}

void SESSION::InitTestLogin(SC_LOGIN_INFO_PACKET& info_packet, QUEST_DATA& quest_data, CS_TEST_LOGIN_PACKET* login_packet)
{
	hp = info_packet.hp;
	a_coin = info_packet.a_coin;
	b_coin = info_packet.b_coin;
	c_coin = info_packet.c_coin;
	gold = info_packet.gold;
	critical_up = info_packet.critical_up;
	speed_up = info_packet.speed_up;
	attack_up = info_packet.attack_up;
	hp_up = info_packet.hp_up;
	recover_hp_up = info_packet.recover_hp_up;
	sniper_up = info_packet.sniper_up;
	attack_hp_up = info_packet.attack_hp_up;
	launcher_up = info_packet.launcher_up;
	launcher_range_up = info_packet.launcher_range_up;
	jump_up = info_packet.jump_up;
	missile_up = info_packet.missile_up;
	slash_up = info_packet.slash_up;
	slash_size_up = info_packet.slash_size_up;
	ultimate_up = info_packet.ultimate_up;

	client_quest_data = quest_data;
	bTest = true;
	SetID(login_packet->name);
	SetName(info_packet.name);
	SetCharacterType(info_packet.character_type);
	SetPosition(info_packet.x, info_packet.y, info_packet.z);
	SetRotation(info_packet.pitch, info_packet.yaw, info_packet.roll);
	SetWeaponType(WEAPON_TYPE::SWORD);
}

void SESSION::recving()
{
	DWORD recv_flag = 0;
	memset(&ext_over.GetWSAOverlapped(), 0, sizeof(ext_over.GetWSAOverlapped()));
	ext_over.SetWSABuf_length(BUF_SIZE - prev_remain_data);
	ext_over.SetWSABuf_buf(ext_over.GetSendBuf() + prev_remain_data);
	WSARecv(socket, &ext_over.GetWSABuf(), 1, 0, &recv_flag, &ext_over.GetWSAOverlapped(), 0);
}

void SESSION::sending(void* packet)
{
	EXT_OVER* send_data = new EXT_OVER{ reinterpret_cast<unsigned char*>(packet) };
	WSASend(socket, &send_data->GetWSABuf(), 1, 0, 0, &send_data->GetWSAOverlapped(), 0);
}

void SESSION::SendToRemovePlayer(int target_id)
{
	SC_REMOVE_PLAYER_PACKET packet;
	packet.sessionID = target_id;
	packet.size = sizeof(SC_REMOVE_PLAYER_PACKET);
	packet.type = SC_REMOVE_PLAYER;
	this_thread::sleep_for(milliseconds(DELAY_TIME));
	if (SESSION_STATE::ACTIVE == GetSessionState())		
		sending(&packet);
}

void SESSION::SendToLoginInfo(SC_LOGIN_INFO_PACKET& info_packet, int sessionID)
{
	info_packet.sessionID = sessionID;
	info_packet.size = sizeof(SC_LOGIN_INFO_PACKET);
	info_packet.type = SC_LOGIN_INFO;
	sending(&info_packet);
}

void SESSION::SendToQuestData()
{
	//cout << "quest info\n";
	SC_QUEST_PACKET quest_packet;
	quest_packet.size = sizeof(SC_QUEST_PACKET);
	quest_packet.type = SC_QUEST;
	quest_packet.quest_level = client_quest_data.quest_level;
	quest_packet.goal_rate = client_quest_data.goal_rate;
	quest_packet.now_rate = client_quest_data.now_rate;
	quest_packet.a_coin = client_quest_data.a_coin;
	quest_packet.b_coin = client_quest_data.b_coin;
	quest_packet.c_coin = client_quest_data.c_coin;
	quest_packet.a_purchase_cost = client_quest_data.a_purchase_cost;
	quest_packet.b_purchase_cost = client_quest_data.b_purchase_cost;
	quest_packet.c_purchase_cost = client_quest_data.c_purchase_cost;
	this_thread::sleep_for(milliseconds(DELAY_TIME));
	sending(&quest_packet);
}

void SESSION::SendToAddPlayer(SESSION& target)
{
	SC_ADD_PLAYER_PACKET new_player_packet;
	new_player_packet.size = sizeof(SC_ADD_PLAYER_PACKET);
	new_player_packet.type = SC_ADD_PLAYER;
	new_player_packet.sessionID = target.GetSessionID();
	new_player_packet.character_type = target.GetCharacterType();
	new_player_packet.weapon_type = target.GetWeaponType();
	strcpy_s(new_player_packet.name, target.GetName());
	new_player_packet.x = target.GetX();
	new_player_packet.y = target.GetY();
	new_player_packet.z = target.GetZ();
	new_player_packet.pitch = target.GetPitch();
	new_player_packet.yaw = target.GetYaw();
	new_player_packet.roll = target.GetRoll();
	new_player_packet.cpitch = target.GetCPitch();
	new_player_packet.cyaw = target.GetCYaw();
	new_player_packet.croll = target.GetCRoll();
	new_player_packet.ship_speed = target.GetShipSpeed();
	this_thread::sleep_for(milliseconds(DELAY_TIME));
	if(SESSION_STATE::ACTIVE == GetSessionState())
		if(GetMap() == target.GetMap())
			sending(&new_player_packet);
}

void SESSION::SendToAddMonster(MONSETR& target)
{
	SC_MONSTER_INFO_PACKET monster_info;
	monster_info.size = sizeof(SC_MONSTER_INFO_PACKET);
	monster_info.type = SC_MONSTER_INFO;
	//target.hp_l.lock();
	monster_info.hp = target.GetHP();
	monster_info.monsterType = target.GetMonsterType();
	monster_info.sessionID = target.GetSessionID();
	monster_info.x = target.GetX();
	monster_info.y = target.GetY();
	monster_info.z = target.GetZ();
	monster_info.pitch = target.GetPitch();
	monster_info.yaw = target.GetYaw();
	monster_info.roll = target.GetRoll();
	if (0 < monster_info.hp) {
		this_thread::sleep_for(milliseconds(DELAY_TIME));
		if (SESSION_STATE::ACTIVE == GetSessionState())
			sending(&monster_info);		
	}
	//target.hp_l.unlock();
}

void SESSION::SendToMovePlayer(SESSION& target)
{
	SC_MOVE_PLAYER_PACKET info_packet;
	info_packet.size = sizeof(SC_MOVE_PLAYER_PACKET);
	info_packet.type = SC_MOVE_PLAYER;
	info_packet.character_type = target.GetCharacterType();
	info_packet.sessionID = target.GetSessionID();
	info_packet.hp = target.hp;
	info_packet.x = target.GetX();
	info_packet.y = target.GetY();
	info_packet.z = target.GetZ();
	info_packet.pitch = target.GetPitch();
	info_packet.yaw = target.GetYaw();
	info_packet.roll = target.GetRoll();
	info_packet.cpitch = target.GetCPitch();
	info_packet.cyaw = target.GetCYaw();
	info_packet.croll = target.GetCRoll();
	info_packet.vx = target.GetVX();
	info_packet.vy = target.GetVY();
	info_packet.vz = target.GetVZ();
	info_packet.ship_speed = target.GetShipSpeed();
	info_packet.weapon_type = target.GetWeaponType();
	strcpy_s(info_packet.name, target.GetName());
	info_packet.client_time = 0;
	//this_thread::sleep_for(milliseconds(16));
	if (SESSION_STATE::ACTIVE == GetSessionState())
		if (GetMap() == target.GetMap())
			sending(&info_packet);
}

void SESSION::SendToTestMovePlayer(SESSION& target, unsigned client_time)
{
	SC_MOVE_PLAYER_PACKET info_packet;
	info_packet.size = sizeof(SC_MOVE_PLAYER_PACKET);
	info_packet.type = SC_MOVE_PLAYER;
	info_packet.character_type = target.GetCharacterType();
	info_packet.sessionID = target.GetSessionID();
	info_packet.hp = target.hp;
	info_packet.x = target.GetX();
	info_packet.y = target.GetY();
	info_packet.z = target.GetZ();
	info_packet.pitch = target.GetPitch();
	info_packet.yaw = target.GetYaw();
	info_packet.roll = target.GetRoll();
	info_packet.cpitch = target.GetCPitch();
	info_packet.cyaw = target.GetCYaw();
	info_packet.croll = target.GetCRoll();
	info_packet.vx = target.GetVX();
	info_packet.vy = target.GetVY();
	info_packet.vz = target.GetVZ();
	info_packet.ship_speed = target.GetShipSpeed();
	info_packet.weapon_type = target.GetWeaponType();
	strcpy_s(info_packet.name, target.GetName());
	info_packet.client_time = client_time;
	//this_thread::sleep_for(milliseconds(16));
	if (SESSION_STATE::ACTIVE == GetSessionState())
		if (GetMap() == target.GetMap())
			sending(&info_packet);
}

void SESSION::SendToChangeCharacter(SESSION& target)
{
	SC_CHANGE_CHARACTER_PACKET info_packet;
	info_packet.size = sizeof(SC_CHANGE_CHARACTER_PACKET);
	info_packet.type = SC_CHARACTER_CHANGE;
	info_packet.sessionID = target.GetSessionID();
	info_packet.character_type = target.GetCharacterType();
	info_packet.weapon_type = target.GetWeaponType();
	info_packet.x = target.GetX();
	info_packet.y = target.GetY();
	info_packet.z = target.GetZ();
	info_packet.pitch = target.GetPitch();
	info_packet.yaw = target.GetYaw();
	info_packet.roll = target.GetRoll();
	strcpy_s(info_packet.name, target.GetName());
	//this_thread::sleep_for(milliseconds(16));
	if (SESSION_STATE::ACTIVE == GetSessionState())
		if (GetMap() == target.GetMap())
			sending(&info_packet);
}

void SESSION::SendToChangeWeapon(SESSION& target)
{
	SC_CHANGE_CHARACTER_PACKET info_packet;
	info_packet.size = sizeof(SC_CHANGE_CHARACTER_PACKET);
	info_packet.type = SC_WEAPON_CHANGE;
	info_packet.sessionID = target.GetSessionID();
	info_packet.weapon_type = target.GetWeaponType();
	strcpy_s(info_packet.name, target.GetName());
	this_thread::sleep_for(milliseconds(DELAY_TIME));
	if (SESSION_STATE::ACTIVE == GetSessionState())
		if (GetMap() == target.GetMap())
			sending(&info_packet);
}

void SESSION::SendToAttackSkill(CS_ATTACK_SKILL_PACKET* packet, SESSION& target)
{
	SC_ATTACK_SKILL_PACKET info_packet;
	info_packet.size = sizeof(SC_ATTACK_SKILL_PACKET);
	info_packet.type = SC_ATTACK_SKILL;
	info_packet.sessionID = packet->sessionID;
	info_packet.attack_skill_type = packet->attack_skill_type;
	info_packet.cpitch = packet->cpitch;
	info_packet.cyaw = packet->cyaw;
	info_packet.croll = packet->croll;	
	info_packet.x = target.GetX();
	info_packet.y = target.GetY();
	info_packet.z = target.GetZ();
	info_packet.pitch = target.GetPitch();
	info_packet.yaw = target.GetYaw();
	info_packet.roll = target.GetRoll();
	info_packet.jump_velocity = packet->jump_velocity;
	info_packet.slash_size = packet->slash_size;
	info_packet.launcher_particle_radius = packet->launcher_particle_radius;
	info_packet.weapon_type = target.GetWeaponType();
	strcpy_s(info_packet.name, target.GetName());
	this_thread::sleep_for(milliseconds(DELAY_TIME));
	if (SESSION_STATE::ACTIVE == GetSessionState())
		if (GetMap() == target.GetMap())
			sending(&info_packet);
}

void SESSION::SendToSpawnShip(CS_SPAWN_SPACESHIP_PACKET* packet, SESSION& target)
{
	SC_SPAWN_SPACESHIP_PACKET info_packet;
	info_packet.size = sizeof(SC_SPAWN_SPACESHIP_PACKET);
	info_packet.type = SC_SPAWN_SPACESHIP;
	info_packet.owner_sessionID = packet->owner_sessionID;
	info_packet.x = packet->x;
	info_packet.y = packet->y;
	info_packet.z = packet->z;
	info_packet.pitch = packet->pitch;
	info_packet.roll = packet->roll;
	info_packet.yaw = packet->yaw;
	info_packet.player_x = target.GetX();
	info_packet.player_y = target.GetY();
	info_packet.player_z = target.GetZ();
	info_packet.player_pitch = target.GetPitch();
	info_packet.player_yaw = target.GetYaw();
	info_packet.player_roll = target.GetRoll();
	info_packet.weapon_type = target.GetWeaponType();
	strcpy_s(info_packet.name, target.GetName());
	//this_thread::sleep_for(milliseconds(16));
	if (SESSION_STATE::ACTIVE == GetSessionState())
		if (GetMap() == target.GetMap())
			sending(&info_packet);
}

void SESSION::SendToRemoveMonster(int target_id)
{
	SC_REMOVE_MONSTER_PACKET remove_packet;
	remove_packet.size = sizeof(SC_REMOVE_MONSTER_PACKET);
	remove_packet.type = SC_REMOVE_MONSTER;
	remove_packet.sessionID = target_id;
	this_thread::sleep_for(milliseconds(DELAY_TIME));
	sending(&remove_packet);
}

void SESSION::SendToGetItem()
{
	SC_GET_ITEM_PACKET get_item;
	get_item.size = sizeof(SC_GET_ITEM_PACKET);
	get_item.type = SC_GET_ITEM;
	get_item.sessionID = sessionID;
	get_item.a_coin = a_coin;
	get_item.b_coin = b_coin;
	get_item.c_coin = c_coin;
	sending(&get_item);
}

void SESSION::SendToBuySell()
{
	SC_BUY_SELL_PACKET buy_sell_packet;
	buy_sell_packet.size = sizeof(SC_BUY_SELL_PACKET);
	buy_sell_packet.type = SC_BUY_SELL;
	buy_sell_packet.sessionID = sessionID;
	buy_sell_packet.a_coin = a_coin;
	buy_sell_packet.b_coin = b_coin;
	buy_sell_packet.c_coin = c_coin;
	buy_sell_packet.gold = gold;
	sending(&buy_sell_packet);
}

void SESSION::SendToItemBuy(CS_ITEM_BUY_PACKET* packet)
{
	SC_ITEM_BUY_PACKET buy_item;
	buy_item.size = sizeof(SC_ITEM_BUY_PACKET);
	buy_item.type = SC_ITEM_BUY;
	buy_item.sessionID = packet->sessionID;
	buy_item.item_type = packet->item_type;
	buy_item.gold = gold;
	sending(&buy_item);
}

void SESSION::SendToMoveMonster(MONSETR& target)
{
	SC_MOVE_MONSTER_PACKET monster_move;
	monster_move.size = sizeof(SC_MOVE_MONSTER_PACKET);
	monster_move.type = SC_MOVE_MONSTER;
	monster_move.monsterType = target.GetMonsterType();
	monster_move.sessionID = target.GetSessionID();
	monster_move.x = target.GetX();
	monster_move.y = target.GetY();
	monster_move.z = target.GetZ();
	monster_move.pitch = target.GetPitch();
	monster_move.yaw = target.GetYaw();
	monster_move.roll = target.GetRoll();
	//target.hp_l.lock();
	monster_move.hp = target.GetHP();
	//target.hp_l.unlock();
	this_thread::sleep_for(milliseconds(DELAY_TIME));
	sending(&monster_move);
}

void SESSION::SendToAttackMonster(MONSETR& monster, SESSION& target, MONSTER_ATTACK_TYPE _type)
{
	SC_ATTACK_MONSTER_PACKET attack_packet;
	attack_packet.size = sizeof(SC_ATTACK_MONSTER_PACKET);
	attack_packet.type = SC_ATTACK_MONSTER;
	attack_packet.attack_type = _type;
	attack_packet.monsterType = monster.GetMonsterType();
	attack_packet.sessionID = monster.GetSessionID();
	attack_packet.targetID = target.GetSessionID();
	attack_packet.x = target.GetX();
	attack_packet.y = target.GetY();
	attack_packet.z = target.GetZ();
	attack_packet.hp = monster.GetHP();
	this_thread::sleep_for(milliseconds(DELAY_TIME));
	sending(&attack_packet);
}
