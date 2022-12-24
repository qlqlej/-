#include "ui_coin_trading_buy.h"
#include "Components/CheckBox.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "Components/Slider.h"
#include "Components/Button.h"
#include "MainGamePlayerController.h"
#include "game_instance.h"

void Uui_coin_trading_buy::NativeConstruct()
{
	Super::NativeConstruct();

	CheckBox_buy_limits = Cast<UCheckBox>(GetWidgetFromName(TEXT("CheckBox_buy_limits")));  // 지정가
	CheckBox_buy_marketPrice = Cast<UCheckBox>(GetWidgetFromName(TEXT("CheckBox_buy_marketPrice")));  // 시장가
	CheckBox_buy_auto = Cast<UCheckBox>(GetWidgetFromName(TEXT("CheckBox_buy_auto")));  // 자동

	TextBlock_buy_orderPossible = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_buy_orderPossible"))); // 주문가능금액

	EditableTextBox_buy_orderPrice = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("EditableTextBox_buy_orderPrice")));  // 주문가격

	EditableTextBox_buy_orderAmount = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("EditableTextBox_buy_orderAmount")));  // 주문수량
	Slider_buy_orderAmount = Cast<USlider>(GetWidgetFromName(TEXT("Slider_buy_orderAmount")));  // 주문수량
	TextBlock_buy_orderAmount_rate = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_buy_orderAmount_rate")));  // 주문수량비율

	EditableTextBox_buy_sum = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("EditableTextBox_buy_sum")));  // 주문금액

	Button_buy_button = Cast<UButton>(GetWidgetFromName(TEXT("Button_buy_button")));  // 매수

	Button_buy_button->OnClicked.AddDynamic(this, &Uui_coin_trading_buy::OnBuyButtonClick);  // 매수 버튼
}

void Uui_coin_trading_buy::SetTextBlockBuyOrderPossible(float set_order_possible)  // 주문가능금액
{
	FString strText;
	strText = FString::Printf(TEXT("%d"), set_order_possible);

	TextBlock_buy_orderPossible->SetText(FText::FromString(strText));
}

void Uui_coin_trading_buy::SetTextBlockBuyOrderAmount(float set_order_amount)  // 주문수량비율
{
	FString strText;
	strText = FString::Printf(TEXT("%d"), set_order_amount);

	TextBlock_buy_orderAmount_rate->SetText(FText::FromString(strText));
}

void Uui_coin_trading_buy::OnBuyButtonClick()
{
	Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));

	CS_BUY_SELL_PACKET coin_buy_sell_packet;

	AMyCharacter* player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	coin_buy_sell_packet.sessionID = player->mySessionID;
	coin_buy_sell_packet.size = sizeof(CS_BUY_SELL_PACKET);
	coin_buy_sell_packet.type = CS_BUY_SELL;
	coin_buy_sell_packet.buy_sell_type = BUY_SELL::BUY;
	coin_buy_sell_packet.price;
	coin_buy_sell_packet.count;

	GameInstanceRef->client->SendToCoinBuySell(coin_buy_sell_packet);
}
