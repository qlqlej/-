#include "ui_player_balance.h"
#include "Components/TextBlock.h"
#include "MyCharacter.h"
#include "game_instance.h"

void Uui_player_balance::NativeConstruct()
{
	Super::NativeConstruct();

	purchase = Cast<UTextBlock>(GetWidgetFromName(TEXT("purchase")));  // √—∏≈¿‘
	evaluation = Cast<UTextBlock>(GetWidgetFromName(TEXT("evaluation")));  // √—∆Ú∞°
	profit_and_loss = Cast<UTextBlock>(GetWidgetFromName(TEXT("profit_and_loss")));  // √—º’¿Õ
	rate = Cast<UTextBlock>(GetWidgetFromName(TEXT("rate"))); // √—ºˆ¿Õ∑¸
	realized_profit_and_loss = Cast<UTextBlock>(GetWidgetFromName(TEXT("realized_profit_and_loss")));  // Ω««ˆº’¿Õ
}

void Uui_player_balance::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
	
	switch (GameInstanceRef->mycharacter_type)
	{
	case CHARACTER_TYPE::HUMAN:
	{
		AMyCharacter* player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		purchase->SetText(FText::FromString(FString::FromInt(player->money)));
		break;
	}
	case CHARACTER_TYPE::SPACESHIP:
	{
		Aspace_ship* ship = Cast<Aspace_ship>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		purchase->SetText(FText::FromString(FString::FromInt(ship->owner_character->money)));
		break;
	}
	default:
		break;
	}
}

void Uui_player_balance::SetPurchase(int32 set_purchase)
{
	FString strText;
	strText = FString::Printf(TEXT("%d"), set_purchase);

	purchase->SetText(FText::FromString(strText));
}

void Uui_player_balance::SetEvaluation(int32 set_evaluation)
{
	FString strText;
	strText = FString::Printf(TEXT("%d"), set_evaluation);

	evaluation->SetText(FText::FromString(strText));
}

void Uui_player_balance::SetProfitAndLoss(int32 set_profit_and_loss)
{
	FString strText;
	strText = FString::Printf(TEXT("%d"), set_profit_and_loss);

	profit_and_loss->SetText(FText::FromString(strText));
}

void Uui_player_balance::SetRate(float set_rate)
{
	FString strText;
	strText = FString::Printf(TEXT("%.2f"), set_rate);

	rate->SetText(FText::FromString(strText));
}

void Uui_player_balance::SetRealizedProfitAndLoss(int32 set_realized_profit_and_loss)
{
	FString strText;
	strText = FString::Printf(TEXT("%d"), set_realized_profit_and_loss);

	realized_profit_and_loss->SetText(FText::FromString(strText));
}