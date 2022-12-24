#include "first_ice_monster_anim.h"
#include "first_ice_monster.h"

Ufirst_ice_monster_anim::Ufirst_ice_monster_anim()
{
    move_stop = true; 
    attack_enable = true;  
    is_ground = true;

    anim_type = (uint8)Emonster_anim::Idle;
}

void Ufirst_ice_monster_anim::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();
}

void Ufirst_ice_monster_anim::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);


    Afirst_ice_monster* owner = Cast<Afirst_ice_monster>(TryGetPawnOwner()); 

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

void Ufirst_ice_monster_anim::ChangeAnim(Emonster_anim anim)
{
    anim_type = (int)anim;
}

void Ufirst_ice_monster_anim::AnimNotify_AttackStart()
{
    Afirst_ice_monster* owner = Cast<Afirst_ice_monster>(TryGetPawnOwner());

    if (IsValid(owner)) {
        owner->attack = true;
        owner->Attack();
        owner->EnableWeaponCollision(true);
    }
}

void Ufirst_ice_monster_anim::AnimNotify_AttackEnd()
{
    Afirst_ice_monster* owner = Cast<Afirst_ice_monster>(TryGetPawnOwner());

    if (IsValid(owner)) {
        owner->attack = false;
        owner->AttackEnd();
        owner->EnableWeaponCollision(false);
    }

}

void Ufirst_ice_monster_anim::AnimNotify_HitEnd()
{
    Afirst_ice_monster* owner = Cast<Afirst_ice_monster>(TryGetPawnOwner());

    if (IsValid(owner)) {
        owner->hit = false;
        owner->HitEnd();
    }
}

void Ufirst_ice_monster_anim::AnimNotify_DeathEnd()
{
    Afirst_ice_monster* owner = Cast<Afirst_ice_monster>(TryGetPawnOwner());

    if (IsValid(owner)) {
        owner->death = false;
        owner->DeathEnd();
    }
}