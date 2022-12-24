#include "ui_coin_price.h"
#include "Components/TextBlock.h"
#include "data_coin_price.h"
#include "data_coin_info.h"

// ������
void Uui_coin_price::NativeConstruct() 
{
	Super::NativeConstruct();

	coin_name = Cast<UTextBlock>(GetWidgetFromName(TEXT("coin_name")));  // �����
	coin_price = Cast<UTextBlock>(GetWidgetFromName(TEXT("coin_price")));  // �ü�
	coin_fluctate_24H = Cast<UTextBlock>(GetWidgetFromName(TEXT("coin_fluctate_24H")));  // �����ݾ�
	coin_fluctate_rate_24H = Cast<UTextBlock>(GetWidgetFromName(TEXT("coin_fluctate_rate_24H")));  // ������
	coin_acc_trade_value_24H = Cast<UTextBlock>(GetWidgetFromName(TEXT("coin_acc_trade_value_24H"))); // �ŷ� �ݾ�

	coin_price->SetVisibility(ESlateVisibility::Hidden);
	coin_fluctate_24H->SetVisibility(ESlateVisibility::Hidden);
	coin_fluctate_rate_24H->SetVisibility(ESlateVisibility::Hidden);
	coin_acc_trade_value_24H->SetVisibility(ESlateVisibility::Hidden);
}

void Uui_coin_price::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

// ������ UI ������ ȣ��
void Uui_coin_price::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	data = Cast<Udata_coin_price>(ListItemObject);
	SetData(data);
}

// ������ ���ý� ȣ��
void Uui_coin_price::NativeOnItemSelectionChanged(bool blsSelected)
{
	
}

void Uui_coin_price::SetCoinName(const FString& name)
{
	coin_name->SetText(FText::FromString(name));

}

void Uui_coin_price::SetCoinPrice(int32 price)
{
	FString strText;
	strText = FString::Printf(TEXT("%d"), price);

	coin_price->SetText(FText::FromString(strText));
}

void Uui_coin_price::SetCoinFluctate24H(int32 price)
{
	FString strText;
	strText = FString::Printf(TEXT("%d"), price);

	coin_fluctate_24H->SetText(FText::FromString(strText));
}

void Uui_coin_price::SetCoinFluctateRate24H(float rate)
{
	FString strText;
	strText = FString::Printf(TEXT("%.2f"), rate);
	
	coin_fluctate_rate_24H->SetText(FText::FromString(strText));
}

void Uui_coin_price::SetCoinAccTradeValue24H(float value)
{
	FString strText;
	strText = FString::Printf(TEXT("%.0f"), value);

	coin_acc_trade_value_24H->SetText(FText::FromString(strText));
}

void Uui_coin_price::SetData(class Udata_coin_price* d)
{
	SetCoinName(d->GetCoinName());
	SetCoinPrice(d->GetCoinPrice());
	SetCoinFluctate24H(d->GetCoinFluctate24H());
	SetCoinFluctateRate24H(d->GetCoinFluctateRate24H());
	SetCoinAccTradeValue24H(d->GetCoinAccTradeValue24H());

}
