#include "player_controller_ui.h"
#include "ui_play_map.h"
#include "Components/InputComponent.h"

Aplayer_controller_ui::Aplayer_controller_ui()
{
	static ConstructorHelpers::FClassFinder<Uui_play_map> play_map(TEXT("WidgetBlueprint'/Game/SpaceCoinContent/UI/PlayMapUI/play_map_wb.play_map_wb_C'"));
	if (play_map.Succeeded()) {
		play_map_ui_class = play_map.Class;
	}
}

void Aplayer_controller_ui::BeginPlay()
{
	Super::BeginPlay();

	play_map_ui_object = CreateWidget<Uui_play_map>(this, play_map_ui_class);
	play_map_ui_object->AddToViewport();

	bShowMouseCursor = true;
}

void Aplayer_controller_ui::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}
