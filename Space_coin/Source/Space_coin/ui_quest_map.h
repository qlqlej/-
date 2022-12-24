#pragma once

#include "game_info.h"
#include "Blueprint/UserWidget.h"
#include "ui_quest_map.generated.h"

UCLASS()
class SPACE_COIN_API Uui_quest_map : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class Uui_quest* quest_wb;

	bool quest_level_change;

	int quest_level, quest_now_rate, quest_goal_rate;

public:
	virtual void NativeConstruct() override;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent);

	void PressTabKey();

};