#pragma once

#include "game_info.h"
#include "GameFramework/PlayerController.h"
#include "player_controller_ui.generated.h"

UCLASS()
class SPACE_COIN_API Aplayer_controller_ui : public APlayerController
{
	GENERATED_BODY()
	
public:
	Aplayer_controller_ui();

	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class Uui_play_map> play_map_ui_class;

	class Uui_play_map* play_map_ui_object;

public:
	virtual void Tick(float DeltaTime) override;
};
