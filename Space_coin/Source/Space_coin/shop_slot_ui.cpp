#include "shop_slot_ui.h"
#include "Input/Reply.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Engine/Texture2D.h"
#include "Components/Image.h"
#include "MyCharacter.h"
#include "MainGamePlayerController.h"
#include "game_instance.h"

void Ushop_slot_ui::NativeConstruct()
{
	Super::NativeConstruct();
	if (item_id >= 0)
	{
		UDataTable* DataTable = LoadObject<UDataTable>(nullptr, TEXT("/Game/SpaceCoinContent/UI/ItemDataTable"));

		item_data_table = DataTable;

		if (item_data_table != nullptr)
		{
			item_table_row = item_data_table->FindRow<FItemDataTable>(FName(*(FString::FormatAsNumber(item_id))), FString(""));
			item_name->SetText(item_table_row->name);
			thumbnail->Brush.SetResourceObject(item_table_row->thumbnail);
			Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
			switch (GameInstanceRef->mycharacter_type)
			{
			case CHARACTER_TYPE::HUMAN:
			{
				AMyCharacter* player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
				if (player->inventory_component->inventory_map.Contains(item_id))
				{
					item_cost = item_table_row->cost;
					for (int i = 0; i < player->inventory_component->inventory_map[item_id]; ++i) {
						item_cost += item_cost * 0.1;
					}
				}
				else
				{
					item_cost = item_table_row->cost;
				}
				cost->SetText(FText::FromString(FString::FromInt(item_cost)));
				break;
			}
			case CHARACTER_TYPE::SPACESHIP:
			{
				Aspace_ship* ship = Cast<Aspace_ship>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
				if (ship->owner_character->inventory_component->inventory_map.Contains(item_id))
				{
					item_cost = item_table_row->cost;
					for (int i = 0; i < ship->owner_character->inventory_component->inventory_map[item_id]; ++i) {
						item_cost += item_cost * 0.1;
					}
				}
				else
				{
					item_cost = item_table_row->cost;
				}
				cost->SetText(FText::FromString(FString::FromInt(item_cost)));
				break;
			}
			default:
				break;
			}

			button_item->OnClicked.AddDynamic(this, &Ushop_slot_ui::OnItemButtonClicked);
		}
	}
	else
	{
		bIsEnabled = false;
		item_name->SetText(FText::FromString(TEXT("")));
		thumbnail->SetVisibility(ESlateVisibility::Hidden);
		cost->SetText(FText::FromString(TEXT("")));
	}
}

void Ushop_slot_ui::OnItemButtonClicked()
{
	Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
	switch (GameInstanceRef->mycharacter_type)
	{
	case CHARACTER_TYPE::HUMAN:
	{
		AMyCharacter* player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (player->money >= item_cost)
		{
			CS_ITEM_BUY_PACKET infodata;
			infodata.price = item_cost;
			infodata.size = sizeof(CS_ITEM_BUY_PACKET);
			infodata.type = CS_ITEM_BUY;
			switch (item_id)
			{
			case 0:
				infodata.item_type = ITEM_TYPE::CRITICAL_UP;
				break;
			case 1:
				infodata.item_type = ITEM_TYPE::SPEED_UP;
				break;
			case 2:
				infodata.item_type = ITEM_TYPE::ATTACK_UP;
				break;
			case 3:
				infodata.item_type = ITEM_TYPE::HP_UP;
				break;
			case 4:
				infodata.item_type = ITEM_TYPE::RECOVER_UP;
				break;
			case 5:
				infodata.item_type = ITEM_TYPE::SNIPER_UP;
				break;
			case 6:
				infodata.item_type = ITEM_TYPE::ATTACK_HP_UP;
				break;
			case 7:
				infodata.item_type = ITEM_TYPE::LAUNCHER_UP;
				break;
			case 8:
				infodata.item_type = ITEM_TYPE::LAUNCHER_RANGE_UP;
				break;
			case 9:
				infodata.item_type = ITEM_TYPE::JUMP_UP;
				break;
			case 10:
				infodata.item_type = ITEM_TYPE::MISSILE_UP;
				break;
			case 11:
				infodata.item_type = ITEM_TYPE::SLASH_UP;
				break;
			case 12:
				infodata.item_type = ITEM_TYPE::SLASH_SIZE_UP;
				break;
			case 13:
				infodata.item_type = ITEM_TYPE::ULTIMATE_UP;
				break;
			default:
				break;
			}
			infodata.gold = player->money;
			infodata.sessionID = player->mySessionID;
			GameInstanceRef->client->SendToItemBuy(infodata);
			item_cost += item_cost * 0.1;
			cost->SetText(FText::FromString(FString::FromInt(item_cost)));
		}
		break;
	}
	case CHARACTER_TYPE::SPACESHIP:
	{
		Aspace_ship* ship = Cast<Aspace_ship>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (ship->owner_character->money >= item_cost)
		{
			CS_ITEM_BUY_PACKET infodata;
			infodata.price = item_cost;
			infodata.size = sizeof(CS_ITEM_BUY_PACKET);
			infodata.type = CS_ITEM_BUY;
			switch (item_id)
			{
			case 0:
				infodata.item_type = ITEM_TYPE::CRITICAL_UP;
				break;
			case 1:
				infodata.item_type = ITEM_TYPE::SPEED_UP;
				break;
			case 2:
				infodata.item_type = ITEM_TYPE::ATTACK_UP;
				break;
			case 3:
				infodata.item_type = ITEM_TYPE::HP_UP;
				break;
			case 4:
				infodata.item_type = ITEM_TYPE::RECOVER_UP;
				break;
			case 5:
				infodata.item_type = ITEM_TYPE::SNIPER_UP;
				break;
			case 6:
				infodata.item_type = ITEM_TYPE::ATTACK_HP_UP;
				break;
			case 7:
				infodata.item_type = ITEM_TYPE::LAUNCHER_UP;
				break;
			case 8:
				infodata.item_type = ITEM_TYPE::LAUNCHER_RANGE_UP;
				break;
			case 9:
				infodata.item_type = ITEM_TYPE::JUMP_UP;
				break;
			case 10:
				infodata.item_type = ITEM_TYPE::MISSILE_UP;
				break;
			case 11:
				infodata.item_type = ITEM_TYPE::SLASH_UP;
				break;
			case 12:
				infodata.item_type = ITEM_TYPE::SLASH_SIZE_UP;
				break;
			case 13:
				infodata.item_type = ITEM_TYPE::ULTIMATE_UP;
				break;
			default:
				break;
			}
			infodata.gold = ship->owner_character->money;
			infodata.sessionID = ship->owner_session_id;
			GameInstanceRef->client->SendToItemBuy(infodata);
			item_cost += item_cost * 0.1;
			cost->SetText(FText::FromString(FString::FromInt(item_cost)));
		}
		break;
	}
	default:
		break;
	}
}

void Ushop_slot_ui::UpdateItemCost()
{
}
