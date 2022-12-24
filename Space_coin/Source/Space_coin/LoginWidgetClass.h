// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/VerticalBox.h"
#include "Components/EditableText.h"
#include "Components/CanvasPanel.h"
#include "Kismet/GameplayStatics.h"
#include "game_instance.h"
#include "LoginGameModeBase.h"
#include "LoginWidgetClass.generated.h"

class UButton;
class UVerticalBox;
class UEditableText;
class UCanvasPanel;
/**
 * 
 */
UCLASS()
class SPACE_COIN_API ULoginWidgetClass : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

	ALoginGameModeBase* gamemode;

	UFUNCTION()	
		void LoginButtonClick();
	UFUNCTION()	
		void SignupButtonClick();
	UFUNCTION()	
		void ExitButtonClick();
	UFUNCTION()	
		void SignupCheckButtonClick();
	UFUNCTION()
		void ReturnLoginButtonClick();
	UFUNCTION()
		void NotificationButtonClick();

public:
		void SetVisibilityNotificationFrame(ESlateVisibility& value);
		void SetNotiticationMessage(const FText& msg);
		void SetSuccessSignup();
		void ChangeMap(MAP_TYPE map);

private:
	UPROPERTY()	
		UButton* LoginBtn;
	UPROPERTY()	
		UButton* ExitBtn;
	UPROPERTY()	
		UButton* SignupBtn;
	UPROPERTY()	
		UButton* SignupCheckBtn;
	UPROPERTY()	
		UButton* ReturnLoginBtn;
	UPROPERTY()	
		UVerticalBox* Signup_Box;
	UPROPERTY()	
		UVerticalBox* Login_Box;
	UPROPERTY()
		UEditableText* Login_ID_Edittext;
	UPROPERTY()
		UEditableText* Login_PW_Edittext;
	UPROPERTY()
		UEditableText* Singup_Nickname_Edittext;
	UPROPERTY()
		UEditableText* Singup_ID_Edittext;
	UPROPERTY()
		UEditableText* Singup_PW1_Edittext;
	UPROPERTY()
		UEditableText* Singup_PW2_Edittext;
	UPROPERTY()
		UCanvasPanel* Notification_Canvas_panel;
	UPROPERTY()
		UEditableText* Notification_Text;
	UPROPERTY()
		UButton* NotificationBtn;
};
