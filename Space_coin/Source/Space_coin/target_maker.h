// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "targeting_ui.h"
#include "target_maker.generated.h"


UCLASS()
class SPACE_COIN_API Atarget_maker : public AActor
{
	GENERATED_BODY()
public:
	Atarget_maker();
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI)
		class UWidgetComponent* targeting;
	class Utargeting_ui* targeting_ui;
};
