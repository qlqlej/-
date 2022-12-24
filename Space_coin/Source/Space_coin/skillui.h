// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "game_info.h"
#include "Blueprint/UserWidget.h"
#include "skillui.generated.h"

UCLASS()
class SPACE_COIN_API Uskillui : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class Uskill_cooltime_ui* cooltime_wb;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class Usword_skill_cooltime_ui* sword_cooltime_wb;
public:
	virtual void NativeConstruct() override;
	void SetVisible();
	void SetHidden();
};
