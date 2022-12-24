#include "ui_coin_map.h"
#include "Kismet/KismetInputLibrary.h"
#include "Input/Reply.h"
#include "MainGamePlayerController.h"
#include "ui_coin_prices.h"
#include "ui_coin_info.h"
#include "ui_coin_trading_buy.h"
#include "ui_coin_trading_sell.h"
#include "ui_player_balance.h"
#include "ui_player_holdings.h"
#include "ui_coin_price_info.h"

void Uui_coin_map::NativeConstruct() 
{
	Super::NativeConstruct();

	SetVisibility(ESlateVisibility::Hidden);

	coin_prices_wb = Cast<Uui_coin_prices>(GetWidgetFromName(TEXT("coin_prices_wb")));
	player_balance_wb = Cast<Uui_player_balance>(GetWidgetFromName(TEXT("player_balance_wb")));
	player_holdings_wb = Cast<Uui_player_holdings>(GetWidgetFromName(TEXT("player_holdings_wb")));
}

void Uui_coin_map::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	coin_prices_wb->SetData();
	player_holdings_wb->SetData();
}

FReply Uui_coin_map::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (UKismetInputLibrary::GetKey(InKeyEvent) == EKeys::P)
	{
		AMainGamePlayerController* player_controller = Cast<AMainGamePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		player_controller->coin_map_ui_visible = false;
		SetVisibility(ESlateVisibility::Hidden);
	}

	return FReply::Handled();
}

void Uui_coin_map::PressPKey()
{
	if (GetVisibility() == ESlateVisibility::Visible) {
		SetVisibility(ESlateVisibility::Hidden);
	}
	else {
		SetVisibility(ESlateVisibility::Visible);
	}
}