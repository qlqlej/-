// Fill out your copyright notice in the Description page of Project Settings.


#include "skill_cooltime_ui.h"
#include "Components/ProgressBar.h"
#include "Engine.h"

// Add default functionality here for any Iskill_cooltime_ui functions that are not pure virtual.
void Uskill_cooltime_ui::NativeConstruct()
{
	Super::NativeConstruct();

}

void Uskill_cooltime_ui::UpdateDashCooltime(float cooltime)
{
	dash_skill_bar->SetPercent(cooltime);
}
void Uskill_cooltime_ui::UpdateLauncherCooltime(float cooltime)
{
	launcher_skill_bar->SetPercent(cooltime);
}
void Uskill_cooltime_ui::UpdateSniperCooltime(float cooltime)
{
	sniper_skill_bar->SetPercent(cooltime);
}
void Uskill_cooltime_ui::UpdateMissileCooltime(float cooltime)
{
	missile_skill_bar->SetPercent(cooltime);
}

