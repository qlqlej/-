// Fill out your copyright notice in the Description page of Project Settings.


#include "death_ui.h"
#include "Animation/WidgetAnimation.h"

void Udeath_ui::NativeConstruct()
{
	Super::NativeConstruct();
	UUserWidget::PlayAnimation(death_anim);

	EndDelegate.BindDynamic(this, &Udeath_ui::AnimationFinished);
	BindToAnimationFinished(death_anim, EndDelegate);
}

void Udeath_ui::AnimationFinished()
{
	RemoveFromParent();
}