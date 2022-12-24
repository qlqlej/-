// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "game_info.h"
#include "Blueprint/UserWidget.h"
#include "inventory_ui.generated.h"

UCLASS()
class SPACE_COIN_API Uinventory_ui : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
		class UButton* button_exit;
	UPROPERTY(meta = (BindWidget))
		class UUniformGridPanel* ItemGrid;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* player_money;
	UFUNCTION()
		void OnExitButtonClicked();



	UFUNCTION()
		void UpdatePlayerWallet();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TSubclassOf<class Uinventory_slot_ui> play_inventory_slot_class;

	class Uinventory_slot_ui* play_inventory_slot_ui_object;

	TArray<int32> IntArray = { 2, 3 };
public:
	virtual void NativeConstruct() override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent);
	void PressIKey();
	int32 FetchItem(int32 index);

};