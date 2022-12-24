#include "second_ice_monster_anim.h"
#include "second_ice_monster.h"


Usecond_ice_monster_anim::Usecond_ice_monster_anim()
{
    move_stop = true;
    attack_enable = true;
    is_ground = true;

    anim_type = (uint8)Emonster_anim::Idle;
}

void Usecond_ice_monster_anim::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();
}

void Usecond_ice_monster_anim::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);


    Asecond_ice_monster* owner = Cast<Asecond_ice_monster>(TryGetPawnOwner());

    if (IsValid(owner)) {
        UCharacterMovementComponent* movement = owner->GetCharacterMovement();

        if (IsValid(movement)) {
            is_ground = movement->IsMovingOnGround();

            if (is_ground) {
                if (movement->Velocity.Size() > 0.f) {
                    move_stop = false;
                    anim_type = (uint8)Emonster_anim::Run;
                }
                else {
                    move_stop = true;
                }
            }
        }
    }
}

void Usecond_ice_monster_anim::ChangeAnim(Emonster_anim anim)
{
    anim_type = (int)anim;
}

void Usecond_ice_monster_anim::AnimNotify_AttackStart()
{
    Asecond_ice_monster* owner = Cast<Asecond_ice_monster>(TryGetPawnOwner());

    if (IsValid(owner)) {
        owner->attack = true;
        owner->Attack();
        owner->EnableWeaponCollision(true);
    }
}

void Usecond_ice_monster_anim::AnimNotify_AttackEnd()
{
    Asecond_ice_monster* owner = Cast<Asecond_ice_monster>(TryGetPawnOwner());

    if (IsValid(owner)) {
        owner->EnableWeaponCollision(false);
    }
}

void Usecond_ice_monster_anim::AnimNotify_AttackNext()
{
    Asecond_ice_monster* owner = Cast<Asecond_ice_monster>(TryGetPawnOwner());

    if (IsValid(owner)) {
        owner->attack = false;
        owner->AttackEnd();
    }
}

void Usecond_ice_monster_anim::AnimNotify_AttackAllEnd()
{
    Asecond_ice_monster* owner = Cast<Asecond_ice_monster>(TryGetPawnOwner());

    if (IsValid(owner)) {
        owner->attack = false;
        owner->AttackEnd();
    }
}

void Usecond_ice_monster_anim::AnimNotify_HitEnd()
{
    Asecond_ice_monster* owner = Cast<Asecond_ice_monster>(TryGetPawnOwner());

    if (IsValid(owner)) {
        owner->hit = false;
        owner->HitEnd();
    }
}

void Usecond_ice_monster_anim::AnimNotify_DeathEnd()
{
    Asecond_ice_monster* owner = Cast<Asecond_ice_monster>(TryGetPawnOwner());

    if (IsValid(owner)) {
        owner->death = false;
        owner->DeathEnd();
    }
}