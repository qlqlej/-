// Fill out your copyright notice in the Description page of Project Settings.


#include "sword_skill_cooltime_ui.h"
#include "Components/ProgressBar.h"
#include "Engine.h"

void Usword_skill_cooltime_ui::NativeConstruct()
{
	Super::NativeConstruct();

}

void Usword_skill_cooltime_ui::UpdateUltimateCooltime(float cooltime)
{
	ultimate_skill_bar->SetPercent(cooltime);
}
void Usword_skill_cooltime_ui::UpdateDefenseCooltime(float cooltime)
{
	defense_skill_bar->SetPercent(cooltime);
}
void Usword_skill_cooltime_ui::UpdateSlashCooltime(float cooltime)
{
	slash_skill_bar->SetPercent(cooltime);
}

