// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameModeBase.h"
#include "MyCharacter.h"
#include "Kismet/GameplayStatics.h"

AMainGameModeBase::AMainGameModeBase()
{	
	static ConstructorHelpers::FClassFinder<APawn>PlayerPawnClassFinder(TEXT("/Game/SpaceCoinContent/Blueprint/BP_MyCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	PlayerControllerClass = AMainGamePlayerController::StaticClass();
}

void AMainGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}

void AMainGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
	client = GameInstanceRef->client;	
}

void AMainGameModeBase::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	client->SetMainPC(nullptr);
}
