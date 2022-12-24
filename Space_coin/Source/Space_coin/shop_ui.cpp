// Fill out your copyright notice in the Description page of Project Settings.


#include "shop_ui.h"
#include "Kismet/KismetInputLibrary.h"
#include "Input/Reply.h"
#include "shop_slot_ui.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"
#include "Components/Button.h"
#include "MainGamePlayerController.h"
#include "MyCharacter.h"
#include "game_instance.h"
void Ushop_ui::NativeConstruct()
{
	Super::NativeConstruct();
	SetVisibility(ESlateVisibility::Hidden);
	button_exit->OnClicked.AddDynamic(this, &Ushop_ui::OnExitButtonClicked);
	
	for (int i = 0; i < 14; i++) 
	{
		play_shop_slot_ui_object = CreateWidget<Ushop_slot_ui>(this, play_shop_slot_class);
		play_shop_slot_ui_object->item_id = FetchItem(i);
		ItemGrid->AddChildToUniformGrid(play_shop_slot_ui_object,i/4, i%4 );
	}
	UpdatePlayerWallet();
}
FReply Ushop_ui::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (UKismetInputLibrary::GetKey(InKeyEvent) == EKeys::B)
	{
		AMainGamePlayerController* player_controller = Cast<AMainGamePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		player_controller->shop_visible = false;
		SetVisibility(ESlateVisibility::Hidden);
	}

	return FReply::Handled();
}

void Ushop_ui::PressBKey()
{
	if (GetVisibility() == ESlateVisibility::Visible) {
		SetVisibility(ESlateVisibility::Hidden);
	}
	else {
		SetVisibility(ESlateVisibility::Visible);
	}
}
void Ushop_ui::UpdatePlayerWallet()
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
int32 Ushop_ui::FetchItem(int32 index)
{
	if (IntArray.IsValidIndex(index))
		return IntArray[index];
	else
		return -1;
}
void Ushop_ui::OnExitButtonClicked()
{
	AMainGamePlayerController* player_controller = Cast<AMainGamePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	player_controller->shop_visible = false;
	SetVisibility(ESlateVisibility::Hidden);
	
}

void Ushop_ui::BindSlot(int32 itemid, int32 quantity)
{
	

	UpdatePlayerWallet();
	AMyCharacter* player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	player->inventory_component->AddtoInventory(itemid, quantity);
		
}
