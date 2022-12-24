// Fill out your copyright notice in the Description page of Project Settings.


#include "targeting_ui.h"
#include "Animation/WidgetAnimation.h"

void Utargeting_ui::NativeConstruct()
{
	Super::NativeConstruct();
	UUserWidget::PlayAnimation(lock_on_anim);
}
