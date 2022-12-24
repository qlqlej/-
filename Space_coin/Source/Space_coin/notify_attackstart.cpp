#include "notify_attackstart.h"
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

FString Unotify_attackstart::GetNotifyName_Implementation() const
{
	return L"AttackStart";
}

void Unotify_attackstart::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	
}