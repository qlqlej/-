#pragma once

#include "game_info.h"
#include "monster.h"
#include "first_ice_monster.h"
#include "second_ice_monster.h"
#include "third_ice_monster.h"
#include "first_sand_monster.h"
#include "second_sand_monster.h"
#include "third_sand_monster.h"
#include "first_water_monster.h"
#include "second_water_monster.h"
#include "third_water_monster.h"
#include "Blueprint/UserWidget.h"
#include "ui_monster_hp.generated.h"

UCLASS()
class SPACE_COIN_API Uui_monster_hp : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	class UProgressBar* hp_bar;

	void SetOwnerMonster(Amonster* monster) { OwnerMonster = monster; }

protected:
	virtual void NativeConstruct() override;  // »ý¼ºÀÚ

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	TWeakObjectPtr<Amonster> OwnerMonster;

};
