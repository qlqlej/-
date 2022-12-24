#pragma once

#include "game_info.h"
#include "Blueprint/UserWidget.h"
#include "ui_coin_fail_or_success.generated.h"

UCLASS()
class SPACE_COIN_API Uui_coin_fail_or_success : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UTextBlock* TextBlock_text; 

	int text_num;

	FString str;
	FText text;

	FString name;
	int amount;
	int price;

protected:
	virtual void NativeConstruct() override;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

};
