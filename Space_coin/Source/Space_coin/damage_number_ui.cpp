// Fill out your copyright notice in the Description page of Project Settings.


#include "damage_number_ui.h"
#include "MyCharacter.h"
#include "game_instance.h"
#include "MainGamePlayerController.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#define LOCTEXT_NAMESPACE "UMG"
void Udamage_number_ui::NativeConstruct()
{
	Super::NativeConstruct();
	PlayAnimationForward(damage_fade);
	EndDelegate.BindDynamic(this, &Udamage_number_ui::AnimationFinished);
	BindToAnimationFinished(damage_fade, EndDelegate);
}
void Udamage_number_ui::NativePreConstruct()
{
	Super::NativePreConstruct();
	AMyCharacter* player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (critical)
	{
		FText text = FText::Format(LOCTEXT("ExampleFText", "{0}!"), damage_amount);
		damage_number_text->SetText(text);
	}
	else
	{
		FText text = FText::Format(LOCTEXT("ExampleFText", "{0}"), damage_amount);
		damage_number_text->SetText(text);
	}

}

void Udamage_number_ui::AnimationFinished()
{
	RemoveFromParent();
}
