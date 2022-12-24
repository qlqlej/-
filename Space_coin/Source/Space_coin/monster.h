#pragma once

#include "spawn_point.h"
#include "GameFramework/Character.h"
#include "..\..\..\SpaceCoin_Server\SpaceCoin_Server\protocol.h"
#include "monster.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackEndDelegate)

USTRUCT(Atomic, BlueprintType)  // 몬스터 상태 정보
struct FMonsterState
{
	GENERATED_USTRUCT_BODY()

public:
	FMonsterState()
	{
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	float attack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	float skill;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	float armor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	int32 hp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	int32 max_hp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	int32 mp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	int32 max_mp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	float trace_range;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	float attack_range;
};

UCLASS()
class SPACE_COIN_API Amonster : public ACharacter
{
	GENERATED_BODY()

public:
	Amonster();
	~Amonster();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	Aspawn_point* spawn_point;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	float trace_range;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	float attack_dist;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	TArray<Apatrol_point*> patrol_point_array;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Colision)
	UBoxComponent* weapon_box_r;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Colision)
	UBoxComponent* weapon_box_l;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	FMonsterState monster_state;  // 몬스터 상태 정보

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	FName monster_name;  // 몬스터 이름

	int32 move_point;
	int32 move_point_dir; 

	FOnAttackEndDelegate on_attack_end;
	TArray<FDelegateHandle> attack_end_handle;

public:
	bool attack = false;
	bool skill = false;
	bool hit = false;
	bool death = false;
	bool damage = false;

	MONSTER_TYPE monster_type;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI)
	class UWidgetComponent* monster_hp;

	class Uui_monster_hp* monster_hp_ui;

public:
	int sessionID;
	float hp;
	float max_hp;

	void AddPatrolPoint(Apatrol_point* point);

	int32 GetPatrolPointCount() const  // patrol_point_array 갯수 넘겨주는 함수.
	{
		return patrol_point_array.Num();
	}

	Apatrol_point* GetPatrolPoint()  // 현재 patrol point 얻을 수 있는 함수
	{
		return patrol_point_array[move_point];   
	}

	void NextPatrolPoint()  // 다음 패트롤 포인트 가리키도록 하는 함수.
	{
		move_point += move_point_dir;  

		if (move_point == patrol_point_array.Num()) {  // 끝까지 도달했을 경우, 
			move_point_dir = -1;  // 반대 방향으로 가도록.
			move_point = patrol_point_array.Num() - 2;
		}
		else if (move_point == -1) {
			move_point_dir = 1;
			move_point = 0;
		}
	}

public:
	float GetTraceRange() const 
	{
		return trace_range;
	}

	float GetAttackDistance() const
	{
		return attack_dist;
	}

	void Attack() 
	{
		attack = true;
	}

	bool IsAttack() const  
	{
		return attack;
	}

	void Skill() 
	{
		skill = true;
	}

	bool IsSkill() const  
	{
		return skill;
	}

	void Hit()
	{
		hit = true;
	}

	bool IsHit() const
	{
		return hit;
	}

	void Death()
	{
		death = true;
	}

	bool IsDeath() const
	{
		return death;
	}

public:
	float GetHp() {
		return hp;
	}

	float GetMaxHp() {
		return max_hp;
	}

public:
	void SetSpawnPoint(Aspawn_point* point) 
	{
		spawn_point = point;
	}

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	virtual void ChangeAnim(Emonster_anim anim);

public:
	void AttackEnd();

	void SkillEnd();

	void HitEnd();

	void DeathEnd(); 

};
