#pragma once

#include "game_info.h"
#include "Blueprint/UserWidget.h"
#include "ui_player_holdings.generated.h"

UCLASS()
class SPACE_COIN_API Uui_player_holdings : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UListView* player_holding_list_view;

protected:
	virtual void NativeConstruct() override;  // »ý¼ºÀÚ

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UFUNCTION(BlueprintCallable)
	void InitList();

	UFUNCTION(BlueprintCallable)
	void ItemClick(UObject* obj);

	void SetData();

	class AMyCharacter* player;

	class AMainGamePlayerController* pc;

};
