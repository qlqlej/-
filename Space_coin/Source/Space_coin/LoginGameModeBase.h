// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "game_instance.h"
#include "LoginGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SPACE_COIN_API ALoginGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	ALoginGameModeBase();

	virtual void BeginPlay() override;
	virtual void Logout(AController* Exiting) override;

	UFUNCTION()
		bool LoginCheck(const FText& id, const FText& pw);
	UFUNCTION()
		bool SignupCheck(const FText& nickname, const FText& id, const FText& pw1, const FText& pw2);
private:
	Client* client;
};
