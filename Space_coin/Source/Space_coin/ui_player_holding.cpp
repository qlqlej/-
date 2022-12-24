#include "ui_player_holding.h"
#include "Components/TextBlock.h"
#include "data_player_holding_coin.h"

// ������
void Uui_player_holding::NativeConstruct()
{
	Super::NativeConstruct();

	coin_name = Cast<UTextBlock>(GetWidgetFromName(TEXT("coin_name")));  // �����
	purchase_price = Cast<UTextBlock>(GetWidgetFromName(TEXT("purchase_price")));  // �ü�
	aluation_profitand_loss = Cast<UTextBlock>(GetWidgetFromName(TEXT("aluation_profitand_loss")));  // ������
	coin_rate = Cast<UTextBlock>(GetWidgetFromName(TEXT("coin_rate"))); // �ŷ� �ݾ�
	amount = Cast<UTextBlock>(GetWidgetFromName(TEXT("amount")));  // �����
	coin_price = Cast<UTextBlock>(GetWidgetFromName(TEXT("coin_price")));  // �ü�
	purchase_amount = Cast<UTextBlock>(GetWidgetFromName(TEXT("purchase_amount")));  // ������
	evaluated_price = Cast<UTextBlock>(GetWidgetFromName(TEXT("evaluated_price"))); // �ŷ� �ݾ�
}

void Uui_player_holding::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

// ������ UI ������ ȣ��
void Uui_player_holding::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	class Udata_player_holding_coin* data = Cast<Udata_player_holding_coin>(ListItemObject);
	SetData(data);
}

// ������ ���ý� ȣ��
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
