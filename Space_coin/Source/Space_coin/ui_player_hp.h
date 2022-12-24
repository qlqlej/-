#pragma once

#include "game_info.h"
#include "Mycharacter.h"
#include "Blueprint/UserWidget.h"
#include "ui_player_hp.generated.h"

UCLASS()
class SPACE_COIN_API Uui_player_hp : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UImage* hp_image;

	UMaterialInstance* material_instance;
	UMaterialInstanceDynamic* dynamic_material_instance;

	AMyCharacter* myCharacter;

protected:
	virtual void NativeConstruct() override;

public:
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

};
