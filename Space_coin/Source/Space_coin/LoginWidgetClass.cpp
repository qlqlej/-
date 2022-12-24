// Fill out your copyright notice in the Description page of Project Settings.


#include "LoginWidgetClass.h"

void ULoginWidgetClass::NativeConstruct()
{
	Super::NativeConstruct();

	gamemode = Cast<ALoginGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	LoginBtn = (UButton*)GetWidgetFromName(TEXT("LoginButton"));
	if (nullptr != LoginBtn) {
		LoginBtn->OnClicked.AddDynamic(this, &ULoginWidgetClass::LoginButtonClick);
	}

	SignupBtn = (UButton*)GetWidgetFromName(TEXT("SignupButton"));
	if (nullptr != SignupBtn) {
		SignupBtn->OnClicked.AddDynamic(this, &ULoginWidgetClass::SignupButtonClick);
	}

	ExitBtn = (UButton*)GetWidgetFromName(TEXT("ExitButton"));
	if (nullptr != ExitBtn) {
		ExitBtn->OnClicked.AddDynamic(this, &ULoginWidgetClass::ExitButtonClick);
	}

	SignupCheckBtn = (UButton*)GetWidgetFromName(TEXT("SignupCheckButton"));
	if (nullptr != SignupCheckBtn) {
		SignupCheckBtn->OnClicked.AddDynamic(this, &ULoginWidgetClass::SignupCheckButtonClick);
	}

	ReturnLoginBtn = (UButton*)GetWidgetFromName(TEXT("ReturnLoginButton"));
	if (nullptr != ReturnLoginBtn) {
		ReturnLoginBtn->OnClicked.AddDynamic(this, &ULoginWidgetClass::ReturnLoginButtonClick);
	}

	NotificationBtn = (UButton*)GetWidgetFromName(TEXT("NotificationButton"));
	if (nullptr != NotificationBtn) {
		NotificationBtn->OnClicked.AddDynamic(this, &ULoginWidgetClass::NotificationButtonClick);
	}

	Signup_Box = (UVerticalBox*)GetWidgetFromName(TEXT("SignupBox"));
	Login_Box = (UVerticalBox*)GetWidgetFromName(TEXT("LoginInputBox"));
	Login_ID_Edittext = (UEditableText*)GetWidgetFromName(TEXT("IDEditableText"));
	Login_PW_Edittext = (UEditableText*)GetWidgetFromName(TEXT("PWEditableText"));
	Singup_Nickname_Edittext = (UEditableText*)GetWidgetFromName(TEXT("NickNameSignupText"));
	Singup_ID_Edittext = (UEditableText*)GetWidgetFromName(TEXT("IDSignupText"));
	Singup_PW1_Edittext = (UEditableText*)GetWidgetFromName(TEXT("PWSignupText01"));
	Singup_PW2_Edittext = (UEditableText*)GetWidgetFromName(TEXT("PWSignupText02"));
	Notification_Canvas_panel = (UCanvasPanel*)GetWidgetFromName(TEXT("NotificationCanvasPanel"));
	Notification_Text = (UEditableText*)GetWidgetFromName(TEXT("NotificationText"));
}

void ULoginWidgetClass::LoginButtonClick()
{
	FString ID, PW;	
	ID = Login_ID_Edittext->GetText().ToString();
	PW = Login_PW_Edittext->GetText().ToString();
	if (false == gamemode->LoginCheck(Login_ID_Edittext->GetText(), Login_PW_Edittext->GetText())) {
		Notification_Canvas_panel->SetVisibility(ESlateVisibility::Visible);
		Notification_Text->SetText(FText::FromString("Check the input value!"));
		LoginBtn->SetIsEnabled(false);
		SignupBtn->SetIsEnabled(false);
		ExitBtn->SetIsEnabled(false);
	}
}

void ULoginWidgetClass::SignupButtonClick()
{
	Login_ID_Edittext->SetText(FText::FromString(""));
	Login_PW_Edittext->SetText(FText::FromString(""));
	Signup_Box->SetVisibility(ESlateVisibility::Visible);
	Login_Box->SetVisibility(ESlateVisibility::Hidden);
}

void ULoginWidgetClass::ExitButtonClick()
{
	Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));	
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}

void ULoginWidgetClass::SignupCheckButtonClick()
{
	FString NICKNAME, ID, PW1, PW2;
	NICKNAME = Singup_Nickname_Edittext->GetText().ToString();
	ID = Singup_ID_Edittext->GetText().ToString();
	PW1 = Singup_PW1_Edittext->GetText().ToString();
	PW2 = Singup_PW2_Edittext->GetText().ToString();
	if (false == gamemode->SignupCheck(Singup_Nickname_Edittext->GetText(), Singup_ID_Edittext->GetText(), Singup_PW1_Edittext->GetText(), Singup_PW2_Edittext->GetText())) {
		Notification_Canvas_panel->SetVisibility(ESlateVisibility::Visible);
		Notification_Text->SetText(FText::FromString("Check the input value!"));
		SignupCheckBtn->SetIsEnabled(false);
		ReturnLoginBtn->SetIsEnabled(false);
	}
}

void ULoginWidgetClass::ReturnLoginButtonClick()
{
	Singup_Nickname_Edittext->SetText(FText::FromString(""));
	Singup_ID_Edittext->SetText(FText::FromString(""));
	Singup_PW1_Edittext->SetText(FText::FromString(""));
	Singup_PW2_Edittext->SetText(FText::FromString(""));
	Signup_Box->SetVisibility(ESlateVisibility::Hidden);
	Login_Box->SetVisibility(ESlateVisibility::Visible);
}

void ULoginWidgetClass::NotificationButtonClick()
{
	Notification_Canvas_panel->SetVisibility(ESlateVisibility::Hidden);
	SignupCheckBtn->SetIsEnabled(true);
	ReturnLoginBtn->SetIsEnabled(true);
	LoginBtn->SetIsEnabled(true);
	SignupBtn->SetIsEnabled(true);
	ExitBtn->SetIsEnabled(true);

}

void ULoginWidgetClass::SetVisibilityNotificationFrame(ESlateVisibility& value)
{
	Notification_Canvas_panel->SetVisibility(value);
	if (ESlateVisibility::Visible == Notification_Canvas_panel->GetVisibility()) {
		if (ESlateVisibility::Visible == Signup_Box->GetVisibility()) {
			SignupCheckBtn->SetIsEnabled(false);
			ReturnLoginBtn->SetIsEnabled(false);
		}
		else if (ESlateVisibility::Visible == Login_Box->GetVisibility()) {
			LoginBtn->SetIsEnabled(false);
			SignupBtn->SetIsEnabled(false);
			ExitBtn->SetIsEnabled(false);
		}
	}
}

void ULoginWidgetClass::SetNotiticationMessage(const FText& msg)
{
	Notification_Text->SetText(msg);
}

void ULoginWidgetClass::SetSuccessSignup()
{
	Singup_Nickname_Edittext->SetText(FText::FromString(""));
	Singup_ID_Edittext->SetText(FText::FromString(""));
	Singup_PW1_Edittext->SetText(FText::FromString(""));
	Singup_PW2_Edittext->SetText(FText::FromString(""));
	Signup_Box->SetVisibility(ESlateVisibility::Hidden);
	Login_Box->SetVisibility(ESlateVisibility::Visible);
}

void ULoginWidgetClass::ChangeMap(MAP_TYPE map)
{
	switch (map) {
	case MAP_TYPE::SPACE:
		UGameplayStatics::OpenLevel(this, "SpaceLevel");
		break;
	case MAP_TYPE::ICE:
		UGameplayStatics::OpenLevel(this, "IcePlanet");
		break;
	case MAP_TYPE::SAND:
		UGameplayStatics::OpenLevel(this, "SandPlanet");
		break;
	case MAP_TYPE::WATER:
		UGameplayStatics::OpenLevel(this, "WaterPlanet");
		break;
	}
}
