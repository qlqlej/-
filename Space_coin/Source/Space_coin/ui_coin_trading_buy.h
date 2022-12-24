#pragma once

#include "game_info.h"
#include "Blueprint/UserWidget.h"
#include "ui_coin_trading_buy.generated.h"

UCLASS()
class SPACE_COIN_API Uui_coin_trading_buy : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UCheckBox* CheckBox_buy_limits;  // 지정가

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UCheckBox* CheckBox_buy_marketPrice;  // 시장가

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UCheckBox* CheckBox_buy_auto;  // 자동

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* TextBlock_buy_orderPossible;  // 주문가능금액

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UEditableTextBox* EditableTextBox_buy_orderPrice;  // 주문가격

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UEditableTextBox* EditableTextBox_buy_orderAmount;  // 주문수량

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class USlider* Slider_buy_orderAmount;  // 주문수량

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* TextBlock_buy_orderAmount_rate;  // 주문수량비율

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UEditableTextBox* EditableTextBox_buy_sum;  // 주문금액

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UButton* Button_buy_button;  // 매수

protected:
	virtual void NativeConstruct() override;

	void SetTextBlockBuyOrderPossible(float set_order_possible);
	void SetTextBlockBuyOrderAmount(float set_order_amount);

	UFUNCTION(BlueprintCallable)
	void OnBuyButtonClick();

};
