// Fill out your copyright notice in the Description page of Project Settings.


#include "inventory_ui.h"
#include "Kismet/KismetInputLibrary.h"
#include "Input/Reply.h"
#include "inventory_slot_ui.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "Components/Button.h"
#include "MyCharacter.h"
#include "space_ship.h"
#include "game_instance.h"
#include "MainGamePlayerController.h"
void Uinventory_ui::NativeConstruct()
{
	Super::NativeConstruct();
	SetVisibility(ESlateVisibility::Hidden);
	button_exit->OnClicked.AddDynamic(this, &Uinventory_ui::OnExitButtonClicked);
	Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
	switch (GameInstanceRef->mycharacter_type)
	{
		case CHARACTER_TYPE::HUMAN:
		{
			AMyCharacter* player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			for (int i = 0; i < 14; i++)
			{
				play_inventory_slot_ui_object = CreateWidget<Uinventory_slot_ui>(this, play_inventory_slot_class);
				play_inventory_slot_ui_object->item_id = FetchItem(i);
				if (play_inventory_slot_ui_object->item_id != -1)
					play_inventory_slot_ui_object->quantity_int = player->inventory_component->inventory_map[i];
				else
					play_inventory_slot_ui_object->quantity_int = 0;
				ItemGrid->AddChildToUniformGrid(play_inventory_slot_ui_object, i / 4, i % 4);
			}
			break;
		}
		case  CHARACTER_TYPE::SPACESHIP:
		{
			Aspace_ship* ship = Cast<Aspace_ship>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			for (int i = 0; i < 14; i++)
			{
				play_inventory_slot_ui_object = CreateWidget<Uinventory_slot_ui>(this, play_inventory_slot_class);
				play_inventory_slot_ui_object->item_id = FetchItem(i);
				if (play_inventory_slot_ui_object->item_id != -1)
					play_inventory_slot_ui_object->quantity_int = ship->owner_character->inventory_component->inventory_map[i];
				else
					play_inventory_slot_ui_object->quantity_int = 0;
				ItemGrid->AddChildToUniformGrid(play_inventory_slot_ui_object, i / 4, i % 4);
			}
			break;
		}
	default:
		break;
	}
	UpdatePlayerWallet();
}
FReply Uinventory_ui::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (UKismetInputLibrary::GetKey(InKeyEvent) == EKeys::I)
	{
		AMainGamePlayerController* player_controller = Cast<AMainGamePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		player_controller->inventory_visible = false;
		SetVisibility(ESlateVisibility::Hidden);
	}


	return FReply::Handled();
}

void Uinventory_ui::PressIKey()
{
	if (GetVisibility() == ESlateVisibility::Visible) {
		SetVisibility(ESlateVisibility::Hidden);
	}
	else {
		SetVisibility(ESlateVisibility::Visible);
	}
}
void Uinventory_ui::UpdatePlayerWallet()
{
	Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
	switch (GameInstanceRef->mycharacter_type)
	{
		case CHARACTER_TYPE::HUMAN:
		{
			AMyCharacter* player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			TArray<FStringFormatArg> args;
			args.Add(FStringFormatArg(player->money));
			FString string = FString::Format(TEXT(" {0} Gold"), args);
			player_money->SetText(FText::FromString(string));
			break;
		}
		case CHARACTER_TYPE::SPACESHIP:
		{
			Aspace_ship* ship = Cast<Aspace_ship>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
			TArray<FStringFormatArg> args;
			args.Add(FStringFormatArg(ship->owner_character->money));
			FString string = FString::Format(TEXT(" {0} Gold"), args);
			player_money->SetText(FText::FromString(string));
			break;
		}
		default:
			break;
	}

}
int32 Uinventory_ui::FetchItem(int32 index)
{
	Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
	switch (GameInstanceRef->mycharacter_type)
	{
	case CHARACTER_TYPE::HUMAN:
	{
		AMyCharacter* player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (player->inventory_component->inventory_map.Contains(index))
			return index;
		else
			return -1;
		break;
	}
	case CHARACTER_TYPE::SPACESHIP:
	{
		Aspace_ship* ship = Cast<Aspace_ship>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (ship->owner_character->inventory_component->inventory_map.Contains(index))
			return index;
		else
			return -1;
		break;
	}
	default:
		break;
	}
	return -1;
}
void Uinventory_ui::OnExitButtonClicked()
{
	SetVisibility(ESlateVisibility::Hidden);
	AMainGamePlayerController* player_controller = Cast<AMainGamePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	player_controller->inventory_visible = false;
}

