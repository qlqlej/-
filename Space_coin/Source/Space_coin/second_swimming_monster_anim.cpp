#include "second_swimming_monster_anim.h"
#include "second_swimming_monster.h"

Usecond_swimming_monster_anim::Usecond_swimming_monster_anim()
{
    move_stop = true;
    attack_enable = true;
    is_ground = true;

    anim_type = (uint8)Emonster_anim::Idle;

    moving = false;
}

void Usecond_swimming_monster_anim::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();
}

void Usecond_swimming_monster_anim::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    Asecond_swimming_monster* owner = Cast<Asecond_swimming_monster>(TryGetPawnOwner());

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

void Usecond_swimming_monster_anim::ChangeAnim(Emonster_anim anim)
{
    anim_type = (int)anim;
}

void Usecond_swimming_monster_anim::AnimNotify_AttackStart()
{
    Asecond_swimming_monster* owner = Cast<Asecond_swimming_monster>(TryGetPawnOwner());

    if (IsValid(owner)) {
        owner->attack = true;
        owner->Attack();
    }
}

void Usecond_swimming_monster_anim::AnimNotify_AttackEnd()
{
    Asecond_swimming_monster* owner = Cast<Asecond_swimming_monster>(TryGetPawnOwner());

    if (IsValid(owner)) {
        owner->attack = false;
        owner->AttackEnd();
    }
}

void Usecond_swimming_monster_anim::AnimNotify_HitEnd()
{
    Asecond_swimming_monster* owner = Cast<Asecond_swimming_monster>(TryGetPawnOwner());

    if (IsValid(owner)) {
        owner->hit = false;
        owner->HitEnd();
    }
}

void Usecond_swimming_monster_anim::AnimNotify_DeathEnd()
{
    Asecond_swimming_monster* owner = Cast<Asecond_swimming_monster>(TryGetPawnOwner());

    if (IsValid(owner)) {
        owner->death = false;
        owner->DeathEnd();
    }
}

