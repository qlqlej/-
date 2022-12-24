#pragma once

#include "game_info.h"
#include "Blueprint/UserWidget.h"
#include "ui_coin_map.generated.h"

UCLASS()
class SPACE_COIN_API Uui_coin_map : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class Uui_coin_prices* coin_prices_wb;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class Uui_player_balance* player_balance_wb;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class Uui_player_holdings* player_holdings_wb;

	bool get_data = false;

public:
	virtual void NativeConstruct() override;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent);

	void PressPKey();

};
