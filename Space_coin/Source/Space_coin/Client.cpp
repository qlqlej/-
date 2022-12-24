// Fill out your copyright notice in the Description page of Project Settings.


#include "Client.h"
#include "Components/SlateWrapperTypes.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

Client::Client() : SafeLoop(0)
{
}

Client::~Client()
{
	closesocket(client_socket);
	WSACleanup();
}

void Client::Error_display(FString msg)
{
}

bool Client::Init()
{
	return true;
}

uint32 Client::Run()
{
	// send()
	FPlatformProcess::Sleep(0.03);

	while (0 == SafeLoop.GetValue()) {
		char recv_buf[BUF_SIZE];
		ret = recv(client_socket, recv_buf, BUF_SIZE, 0);
		if (0 < ret) {
			switch (recv_buf[1]) {
			case SC_LOGIN_INFO:
			{
				SC_LOGIN_INFO_PACKET* p = reinterpret_cast<SC_LOGIN_INFO_PACKET*>(recv_buf);
				LoginPC->ChangeMap(p);
				while (MainPC == nullptr) {
					FPlatformProcess::Sleep(0.016);
				}
				if (MainPC != nullptr) {
					MainPC->SetLoginInfo(p);
				}
				break;
			}
			case SC_ADD_PLAYER:
			{
				SC_ADD_PLAYER_PACKET* p = reinterpret_cast<SC_ADD_PLAYER_PACKET*>(recv_buf);
				while (MainPC == nullptr) {
					FPlatformProcess::Sleep(0.016);
				}
				if (MainPC != nullptr) {
					MainPC->SetAddPlayer(p);
				}
				break;
			}
			case SC_MOVE_PLAYER:
			{
				SC_MOVE_PLAYER_PACKET* p = reinterpret_cast<SC_MOVE_PLAYER_PACKET*>(recv_buf);
				while (MainPC == nullptr) {
					FPlatformProcess::Sleep(0.016);
				}
				if (MainPC != nullptr) {
					MainPC->UpdatePlayerToMove(p);
				}
				break;
			}
			case SC_REMOVE_PLAYER:
			{
				SC_REMOVE_PLAYER_PACKET* p = reinterpret_cast<SC_REMOVE_PLAYER_PACKET*>(recv_buf);
				while (MainPC == nullptr) {
					FPlatformProcess::Sleep(0.016);
				}
				if (MainPC != nullptr) {
					MainPC->RemovePlayer(p);
				}
				break;
			}
			case SC_MONSTER_INFO:
			{
				SC_MONSTER_INFO_PACKET* p = reinterpret_cast<SC_MONSTER_INFO_PACKET*>(recv_buf);
				while (MainPC == nullptr) {
					FPlatformProcess::Sleep(0.016);
				}
				if (MainPC != nullptr) {
					MainPC->SetAddMonster(p);
				}
				break;
			}
			case SC_MOVE_MONSTER:
			{
				SC_MOVE_MONSTER_PACKET* p = reinterpret_cast<SC_MOVE_MONSTER_PACKET*>(recv_buf);
				while (MainPC == nullptr) {
					FPlatformProcess::Sleep(0.016);
				}
				if (MainPC != nullptr) {
					MainPC->UpdateMonsterToMove(p);
				}
				break;
			}
			case SC_REMOVE_MONSTER:
			{
				SC_REMOVE_MONSTER_PACKET* p = reinterpret_cast<SC_REMOVE_MONSTER_PACKET*>(recv_buf);
				while (MainPC == nullptr) {
					FPlatformProcess::Sleep(0.016);
				}
				if (MainPC != nullptr) {
					MainPC->RemoveMonster(p);
				}
				break;
			}
			case SC_ATTACK_MONSTER:
			{
				SC_ATTACK_MONSTER_PACKET* p = reinterpret_cast<SC_ATTACK_MONSTER_PACKET*>(recv_buf);
				while (MainPC == nullptr) {
					FPlatformProcess::Sleep(0.016);
				}
				if (MainPC != nullptr) {
					MainPC->AttackMonster(p);
				}
				break;
			}
			case SC_CHARACTER_CHANGE:
			{
				SC_CHANGE_CHARACTER_PACKET* p = reinterpret_cast<SC_CHANGE_CHARACTER_PACKET*>(recv_buf);
				while (MainPC == nullptr) {
					FPlatformProcess::Sleep(0.016);
				}
				if (MainPC != nullptr) {
					MainPC->ChangeCharacterState(p);
				}
				break;
			}
			case SC_WEAPON_CHANGE:
			{
				SC_CHANGE_CHARACTER_PACKET* p = reinterpret_cast<SC_CHANGE_CHARACTER_PACKET*>(recv_buf);
				while (MainPC == nullptr) {
					FPlatformProcess::Sleep(0.016);
				}
				if (MainPC != nullptr) {
					MainPC->ChangeCharacterState(p);
				}
				break;
			}
			case SC_ATTACK_SKILL:
			{
				SC_ATTACK_SKILL_PACKET* p = reinterpret_cast<SC_ATTACK_SKILL_PACKET*>(recv_buf);
				while (MainPC == nullptr) {
					FPlatformProcess::Sleep(0.016);
				}
				if (MainPC != nullptr) {
					MainPC->AttackSkill(p);
				}
				break;
			}
			case SC_SPAWN_SPACESHIP:
			{
				SC_SPAWN_SPACESHIP_PACKET* p = reinterpret_cast<SC_SPAWN_SPACESHIP_PACKET*>(recv_buf);
				while (MainPC == nullptr) {
					FPlatformProcess::Sleep(0.016);
				}
				if (MainPC != nullptr) {
					MainPC->SpawnSpaceship(p);
				}
				break;
			}
			case SC_CHANGE_MAP:
			{
				SC_CHANGE_MAP_PACKET* p = reinterpret_cast<SC_CHANGE_MAP_PACKET*>(recv_buf);
				while (MainPC == nullptr) {
					FPlatformProcess::Sleep(0.016);
				}
				if (MainPC != nullptr) {
					MainPC->CHangeMap(p);
				}
				break;
			}
			case SC_DAMAGE_MONSTER:
			{
				SC_DAMAGE_MONSTER_PACKET* p = reinterpret_cast<SC_DAMAGE_MONSTER_PACKET*>(recv_buf);
				while (MainPC == nullptr) {
					FPlatformProcess::Sleep(0.016);
				}
				if (MainPC != nullptr) {
					MainPC->MonsterDamage(p);
				}
				break;
			}
			case SC_GET_ITEM:
			{
				SC_GET_ITEM_PACKET* p = reinterpret_cast<SC_GET_ITEM_PACKET*>(recv_buf);
				while (MainPC == nullptr) {
					FPlatformProcess::Sleep(0.016);
				}
				if (MainPC != nullptr) {
					MainPC->GetItem(p);
				}
				break;
			}
			case SC_COIN_PRICE:
			{
				SC_COIN_PRICE_PACKET* p = reinterpret_cast<SC_COIN_PRICE_PACKET*>(recv_buf);
				while (MainPC == nullptr) {
					FPlatformProcess::Sleep(0.016);
				}
				if (MainPC != nullptr) {
					MainPC->GetCoinPrice(p);
				}
				break;
			}
			case SC_ITEM_BUY:
			{
				SC_ITEM_BUY_PACKET* p = reinterpret_cast<SC_ITEM_BUY_PACKET*>(recv_buf);
				while (MainPC == nullptr) {
					FPlatformProcess::Sleep(0.016);
				}
				if (MainPC != nullptr) {
					MainPC->ItemBuy(p);
				}
				break;
			}
			case SC_BUY_SELL:
			{
				SC_BUY_SELL_PACKET* p = reinterpret_cast<SC_BUY_SELL_PACKET*>(recv_buf);
				while (MainPC == nullptr) {
					FPlatformProcess::Sleep(0.016);
				}
				if (MainPC != nullptr) {
					MainPC->BuySell(p);
				}
				break;
			}
			case SC_MONSTER_ATTACK:
			{
				SC_MONSTER_ATTACK_PACKET* p = reinterpret_cast<SC_MONSTER_ATTACK_PACKET*>(recv_buf);
				while (MainPC == nullptr) {
					FPlatformProcess::Sleep(0.016);
				}
				if (MainPC != nullptr) {
					MainPC->MonsterAttack(p);
				}
				break;
			}
			case SC_QUEST:
			{
				SC_QUEST_PACKET* p = reinterpret_cast<SC_QUEST_PACKET*>(recv_buf);
				while (MainPC == nullptr) {
					FPlatformProcess::Sleep(0.016);
				}
				if (MainPC != nullptr) {
					MainPC->Quest(p);
				}
				break;
			}
			case ALL_STATE:
			{
				ALL_STATE_PACKET* p = reinterpret_cast<ALL_STATE_PACKET*>(recv_buf);
				switch (p->state)
				{
				case PACKET_STATE::SIGNUPFAIL: // Signup failed
					LoginPC->SetSignupNotification(true);
					break;
				case PACKET_STATE::LOGINFAIL: // Login failed
					LoginPC->SetLoginNotification(true);
					break;
				case PACKET_STATE::SUCCESS: // Signup success
					LoginPC->SetSuccessNotification(true);
					break;
				}
				break;
			}
			default:
			{
				break;
			}
			}
		}
	}
	return 0;
}

void Client::Stop()
{
	SafeLoop.Increment();
}

void Client::Exit()
{
	SafeLoop.Increment();
}

void Client::error_display(const char* msg, int err_no)
{
	WCHAR* lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, err_no,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	LocalFree(lpMsgBuf);
}

void Client::StartRecvThread()
{
	recvThread = FRunnableThread::Create(this, TEXT("RecvThread"), 0, TPri_BelowNormal);
}

void Client::StopRecvThread()
{
	closesocket(client_socket);
	WSACleanup();
	delete recvThread;
	recvThread = recvThread;
	SafeLoop.Reset();
}

void Client::Initialize()
{
	WSADATA WSAData;
	ret = WSAStartup(MAKEWORD(2, 2), &WSAData);
	if (0 != ret)
		Error_display(L"Client.cpp : WSAStartup error");
	client_socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, 0, WSA_FLAG_OVERLAPPED);

	SOCKADDR_IN server_addr;
	ZeroMemory(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT_NUM);
	inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

	ret = connect(client_socket, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr));
	if (0 != ret)
		Error_display(L"Client.cpp : Connect error");

	StartRecvThread();
}

void Client::SetLoginPC(ALoginPlayerController* pc)
{
	LoginPC = pc;
}

void Client::SetMainPC(AMainGamePlayerController* pc)
{
	MainPC = pc;
}

void Client::SendToLogin(const FText& id, const FText& pw)
{
	FString myID_FString = *id.ToString();
	FString myPW_FString = *pw.ToString();
	const char* myID = StringCast<ANSICHAR>(*myID_FString).Get();
	const char* myPW = StringCast<ANSICHAR>(*myPW_FString).Get();

	CS_LOGIN_PACKET packet;
	packet.type = CS_LOGIN;
	packet.size = sizeof(CS_LOGIN_PACKET);
	strcpy_s(packet.id, myID);
	strcpy_s(packet.pw, myPW);	

	FString ID_str(myID);
	FString PW_str(myPW);

	ret = send(client_socket, reinterpret_cast<const char*>(&packet), sizeof(packet), 0);
	if (SOCKET_ERROR == ret) {
		Error_display(L"Client.cpp : SendToLogin error");
	}
	
}

void Client::SendToSignup(const FText& nickname, const FText& id, const FText& pw)
{
	FString myNICKNAME_FString = *nickname.ToString();
	FString myID_FString = *id.ToString();
	FString myPW_FString = *pw.ToString();
	const char* myNICKNAME = StringCast<ANSICHAR>(*myNICKNAME_FString).Get();
	const char* myID = StringCast<ANSICHAR>(*myID_FString).Get();
	const char* myPW = StringCast<ANSICHAR>(*myPW_FString).Get();

	CS_SIGNUP_PACKET packet;
	packet.type = CS_SIGNUP;
	packet.size = sizeof(CS_SIGNUP_PACKET);
	strcpy_s(packet.name, myNICKNAME);
	strcpy_s(packet.id, myID);
	strcpy_s(packet.pw, myPW);

	FString NICKNAME_str(myNICKNAME);
	FString ID_str(myID);
	FString PW_str(myPW);

	ret = send(client_socket, reinterpret_cast<const char*>(&packet), sizeof(packet), 0);
	if (SOCKET_ERROR == ret) {
		Error_display(L"Client.cpp : SendToSignup error");
	}
	
}

void Client::SendToMove(AMyCharacter* myCharacter)
{
	CS_MOVE_PACKET packet;
	packet.type = CS_MOVE;
	packet.size = sizeof(CS_MOVE_PACKET);
	packet.character_type = CHARACTER_TYPE::HUMAN;
	packet.sessionID = myCharacter->mySessionID;
	packet.hp = myCharacter->health;
	packet.x = myCharacter->GetActorLocation().X;
	packet.y = myCharacter->GetActorLocation().Y;
	packet.z = myCharacter->GetActorLocation().Z;
	packet.pitch = myCharacter->GetActorRotation().Pitch;
	packet.yaw = myCharacter->GetActorRotation().Yaw;
	packet.roll = myCharacter->GetActorRotation().Roll;
	packet.cpitch = myCharacter->GetControlRotation().Pitch;
	packet.cyaw = myCharacter->GetControlRotation().Yaw;
	packet.croll = myCharacter->GetControlRotation().Roll;
	packet.vx = myCharacter->GetVelocity().X;
	packet.vy = myCharacter->GetVelocity().Y;
	packet.vz = myCharacter->GetVelocity().Z;
	ret = send(client_socket, reinterpret_cast<const char*>(&packet), sizeof(packet), 0);
	if (SOCKET_ERROR == ret) {
		Error_display(L"Client.cpp : send error");
	}
}

void Client::SendToMove(Aspace_ship* myShip)
{
	CS_MOVE_PACKET packet;
	packet.type = CS_MOVE;
	packet.size = sizeof(CS_MOVE_PACKET);
	packet.character_type = CHARACTER_TYPE::SPACESHIP;
	packet.sessionID = myShip->owner_session_id;
	packet.hp = myShip->hp;
	packet.x = myShip->GetActorLocation().X;
	packet.y = myShip->GetActorLocation().Y;
	packet.z = myShip->GetActorLocation().Z;
	packet.pitch = myShip->GetActorRotation().Pitch;
	packet.yaw = myShip->GetActorRotation().Yaw;
	packet.roll = myShip->GetActorRotation().Roll;
	packet.cpitch = myShip->GetControlRotation().Pitch;
	packet.cyaw = myShip->GetControlRotation().Yaw;
	packet.croll = myShip->GetControlRotation().Roll;
	packet.vx = myShip->GetVelocity().X;
	packet.vy = myShip->GetVelocity().Y;
	packet.vz = myShip->GetVelocity().Z;
	packet.ship_speed = myShip->current_speed;
	ret = send(client_socket, reinterpret_cast<const char*>(&packet), sizeof(packet), 0);
	if (SOCKET_ERROR == ret) {
		Error_display(L"Client.cpp : send error");
	}
}

void Client::SendToChangeCharacterState(CS_CHANGE_CHARACTER_PACKET packet)
{
	ret = send(client_socket, reinterpret_cast<const char*>(&packet), sizeof(packet), 0);
	if (SOCKET_ERROR == ret) {
		Error_display(L"Client.cpp : send error");
	}
	
}

void Client::SendToAttackSkill(CS_ATTACK_SKILL_PACKET packet)
{
	ret = send(client_socket, reinterpret_cast<const char*>(&packet), sizeof(packet), 0);
	if (SOCKET_ERROR == ret) {
		Error_display(L"Client.cpp : send error");
	}
	
}

void Client::SendToChangeMap(CS_CHANGE_MAP_PACKET packet)
{
	ret = send(client_socket, reinterpret_cast<const char*>(&packet), sizeof(packet), 0);
	if (SOCKET_ERROR == ret) {
		Error_display(L"Client.cpp : send error");
	}
	
}

void Client::SendToSpawnShip(CS_SPAWN_SPACESHIP_PACKET packet)
{
	ret = send(client_socket, reinterpret_cast<const char*>(&packet), sizeof(packet), 0);
	if (SOCKET_ERROR == ret) {
		Error_display(L"Client.cpp : send error");
	}
	
}

void Client::SendToMonsterDamage(CS_DAMAGE_MONSTER_PACKET packet)
{
	ret = send(client_socket, reinterpret_cast<const char*>(&packet), sizeof(packet), 0);
	if (SOCKET_ERROR == ret) {
		Error_display(L"Client.cpp : send error");
	}
	
}

void Client::SendToDropCoin(CS_GET_ITEM_PACKET packet)
{
	ret = send(client_socket, reinterpret_cast<const char*>(&packet), sizeof(packet), 0);
	if (SOCKET_ERROR == ret) {
		Error_display(L"Client.cpp : send error");
	}
	
}

void Client::SendToGetCoinPirce(CS_COIN_PRICE_PACKET packet)
{
	ret = send(client_socket, reinterpret_cast<const char*>(&packet), sizeof(packet), 0);
	if (SOCKET_ERROR == ret) {
		Error_display(L"Client.cpp : send error");
	}
	
}

void Client::SendToItemBuy(CS_ITEM_BUY_PACKET packet)
{
	ret = send(client_socket, reinterpret_cast<const char*>(&packet), sizeof(packet), 0);
	if (SOCKET_ERROR == ret) {
		Error_display(L"Client.cpp : send error");
	}
	
}

void Client::SendToCoinBuySell(CS_BUY_SELL_PACKET packet)
{
	ret = send(client_socket, reinterpret_cast<const char*>(&packet), sizeof(packet), 0);
	if (SOCKET_ERROR == ret) {
		Error_display(L"Client.cpp : send error");
	}
	
}
