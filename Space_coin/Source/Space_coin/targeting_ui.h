// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "targeting_ui.generated.h"

UCLASS()
class SPACE_COIN_API Utargeting_ui : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(Meta = (BindWidgetAnim), Transient)
		class UWidgetAnimation* lock_on_anim;
public:
	virtual void NativeConstruct() override;

};

