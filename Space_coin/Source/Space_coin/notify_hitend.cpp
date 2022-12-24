#include "notify_hitend.h"
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

FString Unotify_hitend::GetNotifyName_Implementation() const
{
	return L"HitEnd";
}

void Unotify_hitend::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

}
