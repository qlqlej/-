#include "third_swimming_monster_anim.h"
#include "third_swimming_monster.h"

Uthird_swimming_monster_anim::Uthird_swimming_monster_anim()
{
    move_stop = true;
    attack_enable = true;
    is_ground = true;

    anim_type = (uint8)Emonster_anim::Idle;

    moving = false;
}

void Uthird_swimming_monster_anim::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();
}

void Uthird_swimming_monster_anim::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    Athird_swimming_monster* owner = Cast<Athird_swimming_monster>(TryGetPawnOwner());

    if (IsValid(owner)) {
        UCharacterMovementComponent* movement = owner->GetCharacterMovement();

        if (IsValid(movement)) {
           
            if (moving == true) {
                move_stop = false;
                anim_type = (uint8)Emonster_anim::Run;
            }
            else {
                move_stop = true;
            }
        }
    }
}

void Uthird_swimming_monster_anim::ChangeAnim(Emonster_anim anim)
{
    anim_type = (int)anim;
}

void Uthird_swimming_monster_anim::AnimNotify_AttackStart()
{
    Athird_swimming_monster* owner = Cast<Athird_swimming_monster>(TryGetPawnOwner());

    if (IsValid(owner)) {
        owner->attack = true;
        owner->Attack();
    }
}

void Uthird_swimming_monster_anim::AnimNotify_AttackEnd()
{
    Athird_swimming_monster* owner = Cast<Athird_swimming_monster>(TryGetPawnOwner());

    if (IsValid(owner)) {
        owner->attack = false;
        owner->AttackEnd();
    }
}

void Uthird_swimming_monster_anim::AnimNotify_SkillEnd()
{
    Athird_swimming_monster* owner = Cast<Athird_swimming_monster>(TryGetPawnOwner());

    if (IsValid(owner)) {
        owner->skill = false;
        owner->SkillEnd();
    }
}

void Uthird_swimming_monster_anim::AnimNotify_HitEnd()
{
    Athird_swimming_monster* owner = Cast<Athird_swimming_monster>(TryGetPawnOwner());

    if (IsValid(owner)) {
        owner->hit = false;
        owner->HitEnd();
    }
}

void Uthird_swimming_monster_anim::AnimNotify_DeathEnd()
{
    Athird_swimming_monster* owner = Cast<Athird_swimming_monster>(TryGetPawnOwner());

    if (IsValid(owner)) {
        owner->death = false;
        owner->DeathEnd();
    }
}

