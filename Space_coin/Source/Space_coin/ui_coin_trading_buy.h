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
	class UCheckBox* CheckBox_buy_limits;  // ������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UCheckBox* CheckBox_buy_marketPrice;  // ���尡

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UCheckBox* CheckBox_buy_auto;  // �ڵ�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* TextBlock_buy_orderPossible;  // �ֹ����ɱݾ�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UEditableTextBox* EditableTextBox_buy_orderPrice;  // �ֹ�����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UEditableTextBox* EditableTextBox_buy_orderAmount;  // �ֹ�����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class USlider* Slider_buy_orderAmount;  // �ֹ�����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* TextBlock_buy_orderAmount_rate;  // �ֹ���������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UEditableTextBox* EditableTextBox_buy_sum;  // �ֹ��ݾ�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UButton* Button_buy_button;  // �ż�

protected:
	virtual void NativeConstruct() override;

	void SetTextBlockBuyOrderPossible(float set_order_possible);
	void SetTextBlockBuyOrderAmount(float set_order_amount);

	UFUNCTION(BlueprintCallable)
	void OnBuyButtonClick();

};
