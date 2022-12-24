// Copyright Epic Games, Inc. All Rights Reserved.


#include "Space_coinGameModeBase.h"
#include "MyCharacter.h"

ASpace_coinGameModeBase::ASpace_coinGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn>PlayerPawnClassFinder(TEXT("/Game/SpaceCoinContent/Blueprint/BP_MyCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}

void ASpace_coinGameModeBase::StartPlay()
{
	Super::StartPlay();
	if (GEngine)
	{
	}
}

void ASpace_coinGameModeBase::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
}
