// Fill out your copyright notice in the Description page of Project Settings.


#include "skillui.h"
#include "skill_cooltime_ui.h"
#include "sword_skill_cooltime_ui.h"
#include "MainGamePlayerController.h"
// Add default functionality here for any Iskillui functions that are not pure virtual.
void Uskillui::NativeConstruct()
{
	Super::NativeConstruct();
	cooltime_wb->SetVisibility(ESlateVisibility::Visible);
	sword_cooltime_wb->SetVisibility(ESlateVisibility::Visible);
}
