// Fill out your copyright notice in the Description page of Project Settings.


#include "damage_indicator_ui.h"
#include "Animation/WidgetAnimation.h"

void Udamage_indicator_ui::NativeConstruct()
{
	Super::NativeConstruct();
	UUserWidget::PlayAnimation(damage_anim);

	EndDelegate.BindDynamic(this, &Udamage_indicator_ui::AnimationFinished);
	BindToAnimationFinished(damage_anim, EndDelegate);
}


void Udamage_indicator_ui::AnimationFinished()
{
	RemoveFromParent();
}