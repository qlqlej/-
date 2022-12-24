#include "ui_coin_info.h"
#include "Components/TextBlock.h"
#include "data_coin_info.h"
#include "data_coin_price.h"

void Uui_coin_info::NativeConstruct()
{
	Super::NativeConstruct();

	coin_name = Cast<UTextBlock>(GetWidgetFromName(TEXT("coin_name")));  // �����
	coin_price = Cast<UTextBlock>(GetWidgetFromName(TEXT("coin_price")));  // �ü�
	coin_units_traded_24H = Cast<UTextBlock>(GetWidgetFromName(TEXT("coin_units_traded_24H")));  // �ŷ���(24H)
	coin_acc_trade_value_24H = Cast<UTextBlock>(GetWidgetFromName(TEXT("coin_acc_trade_value_24H"))); //�ŷ��ݾ�(24H)
	coin_max_price = Cast<UTextBlock>(GetWidgetFromName(TEXT("coin_max_price")));  // ��(����)
	coin_min_price = Cast<UTextBlock>(GetWidgetFromName(TEXT("coin_min_price")));  // ����(����)
	coin_fluctate_rate_24H = Cast<UTextBlock>(GetWidgetFromName(TEXT("coin_fluctate_rate_24H")));  // ������
	coin_prev_closing_price = Cast<UTextBlock>(GetWidgetFromName(TEXT("coin_prev_closing_price"))); // ��������
}

void Uui_coin_info::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void Uui_coin_info::SetCoinName(const FString& name)
{
	coin_name->SetText(FText::FromString(name));
}

void Uui_coin_info::SetCoinPrice(int32 price)
{
	FString strText;
	strText = FString::Printf(TEXT("%d"), price);

	coin_price->SetText(FText::FromString(strText));
}

void Uui_coin_info::SetCoinUnitsTraded24H(float amount)
{
	FString strText;
	strText = FString::Printf(TEXT("%.2f"), amount);

	coin_units_traded_24H->SetText(FText::FromString(strText));
}

void Uui_coin_info::SetCoinAccTradeValue24H(float value)
{
	FString strText;
	strText = FString::Printf(TEXT("%.2f"), value);

	coin_acc_trade_value_24H->SetText(FText::FromString(strText));
}

void Uui_coin_info::SetCoinMaxPrice(int32 price)
{
	FString strText;
	strText = FString::Printf(TEXT("%d"), price);

	coin_max_price->SetText(FText::FromString(strText));
}

void Uui_coin_info::SetCoinMinPrice(int32 price)
{
	FString strText;
	strText = FString::Printf(TEXT("%d"), price);

	coin_min_price->SetText(FText::FromString(strText));
}

void Uui_coin_info::SetCoinFluctateRate24H(int32 volatility)
{
	FString strText;
	strText = FString::Printf(TEXT("%d"), volatility);

	coin_fluctate_rate_24H->SetText(FText::FromString(strText));
}

void Uui_coin_info::SetCoinPrevClosingPrice(float price)
{
	FString strText;
	strText = FString::Printf(TEXT("%.2f"), price);

	coin_prev_closing_price->SetText(FText::FromString(strText));
}

void Uui_coin_info::SetCoinInfoData(class Udata_coin_info* data)
{
	SetCoinName(data->GetCoinName());
	SetCoinPrice(data->GetCoinPrice());
	SetCoinUnitsTraded24H(data->GetCoinUnitsTraded24H());
	SetCoinAccTradeValue24H(data->GetCoinAccTradeValue24H());
	SetCoinMaxPrice(data->GetCoinMaxPrice());
	SetCoinMinPrice(data->GetCoinMinPrice());
	SetCoinFluctateRate24H(data->GetCoinFluctateRate24H());
	SetCoinPrevClosingPrice(data->GetCoinPrevClosingPrice());
}