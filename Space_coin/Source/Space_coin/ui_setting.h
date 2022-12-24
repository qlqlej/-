#pragma once

#include "game_info.h"
#include "Blueprint/UserWidget.h"
#include "ui_setting.generated.h"

UCLASS()
class SPACE_COIN_API Uui_setting : public UUserWidget
{
	GENERATED_BODY()

public:
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UButton* game_quit_button;

public:
	virtual void NativeConstruct() override;

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent);

	UFUNCTION(BlueprintCallable)
	void OnQuitButtonClick();

	void PressEscKey();

};
