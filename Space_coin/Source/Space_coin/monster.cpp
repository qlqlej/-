#include "monster.h"
#include "game_instance.h"  // 추가

Amonster::Amonster()
{
	PrimaryActorTick.bCanEverTick = true;

	spawn_point = nullptr;
	attack = false; 


	GetMesh()->SetGenerateOverlapEvents(true);
	GetMesh()->CanCharacterStepUpOn = ECB_No;
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision")); 

	trace_range = 1000.f;
	attack_dist = 500.f;

	move_point = 0; 
	move_point_dir = 1;  // 방향 설정하는 변수. 1, -1로만 사용.

	GetCapsuleComponent()->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel2);
}

Amonster::~Amonster()
{

}

void Amonster::AddPatrolPoint(Apatrol_point* point) 
{
	patrol_point_array.Add(point);
}

void Amonster::BeginPlay()
{
	Super::BeginPlay();
	
	Ugame_instance* game_inst = GetGameInstance<Ugame_instance>();

	const FMonsterInfo* monster_info = game_inst->FindMonsterInfo(monster_name);
	if (monster_info) {
		monster_state.attack = monster_info->attack;
		monster_state.skill = monster_info->skill;
		monster_state.armor = monster_info->armor;
		monster_state.hp = monster_info->hp;
		monster_state.max_hp = monster_info->max_hp;
		monster_state.mp = monster_info->mp;
		monster_state.max_mp = monster_info->max_mp;
		trace_range = monster_info->trace_range;
		attack_dist = monster_info->attack_range;
	}
}

void Amonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void Amonster::ChangeAnim(Emonster_anim anim)
{
}

void Amonster::AttackEnd()
{
	attack = false;
}

void Amonster::SkillEnd()
{
	skill = false;
}

void Amonster::HitEnd()
{
	hit = false;
}

void Amonster::DeathEnd()
{
	death = false;
}
