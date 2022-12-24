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
	class UCheckBox* CheckBox_sell_limits;  // ������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UCheckBox* CheckBox_sell_marketPrice;  // ���尡

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UCheckBox* CheckBox_sell_auto;  // �ڵ�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* TextBlock_sell_orderPossible;  // �ֹ����ɱݾ�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UEditableTextBox* EditableTextBox_sell_orderPrice;  // �ֹ�����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UEditableTextBox* EditableTextBox_sell_orderAmount;  // �ֹ�����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class USlider* Slider_sell_orderAmount;  // �ֹ�����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* TextBlock_sell_orderAmount_rate;  // �ֹ���������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UEditableTextBox* EditableTextBox_sell_sum;  // �ֹ��ݾ�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UButton* Button_sell_button;  // �ż�

protected:
	virtual void NativeConstruct() override;
	
	void OnCheckBoxClick();
	void SetTextBlockSellOrderPossible(float set_order_possible);
	void SetTextBlockSellOrderAmount(float set_order_amount);

	UFUNCTION(BlueprintCallable)
	void OnSellButtonClick();

};
