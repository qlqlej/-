// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginGameModeBase.h"
#include "LoginPlayerController.h"
#include "Kismet/GameplayStatics.h"

ALoginGameModeBase::ALoginGameModeBase()
{
	PlayerControllerClass = ALoginPlayerController::StaticClass();
}

void ALoginGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
	client = GameInstanceRef->client;
	client->SetLoginPC(Cast<ALoginPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)));
}

void ALoginGameModeBase::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
}

bool ALoginGameModeBase::LoginCheck(const FText& id, const FText& pw)
{
	if(id.IsEmpty() || pw.IsEmpty())
		return false;
	else {
		client->SendToLogin(id, pw);
		return true;
	}
}

bool ALoginGameModeBase::SignupCheck(const FText& nickname, const FText& id, const FText& pw1, const FText& pw2)
{
	if (nickname.IsEmpty() || id.IsEmpty() || pw1.IsEmpty() || pw2.IsEmpty())
		return false;
	else if (pw1.ToString() != pw2.ToString())
		return false;
	else{
		client->SendToSignup(nickname, id, pw1);
		return true;
	}
}
