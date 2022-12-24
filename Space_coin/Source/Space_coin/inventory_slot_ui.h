// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "game_info.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Engine/DataTable.h"
#include "MyCharacter.h"
#include "shop_slot_ui.h"
#include "inventory_slot_ui.generated.h"
DECLARE_DELEGATE_TwoParams(FOnBossDiedDelegate, int32, int32);




UCLASS()
class SPACE_COIN_API Uinventory_slot_ui : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
		class UButton* button_item;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UTextBlock* item_name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UImage* thumbnail;

	class UDataTable* item_data_table;

	int32 item_id;

	int32 quantity_int;

	FItemDataTable* item_table_row;

	FOnBossDiedDelegate OnBossDied;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UTextBlock* quantity;


public:
	virtual void NativeConstruct() override;
	UFUNCTION()
		void OnItemButtonClicked();


};