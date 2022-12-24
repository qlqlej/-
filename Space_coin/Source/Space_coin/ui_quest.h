#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ui_quest.generated.h"

UCLASS()
class SPACE_COIN_API Uui_quest : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* quest_text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* clear_quest_text;

	int quest_level;
	int quest_goal_rate;
	int quest_now_rate;

	FString str_q;
	FText text_q;

	FString str_cq;
	FText text_cq;

	class Ugame_instance* GameInstanceRef;

public:
	virtual void NativeConstruct() override;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
