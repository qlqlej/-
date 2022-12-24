// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Space_coinGameModeBase.generated.h"
/**
 * 
 */
UCLASS()
class SPACE_COIN_API ASpace_coinGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	ASpace_coinGameModeBase();
	
	virtual void StartPlay() override;
	virtual void Logout(AController* Exiting) override;
};
