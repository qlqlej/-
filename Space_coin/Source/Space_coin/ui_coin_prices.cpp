#include "ui_coin_prices.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "data_coin_price.h"
#include "ui_coin_info.h"
#include "data_coin_info.h"
#include "ui_coin_price.h"
#include "ui_coin_fail_or_success.h"
#include "ui_coin_map_loading.h"
#include "MainGamePlayerController.h"
#include "game_instance.h"

void Uui_coin_prices::NativeConstruct()
{
	Super::NativeConstruct();

	coin_price_list_view = Cast<UListView>(GetWidgetFromName(TEXT("coin_price_list_view")));

	coin_name = Cast<UTextBlock>(GetWidgetFromName(TEXT("coin_name")));  // 종목명
	coin_price = Cast<UTextBlock>(GetWidgetFromName(TEXT("coin_price")));  // 시세
	coin_units_traded_24H = Cast<UTextBlock>(GetWidgetFromName(TEXT("coin_units_traded_24H")));  // 거래량(24H)
	coin_acc_trade_value_24H = Cast<UTextBlock>(GetWidgetFromName(TEXT("coin_acc_trade_value_24H"))); //거래금액(24H)
	coin_max_price = Cast<UTextBlock>(GetWidgetFromName(TEXT("coin_max_price")));  // 고가(당일)
	coin_min_price = Cast<UTextBlock>(GetWidgetFromName(TEXT("coin_min_price")));  // 저가(당일)
	coin_fluctate_rate_24H = Cast<UTextBlock>(GetWidgetFromName(TEXT("coin_fluctate_rate_24H")));  // 변동률
	coin_prev_closing_price = Cast<UTextBlock>(GetWidgetFromName(TEXT("coin_prev_closing_price"))); // 전일종가

	EditableTextBox_buy_orderPrice = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("EditableTextBox_buy_orderPrice")));  // 주문가격
	EditableTextBox_buy_orderAmount = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("EditableTextBox_buy_orderAmount")));  // 주문수량
	TextBox_buy_sum = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBox_buy_sum")));  // 주문수량비율
	Button_buy_button = Cast<UButton>(GetWidgetFromName(TEXT("Button_buy_button")));  // 매수

	EditableTextBox_sell_orderPrice = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("EditableTextBox_sell_orderPrice")));  // 주문가격
	EditableTextBox_sell_orderAmount = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("EditableTextBox_sell_orderAmount")));  // 주문수량
	TextBox_sell_sum = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBox_sell_sum")));  // 주문수량비율
	Button_sell_button = Cast<UButton>(GetWidgetFromName(TEXT("Button_sell_button")));  // 매도

	coin_fail_or_success_wb = Cast<Uui_coin_fail_or_success>(GetWidgetFromName(TEXT("coin_fail_or_success_wb")));
	coin_fail_or_success_wb->SetVisibility(ESlateVisibility::Hidden);

	coin_map_loading_wb = Cast<Uui_coin_map_loading>(GetWidgetFromName(TEXT("coin_map_loading_wb")));
	coin_map_loading_wb->SetVisibility(ESlateVisibility::Hidden);

	coin_price_list_view->OnItemClicked().AddUObject(this, &Uui_coin_prices::ItemClick);

	EditableTextBox_buy_orderPrice->OnTextCommitted.AddDynamic(this, &Uui_coin_prices::OnBuyOrderPriceChange);
	EditableTextBox_buy_orderAmount->OnTextCommitted.AddDynamic(this, &Uui_coin_prices::OnBuyOrderAmountChange);
	
	EditableTextBox_sell_orderPrice->OnTextCommitted.AddDynamic(this, &Uui_coin_prices::OnSellOrderPriceChange);
	EditableTextBox_sell_orderAmount->OnTextCommitted.AddDynamic(this, &Uui_coin_prices::OnSellOrderAmountChange);

	Button_buy_button->SetIsEnabled(false);
	Button_sell_button->SetIsEnabled(false);

	Button_buy_button->OnClicked.AddDynamic(this, &Uui_coin_prices::OnBuyButtonClick);
	Button_sell_button->OnClicked.AddDynamic(this, &Uui_coin_prices::OnSellButtonClick);

	pc = Cast<AMainGamePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	InitList();

	set_data_count = 0;
}

void Uui_coin_prices::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void Uui_coin_prices::InitList()
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

	a_data->SetCoinType(1);

	coin_price_list_view->AddItem(a_data);

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

	b_data->SetCoinType(2);

	coin_price_list_view->AddItem(b_data);

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

	c_data->SetCoinType(3);

	coin_price_list_view->AddItem(c_data);
}

void Uui_coin_prices::SetData()
{
	if (pc->a_coin.coin_name.IsEmpty() == false) { 
		set_data_count++;
	}

	if (pc->a_coin.coin_name.IsEmpty() == true || set_data_count < 200) {
		coin_price_list_view->ClearListItems();
		InitList();
	}

	if(pc->a_coin.coin_name.IsEmpty() == false && set_data_count >= 200) {
		coin_map_loading_wb->SetVisibility(ESlateVisibility::Hidden);

		Udata_coin_price* set_a_data = Cast<Udata_coin_price>(coin_price_list_view->GetItemAt(0));

		set_a_data->SetCoinName(pc->a_coin.coin_name);  // 자산
		set_a_data->SetCoinPrice(pc->a_coin.closing_price);  // 현재가
		set_a_data->SetCoinFluctate24H(pc->a_coin.fluctate_24H);  // 변동금액(24h)
		set_a_data->SetCoinFluctateRate24H(pc->a_coin.fluctate_rate_24H);  // 변동률(24h)
		set_a_data->SetCoinAccTradeValue24H(pc->a_coin.acc_trade_value_24H);  // 거래금액(24h)

		set_a_data->SetCoinUnitsTraded24H(pc->a_coin.units_traded_24H);  // 거래량(24h)
		set_a_data->SetCoinMaxPrice(pc->a_coin.max_price);  // 고가(당일)
		set_a_data->SetCoinMinPrice(pc->a_coin.min_price);  // 저가(당일)
		set_a_data->SetCoinPrevClosingPrice(pc->a_coin.prev_closing_price);  // 전일종가

		set_a_data->SetCoinType(1);

		Udata_coin_price* set_b_data = Cast<Udata_coin_price>(coin_price_list_view->GetItemAt(1));

		set_b_data->SetCoinName(pc->b_coin.coin_name);  // 자산
		set_b_data->SetCoinPrice(pc->b_coin.closing_price);  // 현재가
		set_b_data->SetCoinFluctate24H(pc->b_coin.fluctate_24H);  // 변동금액(24h)
		set_b_data->SetCoinFluctateRate24H(pc->b_coin.fluctate_rate_24H);  // 변동률(24h)
		set_b_data->SetCoinAccTradeValue24H(pc->b_coin.acc_trade_value_24H);  // 거래금액(24h)

		set_b_data->SetCoinUnitsTraded24H(pc->b_coin.units_traded_24H);  // 거래량(24h)
		set_b_data->SetCoinMaxPrice(pc->b_coin.max_price);  // 고가(당일)
		set_b_data->SetCoinMinPrice(pc->b_coin.min_price);  // 저가(당일)
		set_b_data->SetCoinPrevClosingPrice(pc->b_coin.prev_closing_price);  // 전일종가

		set_b_data->SetCoinType(2);

		Udata_coin_price* set_c_data = Cast<Udata_coin_price>(coin_price_list_view->GetItemAt(2));

		set_c_data->SetCoinName(pc->c_coin.coin_name);  // 자산
		set_c_data->SetCoinPrice(pc->c_coin.closing_price);  // 현재가
		set_c_data->SetCoinFluctate24H(pc->c_coin.fluctate_24H);  // 변동금액(24h)
		set_c_data->SetCoinFluctateRate24H(pc->c_coin.fluctate_rate_24H);  // 변동률(24h)
		set_c_data->SetCoinAccTradeValue24H(pc->c_coin.acc_trade_value_24H);  // 거래금액(24h)

		set_c_data->SetCoinUnitsTraded24H(pc->c_coin.units_traded_24H);  // 거래량(24h)
		set_c_data->SetCoinMaxPrice(pc->c_coin.max_price);  // 고가(당일)
		set_c_data->SetCoinMinPrice(pc->c_coin.min_price);  // 저가(당일)
		set_c_data->SetCoinPrevClosingPrice(pc->c_coin.prev_closing_price);  // 전일종가

		set_c_data->SetCoinType(3);

		if (IsValid(data)) {
			SetCoinName(data->GetCoinName());
			SetCoinPrice(data->GetCoinPrice());
			SetCoinUnitsTraded24H(data->GetCoinUnitsTraded24H());
			SetCoinAccTradeValue24H(data->GetCoinAccTradeValue24H());
			SetCoinMaxPrice(data->GetCoinMaxPrice());
			SetCoinMinPrice(data->GetCoinMinPrice());
			SetCoinFluctateRate24H(data->GetCoinFluctateRate24H());
			SetCoinPrevClosingPrice(data->GetCoinPrevClosingPrice());
		}
	}
	else {
		coin_map_loading_wb->SetVisibility(ESlateVisibility::Visible);
	}
}

void Uui_coin_prices::ItemClick(UObject* obj)
{
	data = Cast<Udata_coin_price>(obj);

	if (IsValid(data)) {
		SetCoinName(data->GetCoinName());
		SetCoinPrice(data->GetCoinPrice());
		SetCoinUnitsTraded24H(data->GetCoinUnitsTraded24H());
		SetCoinAccTradeValue24H(data->GetCoinAccTradeValue24H());
		SetCoinMaxPrice(data->GetCoinMaxPrice());
		SetCoinMinPrice(data->GetCoinMinPrice());
		SetCoinFluctateRate24H(data->GetCoinFluctateRate24H());
		SetCoinPrevClosingPrice(data->GetCoinPrevClosingPrice());

		coin_type = data->GetCoinType();

		click_coin_name = data->GetCoinName();
		click_coin_price = data->GetCoinPrice();

		EditableTextBox_buy_orderPrice->SetText(FText::FromString(FString::FromInt(click_coin_price)));
		EditableTextBox_sell_orderPrice->SetText(FText::FromString(FString::FromInt(click_coin_price)));
	}
}

void Uui_coin_prices::SetCoinName(const FString& name)
{
	coin_name->SetText(FText::FromString(name));
}

void Uui_coin_prices::SetCoinPrice(int32 price)
{
	FString strText;
	strText = FString::Printf(TEXT("%d"), price);

	coin_price->SetText(FText::FromString(strText));
}

void Uui_coin_prices::SetCoinUnitsTraded24H(float amount)
{
	FString strText;
	strText = FString::Printf(TEXT("%.2f"), amount);

	coin_units_traded_24H->SetText(FText::FromString(strText));
}

void Uui_coin_prices::SetCoinAccTradeValue24H(float value)
{
	FString strText;
	strText = FString::Printf(TEXT("%.0f"), value);  // 정수로

	coin_acc_trade_value_24H->SetText(FText::FromString(strText));
}

void Uui_coin_prices::SetCoinMaxPrice(int32 price)
{
	FString strText;
	strText = FString::Printf(TEXT("%d"), price);

	coin_max_price->SetText(FText::FromString(strText));
}

void Uui_coin_prices::SetCoinMinPrice(int32 price)
{
	FString strText;
	strText = FString::Printf(TEXT("%d"), price);

	coin_min_price->SetText(FText::FromString(strText));
}

void Uui_coin_prices::SetCoinFluctateRate24H(float rate)
{
	FString strText;
	strText = FString::Printf(TEXT("%.2f"), rate);

	coin_fluctate_rate_24H->SetText(FText::FromString(strText));
}

void Uui_coin_prices::SetCoinPrevClosingPrice(float price)
{
	FString strText;
	strText = FString::Printf(TEXT("%.0f"), price);  // 정수로

	coin_prev_closing_price->SetText(FText::FromString(strText));
}

void Uui_coin_prices::OnBuyOrderPriceChange(const FText& Text, ETextCommit::Type CommitMethod)
{
	buy_price = FCString::Atoi(*EditableTextBox_buy_orderPrice->GetText().ToString());
	buy_count = FCString::Atoi(*EditableTextBox_buy_orderAmount->GetText().ToString());
	TextBox_buy_sum->SetText(FText::FromString(FString::FromInt(buy_price * buy_count)));

	Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));

	switch (GameInstanceRef->mycharacter_type)
	{
	case CHARACTER_TYPE::HUMAN:
	{
		AMyCharacter* player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (player->money < buy_price * buy_count) {
			Button_buy_button->SetIsEnabled(false);
		}
		else {
			Button_buy_button->SetIsEnabled(true);
		}
		break;
	}
	case CHARACTER_TYPE::SPACESHIP:
	{
		Aspace_ship* ship = Cast<Aspace_ship>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (ship->owner_character->money < buy_price * buy_count) {
			Button_buy_button->SetIsEnabled(false);
		}
		else {
			Button_buy_button->SetIsEnabled(true);
		}
		break;
	}
	default:
		break;
	}
}

void Uui_coin_prices::OnBuyOrderAmountChange(const FText& Text, ETextCommit::Type CommitMethod)
{
	buy_price = FCString::Atoi(*EditableTextBox_buy_orderPrice->GetText().ToString());
	buy_count = FCString::Atoi(*EditableTextBox_buy_orderAmount->GetText().ToString());
	TextBox_buy_sum->SetText(FText::FromString(FString::FromInt(buy_price * buy_count)));

	Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));

	switch (GameInstanceRef->mycharacter_type)
	{
	case CHARACTER_TYPE::HUMAN:
	{
		AMyCharacter* player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (player->money < buy_price * buy_count) {
			Button_buy_button->SetIsEnabled(false);
		}
		else {
			Button_buy_button->SetIsEnabled(true);
		}
		break;
	}
	case CHARACTER_TYPE::SPACESHIP:
	{
		Aspace_ship* ship = Cast<Aspace_ship>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (ship->owner_character->money < buy_price * buy_count) {
			Button_buy_button->SetIsEnabled(false);
		}
		else {
			Button_buy_button->SetIsEnabled(true);
		}
		break;
	}
	default:
		break;
	}
}

void Uui_coin_prices::OnSellOrderPriceChange(const FText& Text, ETextCommit::Type CommitMethod)
{
	sell_price = FCString::Atoi(*EditableTextBox_sell_orderPrice->GetText().ToString());
	sell_count = FCString::Atoi(*EditableTextBox_sell_orderAmount->GetText().ToString());
	TextBox_sell_sum->SetText(FText::FromString(FString::FromInt(sell_price * sell_count)));

	Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
	int a_coin_count = 0, b_coin_count = 0, c_coin_count = 0;

	switch (GameInstanceRef->mycharacter_type)
	{
	case CHARACTER_TYPE::HUMAN:
	{
		AMyCharacter* player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		a_coin_count = player->a_coin;
		b_coin_count = player->b_coin;
		c_coin_count = player->c_coin;
		break;
	}
	case CHARACTER_TYPE::SPACESHIP:
	{
		Aspace_ship* ship = Cast<Aspace_ship>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		a_coin_count = ship->owner_character->a_coin;
		b_coin_count = ship->owner_character->b_coin;
		c_coin_count = ship->owner_character->c_coin;
		break;
	}
	default:
		break;
	}

	switch (coin_type)
	{
	case 1:
		if (a_coin_count < sell_count) {
			Button_sell_button->SetIsEnabled(false);
		}
		else {
			Button_sell_button->SetIsEnabled(true);
		}
		break;
	case 2:
		if (b_coin_count < sell_count) {
			Button_sell_button->SetIsEnabled(false);
		}
		else {
			Button_sell_button->SetIsEnabled(true);
		}
		break;
	case 3:
		if (c_coin_count < sell_count) {
			Button_sell_button->SetIsEnabled(false);
		}
		else {
			Button_sell_button->SetIsEnabled(true);
		}
		break;
	default:
		break;
	}
}

void Uui_coin_prices::OnSellOrderAmountChange(const FText& Text, ETextCommit::Type CommitMethod)
{
	sell_price = FCString::Atoi(*EditableTextBox_sell_orderPrice->GetText().ToString());
	sell_count = FCString::Atoi(*EditableTextBox_sell_orderAmount->GetText().ToString());
	TextBox_sell_sum->SetText(FText::FromString(FString::FromInt(sell_price * sell_count)));

	Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
	int a_coin_count = 0, b_coin_count = 0, c_coin_count = 0;

	switch (GameInstanceRef->mycharacter_type)
	{
	case CHARACTER_TYPE::HUMAN:
	{
		AMyCharacter* player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		a_coin_count = player->a_coin;
		b_coin_count = player->b_coin;
		c_coin_count = player->c_coin;
		break;
	}
	case CHARACTER_TYPE::SPACESHIP:
	{
		Aspace_ship* ship = Cast<Aspace_ship>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		a_coin_count = ship->owner_character->a_coin;
		b_coin_count = ship->owner_character->b_coin;
		c_coin_count = ship->owner_character->c_coin;
		break;
	}
	default:
		break;
	}

	switch (coin_type)
	{
	case 1:
		if (a_coin_count < sell_count) {
			Button_sell_button->SetIsEnabled(false);
		}
		else {
			Button_sell_button->SetIsEnabled(true);
		}
		break;
	case 2:
		if (b_coin_count < sell_count) {
			Button_sell_button->SetIsEnabled(false);
		}
		else {
			Button_sell_button->SetIsEnabled(true);
		}
		break;
	case 3:
		if (c_coin_count < sell_count) {
			Button_sell_button->SetIsEnabled(false);
		}
		else {
			Button_sell_button->SetIsEnabled(true);
		}
		break;
	default:
		break;
	}
}

void Uui_coin_prices::OnBuyButtonClick()
{
	buy_price = FCString::Atoi(*EditableTextBox_buy_orderPrice->GetText().ToString());
	buy_count = FCString::Atoi(*EditableTextBox_buy_orderAmount->GetText().ToString());

	if (buy_price >= click_coin_price) {  // 입력한 가격 >= 현재 코인 가격, 구입 성공
		coin_fail_or_success_wb->text_num = 1;
		coin_fail_or_success_wb->name = click_coin_name;
		coin_fail_or_success_wb->amount = buy_price;
		coin_fail_or_success_wb->price = buy_count;
		coin_fail_or_success_wb->SetVisibility(ESlateVisibility::Visible);

		FTimerHandle WaitHandle;
		float wait_time = 2.0f;
		GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]() {
			coin_fail_or_success_wb->SetVisibility(ESlateVisibility::Hidden);
			}), wait_time, false);

		Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));

		CS_BUY_SELL_PACKET coin_buy_sell_packet;

		coin_buy_sell_packet.size = sizeof(CS_BUY_SELL_PACKET);
		coin_buy_sell_packet.type = CS_BUY_SELL;
		coin_buy_sell_packet.buy_sell_type = BUY_SELL::BUY;
		switch (coin_type)
		{
		case 1:
			coin_buy_sell_packet.coin_type = DROP_ITEM::A_COIN;
			break;
		case 2:
			coin_buy_sell_packet.coin_type = DROP_ITEM::B_COIN;
			break;
		case 3:
			coin_buy_sell_packet.coin_type = DROP_ITEM::C_COIN;
			break;
		default:
			break;
		}
		coin_buy_sell_packet.price = buy_price;
		coin_buy_sell_packet.count = buy_count;

		switch (GameInstanceRef->mycharacter_type)
		{
		case CHARACTER_TYPE::HUMAN:
		{
			AMyCharacter* player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			coin_buy_sell_packet.sessionID = player->mySessionID;
			break;
		}
		case CHARACTER_TYPE::SPACESHIP:
		{
			Aspace_ship* ship = Cast<Aspace_ship>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			coin_buy_sell_packet.sessionID = ship->owner_session_id;
			break;
		}
		default:
			break;
		}

		GameInstanceRef->client->SendToCoinBuySell(coin_buy_sell_packet);
	}
	else {
		coin_fail_or_success_wb->text_num = 2;
		coin_fail_or_success_wb->name = click_coin_name;
		coin_fail_or_success_wb->amount = buy_price;
		coin_fail_or_success_wb->price = buy_count;
		coin_fail_or_success_wb->SetVisibility(ESlateVisibility::Visible);

		FTimerHandle WaitHandle;
		float wait_time = 2.0f;
		GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]() {
			coin_fail_or_success_wb->SetVisibility(ESlateVisibility::Hidden);
			}), wait_time, false);
	}
}

void Uui_coin_prices::OnSellButtonClick()  // 매도 버튼 클릭
{
	sell_price = FCString::Atoi(*EditableTextBox_sell_orderPrice->GetText().ToString());
	sell_count = FCString::Atoi(*EditableTextBox_sell_orderAmount->GetText().ToString());

	if (sell_price <= click_coin_price) {  // 입력한 가격 <= 현재 코인 가격, 판매 성공
		coin_fail_or_success_wb->text_num = 3;
		coin_fail_or_success_wb->name = click_coin_name;
		coin_fail_or_success_wb->amount = sell_price;
		coin_fail_or_success_wb->price = sell_count;
		coin_fail_or_success_wb->SetVisibility(ESlateVisibility::Visible);

		FTimerHandle WaitHandle;
		float wait_time = 2.0f;
		GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]() {
			coin_fail_or_success_wb->SetVisibility(ESlateVisibility::Hidden);
			}), wait_time, false);

		Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));

		CS_BUY_SELL_PACKET coin_buy_sell_packet;

		coin_buy_sell_packet.size = sizeof(CS_BUY_SELL_PACKET);
		coin_buy_sell_packet.type = CS_BUY_SELL;
		coin_buy_sell_packet.buy_sell_type = BUY_SELL::SELL;
		switch (coin_type)
		{
		case 1:
			coin_buy_sell_packet.coin_type = DROP_ITEM::A_COIN;
			break;
		case 2:
			coin_buy_sell_packet.coin_type = DROP_ITEM::B_COIN;
			break;
		case 3:
			coin_buy_sell_packet.coin_type = DROP_ITEM::C_COIN;
			break;
		default:
			break;
		}
		coin_buy_sell_packet.price = sell_price;
		coin_buy_sell_packet.count = sell_count;

		switch (GameInstanceRef->mycharacter_type)
		{
		case CHARACTER_TYPE::HUMAN:
		{
			AMyCharacter* player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			coin_buy_sell_packet.sessionID = player->mySessionID;
			break;
		}
		case CHARACTER_TYPE::SPACESHIP:
		{
			Aspace_ship* ship = Cast<Aspace_ship>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			coin_buy_sell_packet.sessionID = ship->owner_session_id;
			break;
		}
		default:
			break;
		}

		GameInstanceRef->client->SendToCoinBuySell(coin_buy_sell_packet);
	}
	else {
		coin_fail_or_success_wb->text_num = 4;
		coin_fail_or_success_wb->name = click_coin_name;
		coin_fail_or_success_wb->amount = sell_price;
		coin_fail_or_success_wb->price = sell_count;
		coin_fail_or_success_wb->SetVisibility(ESlateVisibility::Visible);

		FTimerHandle WaitHandle;
		float wait_time = 2.0f;
		GetWorld()->GetTimerManager().SetTimer(WaitHandle, FTimerDelegate::CreateLambda([&]() {
			coin_fail_or_success_wb->SetVisibility(ESlateVisibility::Hidden);
			}), wait_time, false);
	}
}