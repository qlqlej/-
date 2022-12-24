#include "ui_coin_trading_sell.h"
#include "Components/CheckBox.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "Components/Slider.h"
#include "Components/Button.h"
#include "MainGamePlayerController.h"
#include "game_instance.h"

void Uui_coin_trading_sell::NativeConstruct()
{
	Super::NativeConstruct();

	CheckBox_sell_limits = Cast<UCheckBox>(GetWidgetFromName(TEXT("CheckBox_sell_limits")));  // 지정가
	CheckBox_sell_marketPrice = Cast<UCheckBox>(GetWidgetFromName(TEXT("CheckBox_sell_marketPrice")));  // 시장가
	CheckBox_sell_auto = Cast<UCheckBox>(GetWidgetFromName(TEXT("CheckBox_sell_auto")));  // 자동

	TextBlock_sell_orderPossible = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_sell_orderPossible"))); // 주문가능금액

	EditableTextBox_sell_orderPrice = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("EditableTextBox_sell_orderPrice")));  // 주문가격

	EditableTextBox_sell_orderAmount = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("EditableTextBox_sell_orderAmount")));  // 주문수량
	Slider_sell_orderAmount = Cast<USlider>(GetWidgetFromName(TEXT("Slider_sell_orderAmount")));  // 주문수량
	TextBlock_sell_orderAmount_rate = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_sell_orderAmount_rate")));  // 주문수량비율

	EditableTextBox_sell_sum = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("EditableTextBox_sell_sum")));  // 주문금액

	Button_sell_button = Cast<UButton>(GetWidgetFromName(TEXT("Button_sell_button")));  // 매도

	
	 
	Button_sell_button->OnClicked.AddDynamic(this, &Uui_coin_trading_sell::OnSellButtonClick);  // 매도 버튼

}

void Uui_coin_trading_sell::SetTextBlockSellOrderPossible(float set_order_possible)  // 주문가능금액
{
	FString strText;
	strText = FString::Printf(TEXT("%d"), set_order_possible);

	TextBlock_sell_orderPossible->SetText(FText::FromString(strText));
}

void Uui_coin_trading_sell::SetTextBlockSellOrderAmount(float set_order_amount)  // 주문수량비율
{
	FString strText;
	strText = FString::Printf(TEXT("%d"), set_order_amount);

	TextBlock_sell_orderAmount_rate->SetText(FText::FromString(strText));
}

void Uui_coin_trading_sell::OnCheckBoxClick()
{

}

void Uui_coin_trading_sell::OnSellButtonClick()  // 매도 버튼 클릭
{
	Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));

	CS_BUY_SELL_PACKET coin_buy_sell_packet;

	AMyCharacter* player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	coin_buy_sell_packet.sessionID = player->mySessionID;
	coin_buy_sell_packet.size = sizeof(CS_BUY_SELL_PACKET);
	coin_buy_sell_packet.type = CS_BUY_SELL;
	coin_buy_sell_packet.buy_sell_type = BUY_SELL::SELL;
	coin_buy_sell_packet.price;
	coin_buy_sell_packet.count;

	GameInstanceRef->client->SendToCoinBuySell(coin_buy_sell_packet);
}
