#include "ui_monster_hp.h"
#include "Components/ProgressBar.h"
#include "MainGamePlayerController.h"

void Uui_monster_hp::NativeConstruct()
{
	Super::NativeConstruct();

	hp_bar = Cast<UProgressBar>(GetWidgetFromName(TEXT("hp_bar")));

}

void Uui_monster_hp::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!OwnerMonster.IsValid()) {
		return;
	}

	hp_bar->SetPercent(OwnerMonster->GetHp() / OwnerMonster->GetMaxHp());
}



