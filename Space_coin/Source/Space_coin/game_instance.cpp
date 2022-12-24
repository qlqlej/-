#include "game_instance.h"
#include "MyCharacter.h"
#include "MainGamePlayerController.h"

Ugame_instance::Ugame_instance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> MonsterInfoAsset(TEXT("DataTable'/Game/SpaceCoinContent/Monster/datatable/MonsterDataTable.MonsterDataTable'"));
	if (MonsterInfoAsset.Succeeded()) {
		monster_info_table = MonsterInfoAsset.Object;
	}
}

Ugame_instance::~Ugame_instance()
{

}

void Ugame_instance::Init()
{
	Super::Init();

	client = Client::GetClient();
	client->Initialize();	
}

void Ugame_instance::Shutdown()
{
	Super::Shutdown();

	client->StopRecvThread();
}

const FMonsterInfo* Ugame_instance::FindMonsterInfo(const FName& key) const
{
	if (!IsValid(monster_info_table)) {
		return nullptr;
	}

	return monster_info_table->FindRow<FMonsterInfo>(key, TEXT(""));
}

void Ugame_instance::SetLoginInfoData(SC_LOGIN_INFO_PACKET* packet)
{
	sc_login_info_packet.sessionID = packet->sessionID;
	sc_login_info_packet.character_type = packet->character_type;
	sc_login_info_packet.map_type = packet->map_type;
	strcpy_s(sc_login_info_packet.name, packet->name);
	sc_login_info_packet.x = packet->x;
	sc_login_info_packet.y = packet->y;
	sc_login_info_packet.z = packet->z;
	sc_login_info_packet.pitch = packet->pitch;
	sc_login_info_packet.yaw = packet->yaw;
	sc_login_info_packet.roll = packet->roll;
	bLoginInfo = true;
	bLogin = true;
}

void Ugame_instance::SendToChangeCharacterState(CS_CHANGE_CHARACTER_PACKET packet)
{
	client->SendToChangeCharacterState(packet);
}

void Ugame_instance::SendToAttackSkill(CS_ATTACK_SKILL_PACKET packet)
{
	client->SendToAttackSkill(packet);
}

short Ugame_instance::GetPlayerSessionID()
{
	return player_sessionID;
}

FString Ugame_instance::GetPlayerName()
{
	return player_name;
}