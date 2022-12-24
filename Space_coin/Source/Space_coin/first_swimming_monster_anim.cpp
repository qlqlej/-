#include "first_swimming_monster_anim.h"
#include "first_swimming_monster.h"

Ufirst_swimming_monster_anim::Ufirst_swimming_monster_anim()
{
    move_stop = true;
    attack_enable = true;
    is_ground = true;

    anim_type = (uint8)Emonster_anim::Idle;

    moving = false;
}

void Ufirst_swimming_monster_anim::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();
}

void Ufirst_swimming_monster_anim::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    Afirst_swimming_monster* owner = Cast<Afirst_swimming_monster>(TryGetPawnOwner());

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

void Ufirst_swimming_monster_anim::ChangeAnim(Emonster_anim anim)
{
    anim_type = (int)anim;
}

void Ufirst_swimming_monster_anim::AnimNotify_AttackStart()
{
    Afirst_swimming_monster* owner = Cast<Afirst_swimming_monster>(TryGetPawnOwner());

    if (IsValid(owner)) {
        owner->attack = true;
        owner->Attack();
    }
}

void Ufirst_swimming_monster_anim::AnimNotify_AttackEnd()
{
    Afirst_swimming_monster* owner = Cast<Afirst_swimming_monster>(TryGetPawnOwner());

    if (IsValid(owner)) {
        owner->attack = false;
        owner->AttackEnd();
    }
}

void Ufirst_swimming_monster_anim::AnimNotify_HitEnd()
{
    Afirst_swimming_monster* owner = Cast<Afirst_swimming_monster>(TryGetPawnOwner());

    if (IsValid(owner)) {
        owner->hit = false;
        owner->HitEnd();
    }
}

void Ufirst_swimming_monster_anim::AnimNotify_DeathEnd()
{
    Afirst_swimming_monster* owner = Cast<Afirst_swimming_monster>(TryGetPawnOwner());

    if (IsValid(owner)) {
        owner->death = false;
        owner->DeathEnd();
    }
}

