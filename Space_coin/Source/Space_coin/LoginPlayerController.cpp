// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "LoginWidgetClass.h"

ALoginPlayerController::ALoginPlayerController()
{
	static ConstructorHelpers::FClassFinder<ULoginWidgetClass> WB_Title(TEXT("/Game/SpaceCoinContent/UI/LoginUI/LoginUI"));
	if (WB_Title.Succeeded())
	{
		TitleUIClass = WB_Title.Class;
	}
}

void ALoginPlayerController::BeginPlay()
{
	Super::BeginPlay();

	TitleUIObject = CreateWidget<ULoginWidgetClass>(this, TitleUIClass);
	TitleUIObject->AddToViewport();
	
	ALoginPlayerController::bShowMouseCursor = true;
	SetInputMode(FInputModeUIOnly());

	auto value = ESlateVisibility::Hidden;
	TitleUIObject->SetVisibilityNotificationFrame(value);
}

void ALoginPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (true == signupNotify) { // In this case signup failed
		auto value = ESlateVisibility::Visible;
		TitleUIObject->SetVisibilityNotificationFrame(value);
		TitleUIObject->SetNotiticationMessage(FText::FromString("The ID that already exists."));
		signupNotify = false;
	}

	if (true == loginNotify) { // In this case login failed
		auto value = ESlateVisibility::Visible;
		TitleUIObject->SetVisibilityNotificationFrame(value);
		TitleUIObject->SetNotiticationMessage(FText::FromString("The input values is incorrect."));
		loginNotify = false;
	}

	if (true == successNotify) { // In this case signup success
		TitleUIObject->SetSuccessSignup();
		successNotify = false;
	}

	if (true == bchangeMap) {
		Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));		
		TitleUIObject->ChangeMap(GameInstanceRef->sc_login_info_packet.map_type);
		bchangeMap = false;
	}
}

void ALoginPlayerController::SetVisibilityNotificationFrame(ESlateVisibility& value)
{
	TitleUIObject->SetVisibilityNotificationFrame(value);
}

void ALoginPlayerController::SetNotificationMessage(const FText& msg)
{
	TitleUIObject->SetNotiticationMessage(msg);
}

void ALoginPlayerController::ChangeMap(SC_LOGIN_INFO_PACKET* packet)
{
	Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GameInstanceRef->SetLoginInfoData(packet);
	bchangeMap = true;
}