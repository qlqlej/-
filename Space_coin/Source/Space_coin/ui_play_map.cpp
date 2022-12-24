#include "ui_play_map.h"
#include "ui_coin_map.h"
#include "ui_player_info.h"
#include "ui_loading.h"
#include "ui_setting.h"
#include "ui_quest_alarm.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "MainGamePlayerController.h"

void Uui_play_map::NativeConstruct()
{
	Super::NativeConstruct();
	
	loading_wb = Cast<Uui_loading>(GetWidgetFromName(TEXT("loading_wb")));
	quest_alarm_wb = Cast<Uui_quest_alarm>(GetWidgetFromName(TEXT("quest_alarm_wb")));

	loading_wb->SetVisibility(ESlateVisibility::Hidden);
	quest_alarm_wb->SetVisibility(ESlateVisibility::Hidden);
}

void Uui_play_map::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}


void Uui_play_map::LoadingUI()
{
	loading_wb->SetVisibility(ESlateVisibility::Visible);
}

void Uui_play_map::QuestAlarm()
{
	quest_alarm_wb->SetVisibility(ESlateVisibility::Visible);
	FTimerHandle WaitHandle;
	float wait_time = 3.0f;
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]() {
		quest_alarm_wb->SetVisibility(ESlateVisibility::Hidden);
		}), wait_time, false);
}
