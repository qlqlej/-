// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "game_info.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Engine/DataTable.h"
#include "MyCharacter.h"
#include "shop_slot_ui.generated.h"
DECLARE_DELEGATE_TwoParams(FOnBossDiedDelegate,int32,int32);

USTRUCT(BlueprintType)
struct FMyStruct {

	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Something")
		int32 MyInt;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		FText name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		int32 cost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		UTexture2D* thumbnail;

	
};

USTRUCT(BlueprintType)
struct FItemDataTable :public FTableRowBase
{
	GENERATED_BODY()
public:
	FItemDataTable()
	{
	}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		FText name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		int32 cost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
		UTexture2D* thumbnail;
};

UCLASS()
class SPACE_COIN_API Ushop_slot_ui : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
		class UButton* button_item;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UTextBlock* cost;  
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UTextBlock* item_name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
		class UImage* thumbnail;

	class UDataTable* item_data_table;

	int32 item_id;

	FItemDataTable* item_table_row;

	FOnBossDiedDelegate OnBossDied;

	int32 quantity;

	int32 item_cost;
public:
	virtual void NativeConstruct() override;
	UFUNCTION()
		void OnItemButtonClicked();
	UFUNCTION()
		void UpdateItemCost();


};

