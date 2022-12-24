// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "LoginPlayerController.h"
#include "MainGamePlayerController.h"
#include "MyCharacter.h"
#include <array>
#include <WS2tcpip.h>
#pragma comment (lib, "WS2_32.LIB")

#include "..\..\..\SpaceCoin_Server\SpaceCoin_Server\protocol.h"

using namespace std;

class ALoginPlayerController;
class AMainGamePlayerController;
/**
 * 
 */
class SPACE_COIN_API Client : public FRunnable
{
public:
	ALoginPlayerController* LoginPC;
	AMainGamePlayerController* MainPC;
public:
	FRunnableThread*		recvThread;
	FThreadSafeCounter 		SafeLoop;
	SOCKET					client_socket;
	const char*				SERVER_IP = "127.0.0.1";	//180.230.122.47
	int						ret;
	array <AActor*, MAX_USER> players;
public:
	Client();
	~Client();

	void Error_display(FString msg);

	virtual bool Init();
	virtual uint32 Run();
	virtual void Stop();
	virtual void Exit();

	static Client* GetClient()
	{
		static Client ins;
		return &ins;
	}

	void error_display(const char* msg, int err_no);
	void StartRecvThread();
	void StopRecvThread();
	void Initialize();

	void SetLoginPC(ALoginPlayerController* pc);
	void SetMainPC(AMainGamePlayerController* pc);

	void SendToLogin(const FText& id, const FText& pw);
	void SendToSignup(const FText& nickname, const FText& id, const FText& pw);	
	void SendToMove(AMyCharacter* myCharacter);
	void SendToMove(Aspace_ship* myShip);
	void SendToChangeCharacterState(CS_CHANGE_CHARACTER_PACKET packet);
	void SendToAttackSkill(CS_ATTACK_SKILL_PACKET packet);
	void SendToChangeMap(CS_CHANGE_MAP_PACKET packet);
	void SendToSpawnShip(CS_SPAWN_SPACESHIP_PACKET packet);
	void SendToMonsterDamage(CS_DAMAGE_MONSTER_PACKET packet);
	void SendToDropCoin(CS_GET_ITEM_PACKET packet);
	void SendToGetCoinPirce(CS_COIN_PRICE_PACKET packet);
	void SendToItemBuy(CS_ITEM_BUY_PACKET packet);
	void SendToCoinBuySell(CS_BUY_SELL_PACKET packet);
};
