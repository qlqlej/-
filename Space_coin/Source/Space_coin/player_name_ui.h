// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Blueprint/UserWidget.h"
#include "player_name_ui.generated.h"

UCLASS()
class SPACE_COIN_API Uplayer_name_ui : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* player_name;
public:
	virtual void NativeConstruct() override;

};
