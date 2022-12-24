#include "third_sand_monster_anim.h"
#include "third_sand_monster.h"


Uthird_sand_monster_anim::Uthird_sand_monster_anim()
{
    move_stop = true;
    attack_enable = true;
    is_ground = true;

    anim_type = (uint8)Emonster_anim::Idle;
}

void Uthird_sand_monster_anim::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();
}

void Uthird_sand_monster_anim::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    Athird_sand_monster* owner = Cast<Athird_sand_monster>(TryGetPawnOwner());

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

void Uthird_sand_monster_anim::ChangeAnim(Emonster_anim anim)
{
    anim_type = (uint8)anim;
}

void Uthird_sand_monster_anim::AnimNotify_AttackStart()
{
    Athird_sand_monster* owner = Cast<Athird_sand_monster>(TryGetPawnOwner());

    if (IsValid(owner)) {
        owner->attack = true;
        owner->Attack();
        owner->EnableWeaponCollision(true);
    }
}

void Uthird_sand_monster_anim::AnimNotify_AttackEnd()
{
    Athird_sand_monster* owner = Cast<Athird_sand_monster>(TryGetPawnOwner());

    if (IsValid(owner)) {
        owner->EnableWeaponCollision(false);
    }
}

void Uthird_sand_monster_anim::AnimNotify_AttackNext()
{
    Athird_sand_monster* owner = Cast<Athird_sand_monster>(TryGetPawnOwner());

    if (IsValid(owner)) {
        owner->attack = false;
        owner->AttackEnd();
    }
}

void Uthird_sand_monster_anim::AnimNotify_AttackAllEnd()
{
    Athird_sand_monster* owner = Cast<Athird_sand_monster>(TryGetPawnOwner());

    if (IsValid(owner)) {
        owner->attack = false;
        owner->AttackEnd();
    }
}

void Uthird_sand_monster_anim::AnimNotify_SkillEnd()
{
    Athird_sand_monster* owner = Cast<Athird_sand_monster>(TryGetPawnOwner());

    if (IsValid(owner)) {
        owner->skill = false;
        owner->SkillEnd();
    }
}

void Uthird_sand_monster_anim::AnimNotify_HitEnd()
{
    Athird_sand_monster* owner = Cast<Athird_sand_monster>(TryGetPawnOwner());

    if (IsValid(owner)) {
        owner->hit = false;
        owner->HitEnd();
    }
}

void Uthird_sand_monster_anim::AnimNotify_DeathEnd()
{
    Athird_sand_monster* owner = Cast<Athird_sand_monster>(TryGetPawnOwner());

    if (IsValid(owner)) {
        owner->death = false;
        owner->DeathEnd();
    }
}