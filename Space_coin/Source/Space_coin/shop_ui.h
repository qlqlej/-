// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "game_info.h"
#include "Blueprint/UserWidget.h"
#include "shop_ui.generated.h"

UCLASS()
class SPACE_COIN_API Ushop_ui : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY( meta = (BindWidget))
		class UButton* button_exit;
	UPROPERTY(meta = (BindWidget))
		class UUniformGridPanel* ItemGrid;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* player_money;
	UFUNCTION()
		void OnExitButtonClicked();

	UFUNCTION()
		void BindSlot(int32 itemid, int32 quantity);

	UFUNCTION()
		void UpdatePlayerWallet();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TSubclassOf<class Ushop_slot_ui> play_shop_slot_class;

	class Ushop_slot_ui* play_shop_slot_ui_object;

	TArray<int32> IntArray = {0,1,2,3,4,5,6,7,8,9,10,11,12,13};
public:
	virtual void NativeConstruct() override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent);
	void PressBKey();
	int32 FetchItem(int32 index);

};
