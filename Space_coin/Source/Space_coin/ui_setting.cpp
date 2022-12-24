#include "ui_setting.h"
#include "Kismet/KismetInputLibrary.h"
#include "Input/Reply.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "MainGamePlayerController.h"
#include "Sound/SoundMix.h"
#include "Sound/SoundClass.h"
#include "game_instance.h"

void Uui_setting::NativeConstruct()
{
	Super::NativeConstruct();
	
	SetVisibility(ESlateVisibility::Hidden);

	game_quit_button = Cast<UButton>(GetWidgetFromName(TEXT("game_quit_button")));


	game_quit_button->OnClicked.AddDynamic(this, &Uui_setting::OnQuitButtonClick);

}

FReply Uui_setting::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (UKismetInputLibrary::GetKey(InKeyEvent) == EKeys::Escape)
	{
		AMainGamePlayerController* player_controller = Cast<AMainGamePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		player_controller->setting_ui_visible = false;
		SetVisibility(ESlateVisibility::Hidden);
	}

	return FReply::Handled();
}

void Uui_setting::OnQuitButtonClick()
{
	FPlatformMisc::RequestExit(true);
}


void Uui_setting::PressEscKey()
{
	if (GetVisibility() == ESlateVisibility::Visible) {
		SetVisibility(ESlateVisibility::Hidden);
	}
	else {
		SetVisibility(ESlateVisibility::Visible);
	}
}