#pragma once

#include "game_info.h"
#include "Blueprint/UserWidget.h"
#include "ui_coin_trading_sell.generated.h"

UCLASS()
class SPACE_COIN_API Uui_coin_trading_sell : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UCheckBox* CheckBox_sell_limits;  // 지정가

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UCheckBox* CheckBox_sell_marketPrice;  // 시장가

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UCheckBox* CheckBox_sell_auto;  // 자동

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* TextBlock_sell_orderPossible;  // 주문가능금액

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UEditableTextBox* EditableTextBox_sell_orderPrice;  // 주문가격

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UEditableTextBox* EditableTextBox_sell_orderAmount;  // 주문수량

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class USlider* Slider_sell_orderAmount;  // 주문수량

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* TextBlock_sell_orderAmount_rate;  // 주문수량비율

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UEditableTextBox* EditableTextBox_sell_sum;  // 주문금액

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UButton* Button_sell_button;  // 매수

protected:
	virtual void NativeConstruct() override;
	
	void OnCheckBoxClick();
	void SetTextBlockSellOrderPossible(float set_order_possible);
	void SetTextBlockSellOrderAmount(float set_order_amount);

	UFUNCTION(BlueprintCallable)
	void OnSellButtonClick();

};
