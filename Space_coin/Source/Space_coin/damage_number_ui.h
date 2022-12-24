// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "monster.h"
#include "Components/TextBlock.h"
#include "damage_number_ui.generated.h"
UCLASS()
class SPACE_COIN_API Udamage_number_ui : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(Meta = (BindWidgetAnim), Transient)
		class UWidgetAnimation* damage_fade;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (BindWidget))
		UTextBlock* damage_number_text;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float damage_amount;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	Amonster* damage_target;
	bool critical;
public:
	virtual void NativeConstruct() override;

	virtual void NativePreConstruct() override;

	FWidgetAnimationDynamicEvent EndDelegate;
	UFUNCTION()
		void AnimationFinished();
};
