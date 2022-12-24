#pragma once

#include "game_info.h"
#include "Blueprint/UserWidget.h"
#include "ui_player_info.generated.h"

UCLASS()
class SPACE_COIN_API Uui_player_info : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* name_text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* money_text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UProgressBar* hp_bar;

	class Ugame_instance* GameInstanceRef;

public:
	virtual void NativeConstruct() override;
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;


};
