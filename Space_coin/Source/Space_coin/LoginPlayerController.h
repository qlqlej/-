// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "..\..\..\SpaceCoin_Server\SpaceCoin_Server\protocol.h"
#include "LoginPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SPACE_COIN_API ALoginPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	bool signupNotify = false;
	bool loginNotify = false;
	bool successNotify = false;
	bool bchangeMap = false;

	ALoginPlayerController();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class ULoginWidgetClass> TitleUIClass;
	class ULoginWidgetClass* TitleUIObject;

	void SetVisibilityNotificationFrame(ESlateVisibility& value);
	void SetSignupNotification(bool value) { signupNotify = value; }
	void SetLoginNotification(bool value) { loginNotify = value; }
	void SetSuccessNotification(bool value) { successNotify = value; }
	void SetNotificationMessage(const FText& msg);
	void ChangeMap(SC_LOGIN_INFO_PACKET* packet);
};
