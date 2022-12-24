#include "first_sand_monster.h"
#include "first_sand_monster_anim.h"
#include "first_monster_ai_controller.h"
#include "ui_player_hp.h"
#include "ui_monster_hp.h"
#include "Components/WidgetComponent.h"

Afirst_sand_monster::Afirst_sand_monster()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("SkeletalMesh'/Game/ParagonMinions/Characters/Buff/Buff_Red/Meshes/Buff_Red'"));

	if (MeshAsset.Succeeded()) {
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FClassFinder<Ufirst_sand_monster_anim> AnimAsset(TEXT("AnimBlueprint'/Game/SpaceCoinContent/Monster/first_sand_monster_anim_bp'"));

	if (AnimAsset.Succeeded()) {
		GetMesh()->SetAnimInstanceClass(AnimAsset.Class);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AnimMontage(TEXT("AnimMontage'/Game/ParagonMinions/Characters/Buff/Buff_Red/Animations/Hit_Front_Montage'"));

	if (AnimMontage.Succeeded()) {
		hit_montage = AnimMontage.Object;
	}

	GetCapsuleComponent()->SetCapsuleHalfHeight(110.0f);
	GetCapsuleComponent()->SetCapsuleRadius(50.0f);

	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -110.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	weapon_box_r = CreateDefaultSubobject<UBoxComponent>(TEXT("weapon_box_r"));
	weapon_box_r->CanCharacterStepUpOn = ECB_No;
	weapon_box_r->SetCollisionProfileName(TEXT("MonsterAttack"));
	weapon_box_r->SetupAttachment(GetMesh(), TEXT("thumb_01_r_mid"));
	weapon_box_r->SetBoxExtent(FVector(17.f, 17.f, 17.f));
	weapon_box_r->OnComponentBeginOverlap.AddDynamic(this, &Afirst_sand_monster::WeaponBeginOverlap);
	weapon_box_r->OnComponentEndOverlap.AddDynamic(this, &Afirst_sand_monster::WeaponEndOverlap);
	weapon_box_r->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	weapon_box_l = CreateDefaultSubobject<UBoxComponent>(TEXT("weapon_box_l"));
	weapon_box_l->CanCharacterStepUpOn = ECB_No;
	weapon_box_l->SetCollisionProfileName(TEXT("MonsterAttack"));
	weapon_box_l->SetupAttachment(GetMesh(), TEXT("thumb_01_l_mid"));
	weapon_box_l->SetBoxExtent(FVector(17.f, 17.f, 17.f));
	weapon_box_l->OnComponentBeginOverlap.AddDynamic(this, &Afirst_sand_monster::WeaponBeginOverlap);
	weapon_box_l->OnComponentEndOverlap.AddDynamic(this, &Afirst_sand_monster::WeaponEndOverlap);
	weapon_box_l->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	monster_hp = CreateDefaultSubobject<UWidgetComponent>(TEXT("monster_hp"));
	monster_hp->AttachTo(GetCapsuleComponent());
	static ConstructorHelpers::FClassFinder<Uui_monster_hp> MonsterHPUI(TEXT("WidgetBlueprint'/Game/SpaceCoinContent/UI/monster_hp_wb.monster_hp_wb_C'"));
	if (MonsterHPUI.Succeeded()) {
		monster_hp->SetWidgetClass(MonsterHPUI.Class);
	}
	monster_hp->SetWidgetSpace(EWidgetSpace::Screen);
	monster_hp->SetDrawSize(FVector2D(80, 15));
	monster_hp->SetRelativeLocation(FVector(0.0f, 0.0f, 140.0f));

	monster_name = TEXT("first_sand_monster");

	monster_type = MONSTER_TYPE::F_SAND;
}

void Afirst_sand_monster::BeginPlay()
{
	Super::BeginPlay();

	first_sand_monster_anim = Cast<Ufirst_sand_monster_anim>(GetMesh()->GetAnimInstance());

	monster_hp_ui = Cast<Uui_monster_hp>(monster_hp->GetUserWidgetObject());
	monster_hp_ui->SetOwnerMonster(this);
}

void Afirst_sand_monster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UCharacterMovementComponent* movement = GetCharacterMovement();

	if (first_sand_monster_anim->moving == true && movement->Velocity.Size() <= 0.f && attack == false) {
		ChangeAnim(Emonster_anim::Idle);
	}

}

void Afirst_sand_monster::ChangeAnim(Emonster_anim anim)
{
	first_sand_monster_anim->ChangeAnim(anim);
}

void Afirst_sand_monster::MoveToLocation(const FVector& dest, float yaw)
{
	Afirst_monster_ai_controller* controller = Cast<Afirst_monster_ai_controller>(GetController());

	controller->SetControlRotation(FRotator(0.f, yaw, 0.f));

	FVector monster_loc = this->GetActorLocation();
	FVector move_loc = dest;
	move_loc.Z = monster_loc.Z;

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(controller, move_loc);

	monster_loc.Z = 0.f;
	move_loc.Z = 0.f;

	float dist = FVector::Distance(monster_loc, move_loc);
	if (dist >= 250.0f) {
		first_sand_monster_anim->moving = true;
	}
	else {
		first_sand_monster_anim->moving = false;

		ChangeAnim(Emonster_anim::Idle);

		controller->StopMovement();
	}
}

void Afirst_sand_monster::PlayAttack(short target, const FVector& target_loc)
{
	Afirst_monster_ai_controller* controller = Cast<Afirst_monster_ai_controller>(GetController());

	FVector dir = target_loc - this->GetActorLocation();
	dir.Normalize();
	this->SetActorRotation(FRotator(0.f, dir.Rotation().Yaw, 0.f));

	this->ChangeAnim(Emonster_anim::Attack);

	attack = true;
	this->Attack(); 
}

void Afirst_sand_monster::PlayHit()
{

	if (hit_montage) {
		this->PlayAnimMontage(hit_montage, 1.0f, NAME_None);
	}

	hit = true;
	this->Hit();
}

void Afirst_sand_monster::PlayDeath()
{
	ChangeAnim(Emonster_anim::Death);

	death = true;
	this->Death();
}

void Afirst_sand_monster::EnableWeaponCollision(bool enable)
{
	if (enable) {
		weapon_box_r->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		weapon_box_l->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
	else {
		weapon_box_r->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		weapon_box_l->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void Afirst_sand_monster::WeaponBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/*class AMyCharacter* player_character = Cast<AMyCharacter>(OtherActor);
	if (player_character != nullptr)
	{
		TArray<AActor*> AllPlayers;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMyCharacter::StaticClass(), AllPlayers);
		for (auto& player : AllPlayers) {
			AMyCharacter* thisPlayer = Cast<AMyCharacter>(player);
			AMyCharacter* overlapPlayer = Cast<AMyCharacter>(OtherActor);
			if (overlapPlayer->mySessionID != thisPlayer->mySessionID) continue;
			if (IsAttack() == true) {
				overlapPlayer->health -= this->monster_state.attack;
			}
		}
	}*/
	
}

void Afirst_sand_monster::WeaponEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

