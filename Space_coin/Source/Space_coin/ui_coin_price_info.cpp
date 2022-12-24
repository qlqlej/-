#include "ui_coin_price_info.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "data_coin_price.h"
#include "ui_coin_info.h"
#include "data_coin_info.h"
#include "ui_coin_price.h"
#include "MainGamePlayerController.h"

void Uui_coin_price_info::NativeConstruct()
{
	Super::NativeConstruct();

	coin_price_wb_1 = Cast<Uui_coin_price>(GetWidgetFromName(TEXT("coin_price_wb_1")));
	coin_price_wb_2 = Cast<Uui_coin_price>(GetWidgetFromName(TEXT("coin_price_wb_2")));
	coin_price_wb_3 = Cast<Uui_coin_price>(GetWidgetFromName(TEXT("coin_price_wb_3")));

	coin_price_wb_1_button = Cast<UButton>(GetWidgetFromName(TEXT("coin_price_wb_1_button")));
	coin_price_wb_2_button = Cast<UButton>(GetWidgetFromName(TEXT("coin_price_wb_2_button")));
	coin_price_wb_3_button = Cast<UButton>(GetWidgetFromName(TEXT("coin_price_wb_3_button")));

	coin_name = Cast<UTextBlock>(GetWidgetFromName(TEXT("coin_name")));  // 종목명
	coin_price = Cast<UTextBlock>(GetWidgetFromName(TEXT("coin_price")));  // 시세
	coin_units_traded_24H = Cast<UTextBlock>(GetWidgetFromName(TEXT("coin_units_traded_24H")));  // 거래량(24H)
	coin_acc_trade_value_24H = Cast<UTextBlock>(GetWidgetFromName(TEXT("coin_acc_trade_value_24H"))); //거래금액(24H)
	coin_max_price = Cast<UTextBlock>(GetWidgetFromName(TEXT("coin_max_price")));  // 고가(당일)
	coin_min_price = Cast<UTextBlock>(GetWidgetFromName(TEXT("coin_min_price")));  // 저가(당일)
	coin_fluctate_rate_24H = Cast<UTextBlock>(GetWidgetFromName(TEXT("coin_fluctate_rate_24H")));  // 변동률
	coin_prev_closing_price = Cast<UTextBlock>(GetWidgetFromName(TEXT("coin_prev_closing_price"))); // 전일종가

	coin_price_wb_1_button->OnClicked.AddDynamic(this, &Uui_coin_price_info::OnCoin1ButtonClick);
	coin_price_wb_2_button->OnClicked.AddDynamic(this, &Uui_coin_price_info::OnCoin2ButtonClick);
	coin_price_wb_3_button->OnClicked.AddDynamic(this, &Uui_coin_price_info::OnCoin3ButtonClick);

	pc = Cast<AMainGamePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	InitList();
}

void Uui_coin_price_info::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void Uui_coin_price_info::InitList()
{
	/* a coin */
	a_data = NewObject<Udata_coin_price>(this, Udata_coin_price::StaticClass());

	a_data->SetCoinName(pc->a_coin.coin_name);  // 자산
	a_data->SetCoinPrice(pc->a_coin.closing_price);  // 현재가
	a_data->SetCoinFluctate24H(pc->a_coin.fluctate_24H);  // 변동금액(24h)
	a_data->SetCoinFluctateRate24H(pc->a_coin.fluctate_rate_24H);  // 변동률(24h)
	a_data->SetCoinAccTradeValue24H(pc->a_coin.acc_trade_value_24H);  // 거래금액(24h)

	a_data->SetCoinUnitsTraded24H(pc->a_coin.units_traded_24H);  // 거래량(24h)
	a_data->SetCoinMaxPrice(pc->a_coin.max_price);  // 고가(당일)
	a_data->SetCoinMinPrice(pc->a_coin.min_price);  // 저가(당일)
	a_data->SetCoinPrevClosingPrice(pc->a_coin.prev_closing_price);  // 전일종가

	coin_price_wb_1->SetData(a_data);

	/* b coin */
	b_data = NewObject<Udata_coin_price>(this, Udata_coin_price::StaticClass());

	b_data->SetCoinName(pc->b_coin.coin_name);  // 자산
	b_data->SetCoinPrice(pc->b_coin.closing_price);  // 현재가
	b_data->SetCoinFluctate24H(pc->b_coin.fluctate_24H);  // 변동금액(24h)
	b_data->SetCoinFluctateRate24H(pc->b_coin.fluctate_rate_24H);  // 변동률(24h)
	b_data->SetCoinAccTradeValue24H(pc->b_coin.acc_trade_value_24H);  // 거래금액(24h)

	b_data->SetCoinUnitsTraded24H(pc->b_coin.units_traded_24H);  // 거래량(24h)
	b_data->SetCoinMaxPrice(pc->b_coin.max_price);  // 고가(당일)
	b_data->SetCoinMinPrice(pc->b_coin.min_price);  // 저가(당일)
	b_data->SetCoinPrevClosingPrice(pc->b_coin.prev_closing_price);  // 전일종가

	coin_price_wb_2->SetData(b_data);

	/* c coin */
	c_data = NewObject<Udata_coin_price>(this, Udata_coin_price::StaticClass());

	c_data->SetCoinName(pc->c_coin.coin_name);  // 자산
	c_data->SetCoinPrice(pc->c_coin.closing_price);  // 현재가
	c_data->SetCoinFluctate24H(pc->c_coin.fluctate_24H);  // 변동금액(24h)
	c_data->SetCoinFluctateRate24H(pc->c_coin.fluctate_rate_24H);  // 변동률(24h)
	c_data->SetCoinAccTradeValue24H(pc->c_coin.acc_trade_value_24H);  // 거래금액(24h)

	c_data->SetCoinUnitsTraded24H(pc->c_coin.units_traded_24H);  // 거래량(24h)
	c_data->SetCoinMaxPrice(pc->c_coin.max_price);  // 고가(당일)
	c_data->SetCoinMinPrice(pc->c_coin.min_price);  // 저가(당일)
	c_data->SetCoinPrevClosingPrice(pc->c_coin.prev_closing_price);  // 전일종가

	coin_price_wb_3->SetData(c_data);
}

void Uui_coin_price_info::OnCoin1ButtonClick()
{
	SetCoinName(a_data->GetCoinName());
	SetCoinPrice(a_data->GetCoinPrice());
	SetCoinUnitsTraded24H(a_data->GetCoinUnitsTraded24H());
	SetCoinAccTradeValue24H(a_data->GetCoinAccTradeValue24H());
	SetCoinMaxPrice(a_data->GetCoinMaxPrice());
	SetCoinMinPrice(a_data->GetCoinMinPrice());
	SetCoinFluctateRate24H(a_data->GetCoinFluctateRate24H());
	SetCoinPrevClosingPrice(a_data->GetCoinPrevClosingPrice());

}

void Uui_coin_price_info::OnCoin2ButtonClick()
{

}

void Uui_coin_price_info::OnCoin3ButtonClick()
{

}

void Uui_coin_price_info::SetCoinName(const FString& name)
{
	coin_name->SetText(FText::FromString(name));
}

void Uui_coin_price_info::SetCoinPrice(int32 price)
{
	FString strText;
	strText = FString::Printf(TEXT("%d"), price);

	coin_price->SetText(FText::FromString(strText));
}

void Uui_coin_price_info::SetCoinUnitsTraded24H(float amount)
{
	FString strText;
	strText = FString::Printf(TEXT("%.2f"), amount);

	coin_units_traded_24H->SetText(FText::FromString(strText));
}

void Uui_coin_price_info::SetCoinAccTradeValue24H(float value)
{
	FString strText;
	strText = FString::Printf(TEXT("%.0f"), value);  // 정수로

	coin_acc_trade_value_24H->SetText(FText::FromString(strText));
}

void Uui_coin_price_info::SetCoinMaxPrice(int32 price)
{
	FString strText;
	strText = FString::Printf(TEXT("%d"), price);

	coin_max_price->SetText(FText::FromString(strText));
}

void Uui_coin_price_info::SetCoinMinPrice(int32 price)
{
	FString strText;
	strText = FString::Printf(TEXT("%d"), price);

	coin_min_price->SetText(FText::FromString(strText));
}

void Uui_coin_price_info::SetCoinFluctateRate24H(float rate)
{
	FString strText;
	strText = FString::Printf(TEXT("%.2f"), rate);

	coin_fluctate_rate_24H->SetText(FText::FromString(strText));
}

void Uui_coin_price_info::SetCoinPrevClosingPrice(float price)
{
	FString strText;
	strText = FString::Printf(TEXT("%.0f"), price);  // 정수로

	coin_prev_closing_price->SetText(FText::FromString(strText));
}