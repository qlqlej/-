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

	CheckBox_buy_limits = Cast<UCheckBox>(GetWidgetFromName(TEXT("CheckBox_buy_limits")));  // ������
	CheckBox_buy_marketPrice = Cast<UCheckBox>(GetWidgetFromName(TEXT("CheckBox_buy_marketPrice")));  // ���尡
	CheckBox_buy_auto = Cast<UCheckBox>(GetWidgetFromName(TEXT("CheckBox_buy_auto")));  // �ڵ�

	TextBlock_buy_orderPossible = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_buy_orderPossible"))); // �ֹ����ɱݾ�

	EditableTextBox_buy_orderPrice = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("EditableTextBox_buy_orderPrice")));  // �ֹ�����

	EditableTextBox_buy_orderAmount = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("EditableTextBox_buy_orderAmount")));  // �ֹ�����
	Slider_buy_orderAmount = Cast<USlider>(GetWidgetFromName(TEXT("Slider_buy_orderAmount")));  // �ֹ�����
	TextBlock_buy_orderAmount_rate = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_buy_orderAmount_rate")));  // �ֹ���������

	EditableTextBox_buy_sum = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("EditableTextBox_buy_sum")));  // �ֹ��ݾ�

	Button_buy_button = Cast<UButton>(GetWidgetFromName(TEXT("Button_buy_button")));  // �ż�

	Button_buy_button->OnClicked.AddDynamic(this, &Uui_coin_trading_buy::OnBuyButtonClick);  // �ż� ��ư
}

void Uui_coin_trading_buy::SetTextBlockBuyOrderPossible(float set_order_possible)  // �ֹ����ɱݾ�
{
	FString strText;
	strText = FString::Printf(TEXT("%d"), set_order_possible);

	TextBlock_buy_orderPossible->SetText(FText::FromString(strText));
}

void Uui_coin_trading_buy::SetTextBlockBuyOrderAmount(float set_order_amount)  // �ֹ���������
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
