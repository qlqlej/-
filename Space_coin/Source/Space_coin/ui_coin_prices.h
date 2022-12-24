#pragma once

#include "game_info.h"
#include "Blueprint/UserWidget.h"
#include "ui_coin_prices.generated.h"

UCLASS()
class SPACE_COIN_API Uui_coin_prices : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class Uui_coin_fail_or_success* coin_fail_or_success_wb;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class Uui_coin_map_loading* coin_map_loading_wb;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UListView* coin_price_list_view;  

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UEditableTextBox* EditableTextBox_buy_orderPrice;  // 주문가격

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UEditableTextBox* EditableTextBox_buy_orderAmount;  // 주문수량

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* TextBox_buy_sum;  // 주문금액

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UButton* Button_buy_button; // 매수

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UEditableTextBox* EditableTextBox_sell_orderPrice;  // 주문가격

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UEditableTextBox* EditableTextBox_sell_orderAmount;  // 주문수량

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* TextBox_sell_sum;  // 주문금액

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UButton* Button_sell_button;  // 매도

	class AMainGamePlayerController* pc;

protected:
	virtual void NativeConstruct() override;  // 생성자

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	class Udata_coin_price* a_data;
	class Udata_coin_price* b_data;
	class Udata_coin_price* c_data;

	class Udata_coin_price* data;

	int coin_type;

	int buy_price;
	int buy_count; 
	int sell_price;
	int sell_count;

	FString click_coin_name;
	int click_coin_price;

	int set_data_count;

	UFUNCTION(BlueprintCallable)
	void InitList();

	void SetData();

	UFUNCTION(BlueprintCallable)
	void ItemClick(UObject* obj);

public:
	void SetCoinName(const FString& name);
	void SetCoinPrice(int32 price);
	void SetCoinUnitsTraded24H(float amount);
	void SetCoinAccTradeValue24H(float value);
	void SetCoinMaxPrice(int32 price);
	void SetCoinMinPrice(int32 price);
	void SetCoinFluctateRate24H(float rate);
	void SetCoinPrevClosingPrice(float price);

	UFUNCTION()
	void OnBuyOrderPriceChange(const FText& Text, ETextCommit::Type CommitMethod);

	UFUNCTION()
	void OnBuyOrderAmountChange(const FText& Text, ETextCommit::Type CommitMethod);

	UFUNCTION()
	void OnSellOrderPriceChange(const FText& Text, ETextCommit::Type CommitMethod);

	UFUNCTION()
	void OnSellOrderAmountChange(const FText& Text, ETextCommit::Type CommitMethod);

	UFUNCTION(BlueprintCallable)
	void OnBuyButtonClick();

	UFUNCTION(BlueprintCallable)
	void OnSellButtonClick();

};
