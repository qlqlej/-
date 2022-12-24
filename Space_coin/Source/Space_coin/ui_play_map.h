#pragma once

#include "game_info.h"
#include "Blueprint/UserWidget.h"
#include "ui_play_map.generated.h"

UCLASS()
class SPACE_COIN_API Uui_play_map : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class Uui_loading* loading_wb;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class Uui_quest_alarm* quest_alarm_wb;

public:
	virtual void NativeConstruct() override;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	void LoadingUI();

	void QuestAlarm();

};
