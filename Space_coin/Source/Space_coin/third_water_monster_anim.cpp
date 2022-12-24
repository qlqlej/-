#include "third_water_monster_anim.h"
#include "third_water_monster.h"


Uthird_water_monster_anim::Uthird_water_monster_anim()
{
    move_stop = true;
    attack_enable = true;
    is_ground = true;

    anim_type = (uint8)Emonster_anim::Idle;
}

void Uthird_water_monster_anim::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();
}

void Uthird_water_monster_anim::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    Athird_water_monster* owner = Cast<Athird_water_monster>(TryGetPawnOwner());

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

void Uthird_water_monster_anim::ChangeAnim(Emonster_anim anim)
{
    anim_type = (int)anim;
}

void Uthird_water_monster_anim::AnimNotify_AttackStart()
{
    Athird_water_monster* owner = Cast<Athird_water_monster>(TryGetPawnOwner());

    if (IsValid(owner)) {
        owner->attack = true;
        owner->Attack();
        owner->EnableWeaponCollision(true);
    }
}

void Uthird_water_monster_anim::AnimNotify_AttackEnd()
{
    Athird_water_monster* owner = Cast<Athird_water_monster>(TryGetPawnOwner());

    if (IsValid(owner)) {
        owner->EnableWeaponCollision(false);
    }
}

void Uthird_water_monster_anim::AnimNotify_AttackNext()
{
    Athird_water_monster* owner = Cast<Athird_water_monster>(TryGetPawnOwner());

    if (IsValid(owner)) {
        owner->attack = false;
        owner->AttackEnd();
    }
}

void Uthird_water_monster_anim::AnimNotify_AttackAllEnd()
{
    Athird_water_monster* owner = Cast<Athird_water_monster>(TryGetPawnOwner());

    if (IsValid(owner)) {
        owner->attack = false;
        owner->AttackEnd();
    }
}

void Uthird_water_monster_anim::AnimNotify_SkillEnd()
{
    Athird_water_monster* owner = Cast<Athird_water_monster>(TryGetPawnOwner());

    if (IsValid(owner)) {
        owner->skill = false;
        owner->SkillEnd();
    }
}

void Uthird_water_monster_anim::AnimNotify_HitEnd()
{
    Athird_water_monster* owner = Cast<Athird_water_monster>(TryGetPawnOwner());

    if (IsValid(owner)) {
        owner->hit = false;
        owner->HitEnd();
    }
}

void Uthird_water_monster_anim::AnimNotify_DeathEnd()
{
    Athird_water_monster* owner = Cast<Athird_water_monster>(TryGetPawnOwner());

    if (IsValid(owner)) {
        owner->death = false;
        owner->DeathEnd();
    }
}