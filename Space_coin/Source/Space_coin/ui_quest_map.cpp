#include "ui_quest_map.h"
#include "ui_quest.h"
#include "MainGamePlayerController.h"
#include "Kismet/KismetInputLibrary.h"

void Uui_quest_map::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibility(ESlateVisibility::Hidden);

	quest_wb = Cast<Uui_quest>(GetWidgetFromName(TEXT("quest_wb")));
}

void Uui_quest_map::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

FReply Uui_quest_map::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (UKismetInputLibrary::GetKey(InKeyEvent) == EKeys::Tab)
	{
		AMainGamePlayerController* player_controller = Cast<AMainGamePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		player_controller->quest_ui_visible = false;
		SetVisibility(ESlateVisibility::Hidden);
	}

	return FReply::Handled();
}

void Uui_quest_map::PressTabKey()
{
	if (GetVisibility() == ESlateVisibility::Visible) {
		SetVisibility(ESlateVisibility::Hidden);
	}
	else {
		SetVisibility(ESlateVisibility::Visible);
	}
}


