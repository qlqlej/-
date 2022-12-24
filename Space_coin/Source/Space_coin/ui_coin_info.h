#pragma once

#include "game_info.h"
#include "Blueprint/UserWidget.h"
#include "ui_coin_info.generated.h"

UCLASS()
class SPACE_COIN_API Uui_coin_info : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* coin_name;  // �̸�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* coin_price;  // �ü�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* coin_units_traded_24H;  // �ŷ���(24H)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* coin_acc_trade_value_24H;  // �ŷ��ݾ�(24H)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* coin_max_price;  // ��(����)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* coin_min_price;  // ����(����)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* coin_fluctate_rate_24H;  // ������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* coin_prev_closing_price;  // ��������

protected:
	virtual void NativeConstruct() override;  // ������

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	void SetCoinName(const FString& name);
	void SetCoinPrice(int32 price);
	void SetCoinUnitsTraded24H(float amount);
	void SetCoinAccTradeValue24H(float value);
	void SetCoinMaxPrice(int32 price);
	void SetCoinMinPrice(int32 price);
	void SetCoinFluctateRate24H(int32 volatility);
	void SetCoinPrevClosingPrice(float price);

	void SetCoinInfoData(class Udata_coin_info* data);
};
