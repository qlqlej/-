// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "game_instance.h"
#include "MainGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SPACE_COIN_API AMainGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AMainGameModeBase();

	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void BeginPlay() override;
	virtual void Logout(AController* Exiting) override;

private:
	Client* client;
};
