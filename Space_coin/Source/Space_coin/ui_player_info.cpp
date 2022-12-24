#include "ui_player_info.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "game_instance.h"
#include "MyCharacter.h"

void Uui_player_info::NativeConstruct()
{
	Super::NativeConstruct();

	name_text = Cast<UTextBlock>(GetWidgetFromName(TEXT("name_text")));
	money_text = Cast<UTextBlock>(GetWidgetFromName(TEXT("money_text")));
	hp_bar = Cast<UProgressBar>(GetWidgetFromName(TEXT("hp_bar")));

	GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
}

void Uui_player_info::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (GameInstanceRef->change_map == true) {
		switch (GameInstanceRef->mycharacter_type)
		{
		case CHARACTER_TYPE::HUMAN:
		{
			AMyCharacter* player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

			name_text->SetText(FText::FromName(player->myName));
			money_text->SetText(FText::FromString(FString::FromInt(player->money)));
			hp_bar->SetPercent(player->health / player->max_hp);

			GameInstanceRef->change_map = false;
			break;
		}
		case CHARACTER_TYPE::SPACESHIP:
		{
			Aspace_ship* ship = Cast<Aspace_ship>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

			name_text->SetText(FText::FromName(ship->owner_character->myName));
			money_text->SetText(FText::FromString(FString::FromInt(ship->owner_character->money)));
			hp_bar->SetPercent(ship->owner_character->health / ship->owner_character->max_hp);

			if (name_text->GetText().IsEmpty()) {
				GameInstanceRef->change_map = false;
			}

			break;
		}
		default:
			break;
		}
	}
	else {
		if (GameInstanceRef->name_set == true) {
			switch (GameInstanceRef->mycharacter_type)
			{
			case CHARACTER_TYPE::HUMAN:
			{
				AMyCharacter* player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

				name_text->SetText(FText::FromName(player->myName));
				GameInstanceRef->name_set = false;
				break;
			}
			case CHARACTER_TYPE::SPACESHIP:
			{
				Aspace_ship* ship = Cast<Aspace_ship>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

				name_text->SetText(FText::FromName(ship->owner_character->myName));
				GameInstanceRef->name_set = false;
				break;
			}
			default:
				break;
			}
		}

		if (GameInstanceRef->money_set == true) {
			switch (GameInstanceRef->mycharacter_type)
			{
			case CHARACTER_TYPE::HUMAN:
			{
				AMyCharacter* player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

				money_text->SetText(FText::FromString(FString::FromInt(player->money)));
				GameInstanceRef->money_set = false;
				break;
			}
			case CHARACTER_TYPE::SPACESHIP:
			{
				Aspace_ship* ship = Cast<Aspace_ship>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

				money_text->SetText(FText::FromString(FString::FromInt(ship->owner_character->money)));
				GameInstanceRef->money_set = false;
				break;
			}
			default:
				break;
			}
		}

		if (GameInstanceRef->hp_set == true) {
			switch (GameInstanceRef->mycharacter_type)
			{
			case CHARACTER_TYPE::HUMAN:
			{
				AMyCharacter* player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

				hp_bar->SetPercent(player->health / player->max_hp);
				GameInstanceRef->hp_set = false;
				break;
			}
			case CHARACTER_TYPE::SPACESHIP:
			{
				Aspace_ship* ship = Cast<Aspace_ship>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

				hp_bar->SetPercent(ship->owner_character->health / ship->owner_character->max_hp);
				GameInstanceRef->hp_set = false;
				break;
			}
			default:
				break;
			}
		}
	}
}
