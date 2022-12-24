// Fill out your copyright notice in the Description page of Project Settings.


#include "inventory_slot_ui.h"
#include "Input/Reply.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Engine/Texture2D.h"
#include "Components/Image.h"
#include "MyCharacter.h"

void Uinventory_slot_ui::NativeConstruct()
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
			quantity->SetText(FText::FromString(FString::FromInt(quantity_int)));
			thumbnail->Brush.SetResourceObject(item_table_row->thumbnail);
			
		}

	}
	else
	{
		item_name->SetText(FText::FromString(TEXT("")));
		quantity->SetText(FText::FromString(TEXT("")));
		thumbnail->SetVisibility(ESlateVisibility::Hidden);

	}
}

void Uinventory_slot_ui::OnItemButtonClicked()
{

	AMyCharacter* player = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (player->money >= item_table_row->cost)
	{
		player->SpendMoney(item_table_row->cost);
	}
}