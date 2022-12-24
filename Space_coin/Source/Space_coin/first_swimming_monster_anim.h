#pragma once

#include "game_info.h"
#include "Animation/AnimInstance.h"
#include "first_swimming_monster_anim.generated.h"

UCLASS()
class SPACE_COIN_API Ufirst_swimming_monster_anim : public UAnimInstance
{
	GENERATED_BODY()

public:
	Ufirst_swimming_monster_anim();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true", Bitmask, BitmaskEnum = "Emonster_anim"))
	uint8 anim_type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	bool move_stop;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	bool is_ground;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	bool attack_enable;

public:
	bool moving;

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

public:
	void ChangeAnim(Emonster_anim anim);

public:
	UFUNCTION()
	void AnimNotify_AttackStart();

	UFUNCTION()
	void AnimNotify_AttackEnd();

	UFUNCTION()
	void AnimNotify_HitEnd();

	UFUNCTION()
	void AnimNotify_DeathEnd();

};
