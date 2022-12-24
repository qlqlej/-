#include "third_swimming_monster.h"
#include "third_swimming_monster_anim.h"
#include "swimming_monster_ai_controller.h"
#include "ui_player_hp.h"
#include "ui_monster_hp.h"
#include "Components/WidgetComponent.h"
#include "Components/SpotLightComponent.h"
#include "Kismet/KismetMathLibrary.h"

Athird_swimming_monster::Athird_swimming_monster()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/Luminous_Monster/Mesh/SK_Luminous_Monster'"));

	if (MeshAsset.Succeeded()) {
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FClassFinder<Uthird_swimming_monster_anim> AnimAsset(TEXT("AnimBlueprint'/Game/SpaceCoinContent/Monster/third_swimming_monster_anim_bp'"));

	if (AnimAsset.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);
	}

	GetCapsuleComponent()->SetCapsuleHalfHeight(250.0f);
	GetCapsuleComponent()->SetCapsuleRadius(250.0f);

	GetMesh()->SetRelativeLocation(FVector(200.f, 0.f, 0.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	GetMesh()->SetRelativeScale3D(FVector(8.0f, 8.0f, 8.0f));

	monster_hp = CreateDefaultSubobject<UWidgetComponent>(TEXT("monster_hp"));
	monster_hp->AttachTo(GetCapsuleComponent());
	static ConstructorHelpers::FClassFinder<Uui_monster_hp> MonsterHPUI(TEXT("WidgetBlueprint'/Game/SpaceCoinContent/UI/monster_hp_wb.monster_hp_wb_C'"));
	if (MonsterHPUI.Succeeded()) {
		monster_hp->SetWidgetClass(MonsterHPUI.Class);
	}
	monster_hp->SetWidgetSpace(EWidgetSpace::Screen);
	monster_hp->SetDrawSize(FVector2D(80, 15));
	monster_hp->SetRelativeLocation(FVector(0.0f, 0.0f, 130.0f));

	water_light = CreateDefaultSubobject<USpotLightComponent>(TEXT("water_light"));
	water_light->AttachTo(GetMesh());
	water_light->IntensityUnits = ELightUnits::Candelas;
	water_light->Intensity = 500;
	water_light->AttenuationRadius = 2000;
	water_light->InnerConeAngle = 70;
	water_light->OuterConeAngle = 80;

	move = false;

	monster_name = TEXT("third_swimming_monster");

	monster_type = MONSTER_TYPE::T_FISH;
}

void Athird_swimming_monster::BeginPlay()
{
	Super::BeginPlay();

	third_swimming_monster_anim = Cast<Uthird_swimming_monster_anim>(GetMesh()->GetAnimInstance());

	monster_hp_ui = Cast<Uui_monster_hp>(monster_hp->GetUserWidgetObject());
	monster_hp_ui->SetOwnerMonster(this);
}

void Athird_swimming_monster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (move == true) {
		Move(move_dest, move_rot);
	}
}

void Athird_swimming_monster::ChangeAnim(Emonster_anim anim)
{
	third_swimming_monster_anim->ChangeAnim(anim);
}

void Athird_swimming_monster::MoveToLocation(const FVector& dest, const FRotator& rot)
{


	if (move == false) {
		move = true;

		move_dest = dest;
		move_rot = rot;

		Move(move_dest, move_rot);
	}
}

void Athird_swimming_monster::Move(const FVector& dest, const FRotator& rot)
{
	FRotator r = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), dest);
	FVector vec = UKismetMathLibrary::GetForwardVector(r);
	AddMovementInput(vec, 1.0f, true);

	float delta_seconds = UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
	FRotator new_rot = UKismetMathLibrary::RInterpTo(GetActorRotation(), r, delta_seconds, 2.0f);
	SetActorRotation(new_rot);

	

	FVector loc = GetActorLocation();
	FVector dest_loc = dest;
	loc.Z = dest_loc.Z;
	float dist = FVector::Distance(loc, dest_loc);
	if (dist >= 250.0f) {
		third_swimming_monster_anim->moving = true;
	}
	else {
		third_swimming_monster_anim->moving = false;

		move = false;
	}
}

void Athird_swimming_monster::PlayAttack(short target, const FVector& target_loc)
{
	FRotator r = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), target_loc);
	SetActorRotation(r);

	ChangeAnim(Emonster_anim::Attack);

	attack = true;
	this->Attack();
}

void Athird_swimming_monster::PlaySkill(short target, const FVector& target_loc)
{
	FRotator r = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), target_loc);
	SetActorRotation(r);

	ChangeAnim(Emonster_anim::Skill);

	skill = true;
	this->Skill();
}

void Athird_swimming_monster::PlayDeath()
{
	ChangeAnim(Emonster_anim::Death);
}
