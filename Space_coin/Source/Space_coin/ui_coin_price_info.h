#pragma once

#include "game_info.h"
#include "Blueprint/UserWidget.h"
#include "ui_coin_price_info.generated.h"

UCLASS()
class SPACE_COIN_API Uui_coin_price_info : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class Uui_coin_price* coin_price_wb_1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class Uui_coin_price* coin_price_wb_2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class Uui_coin_price* coin_price_wb_3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UButton* coin_price_wb_1_button;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UButton* coin_price_wb_2_button;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UButton* coin_price_wb_3_button;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* coin_name;  // 이름

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* coin_price;  // 시세

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* coin_units_traded_24H;  // 거래량(24H)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* coin_acc_trade_value_24H;  // 거래금액(24H)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* coin_max_price;  // 고가(당일)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* coin_min_price;  // 저가(당일)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* coin_fluctate_rate_24H;  // 변동률

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* coin_prev_closing_price;  // 전일종가

	class AMainGamePlayerController* pc;

protected:
	virtual void NativeConstruct() override;  // 생성자

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	class Udata_coin_price* a_data;
	class Udata_coin_price* b_data;
	class Udata_coin_price* c_data;

	UFUNCTION(BlueprintCallable)
		void InitList();

	void SetData();

	UFUNCTION(BlueprintCallable)
	void OnCoin1ButtonClick();

	UFUNCTION(BlueprintCallable)
	void OnCoin2ButtonClick();

	UFUNCTION(BlueprintCallable)
	void OnCoin3ButtonClick();

public:
	void SetCoinName(const FString& name);
	void SetCoinPrice(int32 price);
	void SetCoinUnitsTraded24H(float amount);
	void SetCoinAccTradeValue24H(float value);
	void SetCoinMaxPrice(int32 price);
	void SetCoinMinPrice(int32 price);
	void SetCoinFluctateRate24H(float rate);
	void SetCoinPrevClosingPrice(float price);

};
