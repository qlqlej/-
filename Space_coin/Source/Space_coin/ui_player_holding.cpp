#include "ui_player_holding.h"
#include "Components/TextBlock.h"
#include "data_player_holding_coin.h"

// 생성자
void Uui_player_holding::NativeConstruct()
{
	Super::NativeConstruct();

	coin_name = Cast<UTextBlock>(GetWidgetFromName(TEXT("coin_name")));  // 종목명
	purchase_price = Cast<UTextBlock>(GetWidgetFromName(TEXT("purchase_price")));  // 시세
	aluation_profitand_loss = Cast<UTextBlock>(GetWidgetFromName(TEXT("aluation_profitand_loss")));  // 변동률
	coin_rate = Cast<UTextBlock>(GetWidgetFromName(TEXT("coin_rate"))); // 거래 금액
	amount = Cast<UTextBlock>(GetWidgetFromName(TEXT("amount")));  // 종목명
	coin_price = Cast<UTextBlock>(GetWidgetFromName(TEXT("coin_price")));  // 시세
	purchase_amount = Cast<UTextBlock>(GetWidgetFromName(TEXT("purchase_amount")));  // 변동률
	evaluated_price = Cast<UTextBlock>(GetWidgetFromName(TEXT("evaluated_price"))); // 거래 금액
}

void Uui_player_holding::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

// 아이템 UI 설정시 호출
void Uui_player_holding::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	class Udata_player_holding_coin* data = Cast<Udata_player_holding_coin>(ListItemObject);
	SetData(data);
}

// 아이템 선택시 호출
void Uui_player_holding::NativeOnItemSelectionChanged(bool blsSelected)
{

}

void Uui_player_holding::SetCoinName(const FString& name)
{
	coin_name->SetText(FText::FromString(name));
}

void Uui_player_holding::SetPurchasePrice(int32 price)
{
	FString strText;
	strText = FString::Printf(TEXT("%d"), price);

	purchase_price->SetText(FText::FromString(strText));
}

void Uui_player_holding::SetAluationProfitandLoss(float profitand_loss)
{
	FString strText;
	strText = FString::Printf(TEXT("%.2f"), profitand_loss);

	aluation_profitand_loss->SetText(FText::FromString(strText));
}

void Uui_player_holding::SetCoinRate(float rate)
{
	FString strText;
	strText = FString::Printf(TEXT("%.2f"), rate);

	coin_rate->SetText(FText::FromString(strText));
}

void Uui_player_holding::SetAmount(int32 amt)
{
	FString strText;
	strText = FString::Printf(TEXT("%d"), amt);

	amount->SetText(FText::FromString(strText));
}

void Uui_player_holding::SetCoinPrice(int32 price)
{
	FString strText;
	strText = FString::Printf(TEXT("%d"), price);

	coin_price->SetText(FText::FromString(strText));
}

void Uui_player_holding::SetPurchaseAmount(int32 amt)
{
	FString strText;
	strText = FString::Printf(TEXT("%d"), amt);

	purchase_amount->SetText(FText::FromString(strText));
}

void Uui_player_holding::SetEvaluatedPrice(int32 price)
{
	FString strText;
	strText = FString::Printf(TEXT("%d"), price);

	evaluated_price->SetText(FText::FromString(strText));
}

void Uui_player_holding::SetData(class Udata_player_holding_coin* data)
{
	SetCoinName(data->GetCoinName());
	SetPurchasePrice(data->GetPurchasePrice());
	SetAluationProfitandLoss(data->GetAluationProfitandLoss());
	SetCoinRate(data->GetCoinRate());
	SetAmount(data->GetAmount());
	SetCoinPrice(data->GetCoinPrice());
	SetPurchaseAmount(data->GetPurchaseAmount());
	SetEvaluatedPrice(data->GetEvaluatedPrice());
}
