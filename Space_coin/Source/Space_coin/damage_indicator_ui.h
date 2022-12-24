// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "damage_indicator_ui.generated.h"

UCLASS()
class SPACE_COIN_API Udamage_indicator_ui : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(Meta = (BindWidgetAnim), Transient)
		class UWidgetAnimation* damage_anim;

public:
	virtual void NativeConstruct() override;

	FWidgetAnimationDynamicEvent EndDelegate;
	UFUNCTION()
		void AnimationFinished();
};
