// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "space_ship.h"
#include "Projectile.h"
#include "sniper_projectile.h"
#include "launcher_projectile.h"
#include "Animation/AnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Space_coinGameModeBase.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "missile.h"
#include "game_instance.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Client.h"
#include "weapon.h"
#include "sword_slash.h"
#include "player_name_ui.h"
#include "Components/WidgetComponent.h"
#include "target_maker.h"
#include "damage_indicator_ui.h"
#include "death_ui.h"
#include "EngineUtils.h"
#include "damage_number_ui.h"
#include "third_ice_monster.h"
#include "third_sand_monster.h"
#include "third_water_monster.h"
#include "Components/SpotLightComponent.h"


// Sets default values
AMyCharacter::AMyCharacter()
{

	GetMesh()->SetGenerateOverlapEvents(true);
	GetMesh()->CanCharacterStepUpOn = ECB_No;
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.0f;
	GetCharacterMovement()->AirControl = 0.2f;

	camera_boom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	camera_boom->SetupAttachment(RootComponent);
	camera_boom->SetRelativeLocation(FVector(0.0f, 100.0f, 0.0f));
	camera_boom->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	camera_boom->TargetArmLength = 400.0f;
	camera_boom->bUsePawnControlRotation = true;

	follow_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	follow_camera->SetupAttachment(camera_boom, USpringArmComponent::SocketName);
	follow_camera->bUsePawnControlRotation = false;

	scope_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("scope_camera"));
	scope_camera->SetupAttachment(camera_boom, USpringArmComponent::SocketName);
	scope_camera->bUsePawnControlRotation = false;

	hands_mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Character Mesh"));
	hands_mesh->SetOnlyOwnerSee(true);
	hands_mesh->SetupAttachment(camera_boom);
	hands_mesh->bCastDynamicShadow = false;
	hands_mesh->CastShadow = false;
	hands_mesh->AddRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	hands_mesh->AddRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	gun_mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun"));
	gun_mesh->SetOnlyOwnerSee(true);
	gun_mesh->bCastDynamicShadow = false;
	gun_mesh->CastShadow = false;

	fx_loc = CreateDefaultSubobject<UArrowComponent>(TEXT("Fx_loc"));
	fx_loc->SetupAttachment(RootComponent);

	spawn_missile = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Spawn_missile"));
	spawn_missile->SetupAttachment(RootComponent);
	

	muzzle_location = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle Location"));
	muzzle_location->SetupAttachment(gun_mesh);
	muzzle_location->SetRelativeLocation(FVector(0.2f, 21.0f, 0.0f));

	gun_offset = FVector(100.0f, 0.0f, 10.0f);


	missile_target_monster = NULL;

	dash_skill_cooldown = 0;
	launcher_skill_cooldown = 0;
	sniper_skill_cooldown = 0;
	missile_skill_cooldown = 0;
	ultimate_skill_cooldown = 0;
	defense_skill_cooldown = 0;
	slash_skill_cooldown = 0;
	
	slash_size = 10;

	money = 1000;
	ultimate_damage = 50;

	inventory_component = CreateDefaultSubobject<Uinventory_component>(TEXT("Inventory_component"));

	skill_defense = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("skill_defense"));
	skill_defense->AttachTo(RootComponent);
	skill_defense->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ConstructorHelpers::FObjectFinder<UStaticMesh> SphereAsset(TEXT("/Game/SpaceCoinContent/Resource/SkillEffect/ultimate/Shield"));
	if (SphereAsset.Succeeded())
	{
		skill_defense->SetStaticMesh(SphereAsset.Object);
		skill_defense->SetRelativeLocation(FVector(0, 0, -100));
		skill_defense->SetWorldScale3D(FVector(3, 3, 3));
	}
	skill_defense->SetHiddenInGame(true);
	healing_count = 0;

	ui_player_name = CreateDefaultSubobject<UWidgetComponent>(TEXT("player_name"));
	ui_player_name->AttachTo(GetCapsuleComponent());
	static ConstructorHelpers::FClassFinder<Uplayer_name_ui> PlayerNameUI(TEXT("WidgetBlueprint'/Game/SpaceCoinContent/UI/player_name_wb.player_name_wb_C'"));
	if (PlayerNameUI.Succeeded()) {
		ui_player_name->SetWidgetClass(PlayerNameUI.Class);
	}
	ui_player_name->SetWidgetSpace(EWidgetSpace::Screen);
	ui_player_name->SetDrawSize(FVector2D(90, 12));
	ui_player_name->SetRelativeLocation(FVector(0, 0, 120));

	water_light = CreateDefaultSubobject<USpotLightComponent>(TEXT("water_light"));
	water_light->AttachTo(GetMesh());
	water_light->IntensityUnits = ELightUnits::Candelas;
	water_light->Intensity = 500;
	water_light->AttenuationRadius = 2000;
	water_light->InnerConeAngle = 70;
	water_light->OuterConeAngle = 80;
	water_light->SetVisibility(false);
}


// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	gun_mesh->AttachToComponent(hands_mesh,
		FAttachmentTransformRules::SnapToTargetNotIncludingScale,
		TEXT(""));

	world = GetWorld();

	anim_instance = hands_mesh->GetAnimInstance();
	
	LerpTimeline.SetPlayRate(5.0f);

	follow_camera->SetActive(true);
	scope_camera->SetActive(false);
	dash_possible = true;
	sniper_possible = true;
	launcher_possible = true;
	missile_possible = true;
	ultimate_possible = true;
	defense_possible = true;
	slash_possible = true;

	ui_player_name_ui = Cast<Uplayer_name_ui>(ui_player_name->GetUserWidgetObject());
	
}

void AMyCharacter::BeHit()
{
	if (!is_respawning)
	{
		if (cur_weapon == 1 && !in_water_shoot) 
		{
			PlayAnimMontage(be_hit_anim, 1, NAME_None);
		}
		else if(cur_weapon == 0)
		{
			PlayAnimMontage(be_hit_sword_anim, 1, NAME_None);
		}
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), behit_sound, GetActorLocation());
		UGameplayStatics::PlayWorldCameraShake(GetWorld(), be_hit_camera_shake,GetActorLocation(),0,500);
		AddScreenDamage();
		EndAttacking();
	}
}

void AMyCharacter::OnDamaged()
{
	is_respawning = false;
}

void AMyCharacter::AddScreenDamage()
{
	AMainGamePlayerController* player_controller = Cast<AMainGamePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	screen_damage_ui_object = CreateWidget<Udamage_indicator_ui>(player_controller, screen_damage_class);
	screen_damage_ui_object->AddToViewport();
}

void AMyCharacter::AddScreenDeath()
{
	AMainGamePlayerController* player_controller = Cast<AMainGamePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	screen_death_ui_object = CreateWidget<Udeath_ui>(player_controller, screen_death_class);
	screen_death_ui_object->AddToViewport();
}

void AMyCharacter::StartAnim()
{
	if (!is_swimming) 
	{
		if (cur_weapon == 1)
		{
			PlayAnimMontage(gun_start_animation, 1, NAME_None);
		}
		else
		{
			PlayAnimMontage(sword_start_animation, 1, NAME_None);
		}
		EndAttacking();
	}
}





void AMyCharacter::SpendMoney(int32 pmoney)
{
	money -= pmoney;
}






// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (is_dashing_client && GetCharacterMovement()->IsFalling())
	{
		GetCharacterMovement()->FallingLateralFriction = 10;
	}
	else
		GetCharacterMovement()->FallingLateralFriction = 0;
	if(healing>0)
		Healing(DeltaTime);
	if (health <= 0) {
		is_respawning = true;
		health = max_hp;
		PlayAnimMontage(death_animation, 0.5f, NAME_None);
		AddScreenDeath();
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), death_sound, GetActorLocation());
		AMainGamePlayerController* player_controller = Cast<AMainGamePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		DisableInput(player_controller);
		FTimerHandle handle;
		GetWorld()->GetTimerManager().SetTimer(handle, this, &AMyCharacter::ReSpawn, 4.5f, false);
	}
	if (is_swimming && cur_weapon == 1 && !in_water_shoot)
	{
		GetMesh()->HideBoneByName(FName("weapon_r"), EPhysBodyOp::PBO_None);
	}

	if (is_target_locked)
	{
		if (target_monster->IsA(Athird_ice_monster::StaticClass()) || target_monster->IsA(Athird_sand_monster::StaticClass()) ||
			target_monster->IsA(Athird_water_monster::StaticClass()))
		{
			if (GetDistanceTo(target_monster) >= 2000)
			{
				is_target_locked = false;
				target_maker_object->Destroy();
				target_maker_object = NULL;
			}
			FRotator new_rotation;
			new_rotation = FRotator(
				FMath::RInterpTo(GetControlRotation(),
					UKismetMathLibrary::FindLookAtRotation(GetActorLocation(),
						FVector(target_monster->GetActorLocation().X, target_monster->GetActorLocation().Y, target_monster->GetActorLocation().Z  - (-0.03 * GetDistanceTo(target_monster) + 200) )),
					DeltaTime,
					10).Pitch,
				FMath::RInterpTo(GetControlRotation(),
					UKismetMathLibrary::FindLookAtRotation(GetActorLocation(),
						FVector(target_monster->GetActorLocation().X, target_monster->GetActorLocation().Y, target_monster->GetActorLocation().Z - (-0.03 * GetDistanceTo(target_monster) + 200))),
					DeltaTime,
					10).Yaw,
				GetControlRotation().Roll
			);
			GetController()->SetControlRotation(new_rotation);
		}
		else
		{
			if (GetDistanceTo(target_monster) >= 2000)
			{
				is_target_locked = false;
				target_maker_object->Destroy();
				target_maker_object = NULL;
			}
			FRotator new_rotation;
			new_rotation = FRotator(
				FMath::RInterpTo(GetControlRotation(),
					UKismetMathLibrary::FindLookAtRotation(GetActorLocation(),
						FVector(target_monster->GetActorLocation().X, target_monster->GetActorLocation().Y, target_monster->GetActorLocation().Z - 40)),
					DeltaTime,
					10).Pitch,
				FMath::RInterpTo(GetControlRotation(),
					UKismetMathLibrary::FindLookAtRotation(GetActorLocation(),
						FVector(target_monster->GetActorLocation().X, target_monster->GetActorLocation().Y, target_monster->GetActorLocation().Z - 40)),
					DeltaTime,
					10).Yaw,
				GetControlRotation().Roll
			);
			GetController()->SetControlRotation(new_rotation);
		}
	}

	if (is_swimming == true) {
		water_light->SetVisibility(true);
	}
	else {
		water_light->SetVisibility(false);
	}
}
void AMyCharacter::DieAnimaition()
{
	
	PlayAnimMontage(death_animation, 0.5f, NAME_None);
		
	
}
FString AMyCharacter::GetCurrentMapName()

{
	UWorld* MyWorld = GetWorld();
	FString CurrentMapName = MyWorld->GetMapName();

	return CurrentMapName;

}
void AMyCharacter::ReSpawn()
{ 
	if (is_swimming)
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		GetCharacterMovement()->GetPhysicsVolume()->bWaterVolume = false;
		is_swimming = false;
	}
	FString map_name = GetCurrentMapName();
	if (map_name == FString(TEXT("IcePlanet")))
	{
		SetActorLocation(FVector(78109.15625, 9469.367188, 1287.0354));
	}
	if (map_name == FString(TEXT("SandPlanet")))
	{
		SetActorLocation(FVector(-75957.445312, -31350.246094, 180.40097));
	}
	if (map_name == FString(TEXT("WaterPlanet")))
	{
		SetActorLocation(FVector(-28515.636719, -27109.085938, 3379.514404));
	}

	StartAnim();
	EndAttacking();
	EnableInputKey();
	health = max_hp;
	FTimerHandle handle;
	GetWorld()->GetTimerManager().SetTimer(handle, this, &AMyCharacter::OnDamaged, 3, false);
}

void AMyCharacter::EnableInputKey()
{
	AMainGamePlayerController* player_controller = Cast<AMainGamePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	EnableInput(player_controller);
}

unsigned int HashCode(const char* str)
{
	unsigned int hash = 0;
	while (*str)
	{
		hash = 65599 * hash + str[0];
		str++;
	}
	return hash ^ (hash >> 16);
}
// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &AMyCharacter::AddControllerYaw);
	PlayerInputComponent->BindAxis("LookUpCharacter", this, &AMyCharacter::AddControllerPitch);
	
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::SendJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMyCharacter::SendOnFire);

	PlayerInputComponent->BindAction("Gun", IE_Pressed, this, &AMyCharacter::SendOnChangeGun);
	PlayerInputComponent->BindAction("Sword", IE_Pressed, this, &AMyCharacter::SendOnChangeSword);

	PlayerInputComponent->BindAction("EnterVehicle", IE_Pressed, this, &AMyCharacter::SendEnterVehicle);

	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &AMyCharacter::SendDash);

	PlayerInputComponent->BindAction("Launcher", IE_Pressed, this, &AMyCharacter::SendOnLauncher);

	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &AMyCharacter::ToggleAiming);

	PlayerInputComponent->BindAction("Spawn", IE_Pressed, this, &AMyCharacter::SendSpawnShip);
	
	PlayerInputComponent->BindAction("SpawnMissile", IE_Pressed, this, &AMyCharacter::SendMissileLaunch);

	PlayerInputComponent->BindAction("SwordUltimate", IE_Pressed, this, &AMyCharacter::SendOnUltimate);
	
	PlayerInputComponent->BindAction("Defnese", IE_Pressed, this, &AMyCharacter::SendDefense);

	PlayerInputComponent->BindAction("Slash", IE_Pressed, this, &AMyCharacter::SendOnSlash);

	PlayerInputComponent->BindAction("Targeting", IE_Pressed, this, &AMyCharacter::Targeting);
}

void AMyCharacter::AddControllerYaw(float Axis)
{
	if (!is_target_locked && !is_othercharacter) 
	{
		APawn::AddControllerYawInput(Axis);
		if (GetVelocity().Size() == 0)
		{
			if (Axis > 0.3)
			{
				TurnRightLeft(true, false);
			}
			else
			{
				turn_right = false;
			}
			
			if (Axis < -0.3)
			{
				TurnRightLeft(false, true);
			}
			else
			{
				turn_left = false;
			}
		}
		else
		{
			TurnRightLeft(false, false);
		}
	}
}
void AMyCharacter::TurnRightLeft(bool is_turn_right, bool is_turn_left)
{
	turn_right = is_turn_right;
	turn_left = is_turn_left;
}
void AMyCharacter::HideGun()
{
	if (is_swimming)
	{
		in_water_shoot = false;
	}
	else
		GetMesh()->HideBoneByName(FName("weapon_r"), EPhysBodyOp::PBO_None);
}
void AMyCharacter::UnHideGun()
{
	if (is_swimming)
	{
		in_water_shoot = true;
		GetMesh()->UnHideBoneByName(FName("weapon_r"));
	}
	else
		GetMesh()->UnHideBoneByName(FName("weapon_r"));
}

void AMyCharacter::AddControllerPitch(float Axis)
{
	if (!is_target_locked) 
	{
		APawn::AddControllerPitchInput(Axis);
	}
}


void AMyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SpawnDefaultsInventory();
}

void AMyCharacter::MoveForward(float Axis)
{
	if (!enter)
	{
		if (is_swimming)
		{
			GetCharacterMovement()->RotationRate = FRotator(600,600,600);
			this->AddMovementInput(follow_camera->GetForwardVector(), Axis);
		}
		else
		{
			GetCharacterMovement()->RotationRate = FRotator(0, 0, 540);
			SetActorRotation(FRotator(0, GetActorRotation().Yaw, 0));
			FRotator rotation = this->GetControlRotation();
			FRotator yaw_rotation(0.0f, rotation.Yaw, 0.0f);

			FVector direction = FRotationMatrix(yaw_rotation).GetUnitAxis(EAxis::X);
			this->AddMovementInput(direction, Axis);
		}

	}
}

void AMyCharacter::MoveRight(float Axis)
{
	if (!enter && !is_swimming)
	{
		FRotator rotation = this->GetControlRotation();
		FRotator yaw_rotation(0.0f, rotation.Yaw, 0.0f);

		FVector direction = FRotationMatrix(yaw_rotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(direction, Axis);
	}
}

void AMyCharacter::SendOnChangeGun()
{
	if (during_attack == false) 
	{
		CS_CHANGE_CHARACTER_PACKET infodata2;
		infodata2.sessionID = mySessionID;
		infodata2.size = sizeof(CS_CHANGE_CHARACTER_PACKET);
	
		{
			infodata2.type = CS_WEAPON_CHANGE;
			infodata2.weapon_type = WEAPON_TYPE::GUN; 
		}

		Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
		GameInstanceRef->SendToChangeCharacterState(infodata2);
		OnChangeGun();
	}
}

void AMyCharacter::OnChangeGun()
{
	const int32 current_weapon_index = inventory.IndexOfByKey(current_weapon);

	Aweapon* next_weapon = inventory[0];
	EquipWeapon(next_weapon);
	cur_weapon = 1;
	GetMesh()->UnHideBoneByName(FName("weapon_r"));
	if (is_othercharacter == false)
	{
		Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
		GameInstanceRef->player_weapon_type = WEAPON_TYPE::GUN;
	}
}
void AMyCharacter::SendOnChangeSword()
{

	CS_CHANGE_CHARACTER_PACKET infodata2;
	infodata2.sessionID = mySessionID;
	infodata2.size = sizeof(CS_CHANGE_CHARACTER_PACKET);
	
	{
		infodata2.type = CS_WEAPON_CHANGE; 
		infodata2.weapon_type = WEAPON_TYPE::SWORD; 
	}

	Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GameInstanceRef->SendToChangeCharacterState(infodata2);
	OnChangeSword();
}
void AMyCharacter::OnChangeSword()
{
	const int32 current_weapon_index = inventory.IndexOfByKey(current_weapon);

	Aweapon* next_weapon = inventory[1];
	EquipWeapon(next_weapon);
	cur_weapon = 0;
	GetMesh()->HideBoneByName(FName("weapon_r"), EPhysBodyOp::PBO_None);
	if (is_othercharacter == false) 
	{
		Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
		GameInstanceRef->player_weapon_type = WEAPON_TYPE::SWORD;
	}
}
void AMyCharacter::SendOnFire()
{
	is_attack = true;
	if (cur_weapon)
	{
		if (is_aiming)
		{
			if (sniper_possible) {
				if (world != NULL)
				{
					if (sniper_bullet_count > 0) 
					{
						CS_ATTACK_SKILL_PACKET infodata;
						infodata.attack_skill_type = ATTACK_SKILL_TYPE::SNIPING;
						infodata.sessionID = mySessionID;
						infodata.size = sizeof(CS_ATTACK_SKILL_PACKET);
						infodata.type = CS_ATTACK_SKILL;
						infodata.cpitch = GetControlRotation().Pitch;
						infodata.cyaw = GetControlRotation().Yaw;
						infodata.croll = GetControlRotation().Roll;
					

						Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
						GameInstanceRef->SendToAttackSkill(infodata);
						spawn_rotation = GetControlRotation();

						OnFireSniper(spawn_rotation);

						sniper_bullet_count -= 1;
						if (sniper_bullet_count == 0)
						{
							sniper_skill_cooldown = 1;
							sniper_possible = false;
							SniperCooltimeLoop();

							FTimerHandle handle;
							GetWorld()->GetTimerManager().SetTimer(handle, FTimerDelegate::CreateLambda([&]()
								{
									is_aiming = !is_aiming;
									HideSniperOverlay();
									follow_camera->SetActive(true);
									scope_camera->SetActive(false);
									follow_camera->SetFieldOfView(90.f);
									GetMesh()->UnHideBoneByName(FName("weapon_r"));
								}), 0.2f, false);
						}
						
					}
					
				}
			}
		}
		else
		{
			if (world != NULL)
			{
				CS_ATTACK_SKILL_PACKET infodata;
				infodata.attack_skill_type = ATTACK_SKILL_TYPE::NORMAL;
				infodata.sessionID = mySessionID;
				infodata.size = sizeof(CS_ATTACK_SKILL_PACKET);
				infodata.type = CS_ATTACK_SKILL;
				infodata.cpitch = GetControlRotation().Pitch;
				infodata.cyaw = GetControlRotation().Yaw;
				infodata.croll = GetControlRotation().Roll;
			

				Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
				GameInstanceRef->SendToAttackSkill(infodata);
				spawn_rotation = GetControlRotation();
				OnFireGun(spawn_rotation);
			}
		}
	}
	else
	{
		if (!is_ultimate_anim && !is_defense_anim)
		{
			CS_ATTACK_SKILL_PACKET infodata;
			infodata.attack_skill_type = ATTACK_SKILL_TYPE::NORMAL;
			infodata.sessionID = mySessionID;
			infodata.size = sizeof(CS_ATTACK_SKILL_PACKET);
			infodata.type = CS_ATTACK_SKILL;
			infodata.cpitch = GetControlRotation().Pitch;
			infodata.cyaw = GetControlRotation().Yaw;
			infodata.croll = GetControlRotation().Roll;

			Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
			GameInstanceRef->SendToAttackSkill(infodata);
			Apublic_character::WeaponAttack();
		}
	}
}
void AMyCharacter::SniperCooltimeLoop()
{
	if (sniper_skill_cooldown > 0)
	{
		sniper_skill_cooldown -= 0.1;
		FTimerHandle handle;
		GetWorld()->GetTimerManager().SetTimer(handle, this, &AMyCharacter::SniperCooltimeLoop, 0.5f, false);
	}
	if (sniper_skill_cooldown <= 0)
	{
		sniper_possible = true;
	}
}
void AMyCharacter::ToggleAiming()
{
	if (cur_weapon != 0)
	{
		is_attack = true;
		if (!is_aiming)
		{
			if (sniper_possible)
			{
				is_aiming = !is_aiming;
				ShowSniperOverlay();
				follow_camera->SetActive(false);
				scope_camera->SetActive(true);
				scope_camera->SetFieldOfView(10.f);
				GetMesh()->HideBoneByName(FName("weapon_r"), EPhysBodyOp::PBO_None);
				sniper_bullet_count = 5;
			}
		}
		else
		{
			sniper_skill_cooldown = 1;
			sniper_possible = false;
			SniperCooltimeLoop();

			is_aiming = !is_aiming;
			HideSniperOverlay();
			follow_camera->SetActive(true);
			scope_camera->SetActive(false);
			follow_camera->SetFieldOfView(90.f);
			GetMesh()->UnHideBoneByName(FName("weapon_r"));
		}
	}
}
void AMyCharacter::OnFireGun(FRotator rot)
{
	spawn_location = muzzle_location->GetComponentLocation();

	FActorSpawnParameters actor_spawn_params;
	if (!is_swimming) {
		actor_spawn_params.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	}
	else
	{
		actor_spawn_params.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	}

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), fire_sound, spawn_location);
	projectile_object = GetWorld()->SpawnActor<AProjectile>(projectile,
		spawn_location, rot, actor_spawn_params);
	


	if (projectile_object) 
	{
		if (is_othercharacter == false)
			projectile_object->owner = true;
		else
			projectile_object->owner = false;

		projectile_object->damage = atk;
		projectile_object->critical_percent = critical_percent;
		projectile_object->speed = 10;
		projectile_object->session_id = mySessionID;
		projectile_object->hit_delegate.BindUObject(this, &AMyCharacter::AttackHP);
	}
	UNiagaraComponent* shoot_spark = UNiagaraFunctionLibrary::SpawnSystemAttached(spark, GetMesh(), TEXT("muzzlepoint"),
		FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, false, true,ENCPoolMethod::None,true);
	
	
	if (fire_animation)
	{
		PlayAnimMontage(fire_animation, 1, NAME_None);
	}
	
}
void AMyCharacter::OnFireSniper(FRotator rot)
{
	spawn_location = muzzle_location->GetComponentLocation();

	FActorSpawnParameters actor_spawn_params;
	if (!is_swimming) {
		actor_spawn_params.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	}
	else
	{
		actor_spawn_params.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	}
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), sniper_sound, spawn_location);

	sniper_projectile_object = world->SpawnActor<Asniper_projectile>(sniper_projectile,
		spawn_location, rot, actor_spawn_params);
	if (sniper_projectile_object) 
	{
		if (is_othercharacter == false)
			sniper_projectile_object->owner = true;
		else
			sniper_projectile_object->owner = false;

		sniper_projectile_object->damage = sniper_damage;
		sniper_projectile_object->session_id = mySessionID;
	}
	if (fire_animation)
	{
		PlayAnimMontage(fire_animation, 1, NAME_None);
	}
}

void AMyCharacter::SendOnSlash()
{
	is_attack = true;
	if (cur_weapon == 0 && slash_possible)
	{
		if (world != NULL)
		{

			CS_ATTACK_SKILL_PACKET infodata;
			infodata.attack_skill_type = ATTACK_SKILL_TYPE::SLASH;
			infodata.sessionID = mySessionID;
			infodata.size = sizeof(CS_ATTACK_SKILL_PACKET);
			infodata.type = CS_ATTACK_SKILL;
			infodata.cpitch = GetControlRotation().Pitch;
			infodata.cyaw = GetControlRotation().Yaw;
			infodata.croll = GetControlRotation().Roll;
			infodata.slash_size = slash_size;

			Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
			GameInstanceRef->SendToAttackSkill(infodata);
			
			spawn_rotation = GetControlRotation();
			SlashAnim(spawn_rotation);
		}
	}
}
void AMyCharacter::SlashAnim(FRotator rot)
{
	slash_possible = false;

	if (slash_animation)
	{
		PlayAnimMontage(slash_animation, 1, NAME_None);
	}
	is_slash_anim = true;
	slash_rot = rot;

	FTimerHandle handle;
	GetWorld()->GetTimerManager().SetTimer(handle, this, &AMyCharacter::OnSlash, 0.5f, false);
	FTimerHandle handle2;
	GetWorld()->GetTimerManager().SetTimer(handle2, this, &AMyCharacter::SlashAnimEnd, 1.266667f, false);
	
}
void AMyCharacter::OnSlash()
{
	spawn_location = current_weapon->GetActorLocation();
	FActorSpawnParameters actor_spawn_params;
	if (!is_swimming) {
		actor_spawn_params.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	}
	else
	{
		actor_spawn_params.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	}

	slash_object = world->SpawnActor<Asword_slash>(slash,
		spawn_location, slash_rot, actor_spawn_params);
	if (slash_object) {
		if (is_othercharacter == false)
			slash_object->owner = true;
		else
			slash_object->owner = false;

		slash_object->SetActorScale3D(FVector(slash_size, slash_size,2));
		slash_object->session_id = mySessionID;
		slash_object->damage = slash_damage;
	}
	slash_skill_cooldown = 1;
	SlashCooltimeLoop();
}
void AMyCharacter::SlashCooltimeLoop()
{
	if (slash_skill_cooldown > 0)
	{
		slash_skill_cooldown -= 0.1;
		FTimerHandle handle;
		GetWorld()->GetTimerManager().SetTimer(handle, this, &AMyCharacter::SlashCooltimeLoop, 0.8f, false);
	}
	if (slash_skill_cooldown <= 0)
	{
		slash_possible = true;
	}
}
void AMyCharacter::SlashAnimEnd()
{
	if (cur_weapon == 0)
	{
		EndAttacking();
	}
}

void AMyCharacter::SendOnLauncher()
{
	is_attack = true;
	if (cur_weapon)
	{
		if (launcher_possible)
		{
			if (world != NULL)
			{
				CS_ATTACK_SKILL_PACKET infodata;
				infodata.attack_skill_type = ATTACK_SKILL_TYPE::LAUNCHER;
				infodata.sessionID = mySessionID;
				infodata.size = sizeof(CS_ATTACK_SKILL_PACKET);
				infodata.type = CS_ATTACK_SKILL;
				infodata.cpitch = GetControlRotation().Pitch;
				infodata.cyaw = GetControlRotation().Yaw;
				infodata.croll = GetControlRotation().Roll;
				infodata.launcher_particle_radius = launcher_particle_radius;

				Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
				GameInstanceRef->SendToAttackSkill(infodata);
				spawn_rotation = GetControlRotation();

				OnLauncherProjectile(spawn_rotation);
				launcher_skill_cooldown = 1;
				launcher_possible = false;
				LauncherCooltimeLoop();

			}
		}
	}
}
void AMyCharacter::LauncherCooltimeLoop()
{
	if (launcher_skill_cooldown > 0)
	{
		launcher_skill_cooldown -= 0.1;
		FTimerHandle handle;
		GetWorld()->GetTimerManager().SetTimer(handle, this, &AMyCharacter::LauncherCooltimeLoop, 0.3f, false);
	}
	if (launcher_skill_cooldown <= 0)
	{
		launcher_possible = true;
	}
}
void AMyCharacter::OnLauncherProjectile(FRotator rot)
{
	spawn_location = muzzle_location->GetComponentLocation();

	FActorSpawnParameters actor_spawn_params;
	if (!is_swimming) {
		actor_spawn_params.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	}
	else
	{
		actor_spawn_params.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	}

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), launcher_sound, spawn_location);

	launcher_projectile_object = world->SpawnActor<Alauncher_projectile>(launcher_projectile,
		spawn_location, rot, actor_spawn_params);
	if (launcher_projectile_object) 
	{
		if (is_othercharacter == false)
			launcher_projectile_object->owner = true;
		else
			launcher_projectile_object->owner = false;
		launcher_projectile_object->radius = launcher_radius;
		launcher_projectile_object->explosion_particle_range = launcher_particle_radius;
		launcher_projectile_object->damage = launcher_damage;
		launcher_projectile_object->session_id = mySessionID;
	}
	if (fire_animation)
	{
		PlayAnimMontage(fire_animation, 1, NAME_None);
	}
}

void AMyCharacter::SendOnUltimate()
{
	is_attack = true;
	if (cur_weapon == 0)
	{
		if (ultimate_possible && !GetCharacterMovement()->IsFalling())
		{
			if (world != NULL)
			{
				CS_ATTACK_SKILL_PACKET infodata;
				infodata.attack_skill_type = ATTACK_SKILL_TYPE::ULTIMATE;
				infodata.sessionID = mySessionID;
				infodata.size = sizeof(CS_ATTACK_SKILL_PACKET);
				infodata.type = CS_ATTACK_SKILL;
				infodata.cpitch = GetControlRotation().Pitch;
				infodata.cyaw = GetControlRotation().Yaw;
				infodata.croll = GetControlRotation().Roll;

				Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
				GameInstanceRef->SendToAttackSkill(infodata);

				OnUltimate(GetActorForwardVector());

			}
		}
	}
}
void AMyCharacter::UltimateCooltimeLoop()
{
	if (ultimate_skill_cooldown > 0)
	{
		ultimate_skill_cooldown -= 0.1;
		FTimerHandle handle;
		GetWorld()->GetTimerManager().SetTimer(handle, this, &AMyCharacter::UltimateCooltimeLoop, 0.3f, false);
	}
	if (ultimate_skill_cooldown <= 0)
	{
		ultimate_possible = true;
	}
}
void AMyCharacter::OnUltimate(FVector vec)
{
	if (ultimate_montage)
	{
		ultimate_vec = vec;
		PlayAnimMontage(ultimate_montage, 1, NAME_None);
		is_ultimate_anim = true;
		SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + 300));
		FTimerHandle handle;
		GetWorld()->GetTimerManager().SetTimer(handle, this, &AMyCharacter::UltimateLaunch, 0.05, false);
		FTimerHandle handle2;
		GetWorld()->GetTimerManager().SetTimer(handle2, this, &AMyCharacter::EndUltimateAnim, 1, false);
	}
}
void AMyCharacter::UltimateLaunch()
{
	const FVector foward_dir = ultimate_vec;
	this->LaunchCharacter(foward_dir * 1500, false, false);
}
void AMyCharacter::EndUltimateAnim()
{
	if(cur_weapon == 0)
	{
		UltimateEffect();

		TArray<FHitResult> hit_actors;

		FVector start_trace = GetActorLocation();
		FVector end_trace = start_trace;
		end_trace.Z += 300.f;

		FCollisionShape collision_shape;
		collision_shape.ShapeType = ECollisionShape::Sphere;
		float radius = 500;
		collision_shape.SetSphere(radius);

		if (GetWorld()->SweepMultiByChannel(hit_actors, start_trace, end_trace, FQuat::FQuat(), ECC_WorldStatic, collision_shape))
		{
			for (auto actors : hit_actors)
			{
				class Amonster* monster_character = Cast<Amonster>(actors.Actor);
				if (monster_character != nullptr)
				{
					if (is_othercharacter == false)
					{
						AMainGamePlayerController* player_controller = Cast<AMainGamePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
						damage_number_ui_object = CreateWidget<Udamage_number_ui>(player_controller, damage_number_class);
						damage_number_ui_object->damage_amount = ultimate_damage;
						damage_number_ui_object->damage_target = monster_character;
						damage_number_ui_object->AddToViewport();

						CS_DAMAGE_MONSTER_PACKET infodata;
						infodata.damage = ultimate_damage;
						infodata.attack_sessionID = mySessionID;
						infodata.sessionID = monster_character->sessionID;
						infodata.size = sizeof(CS_DAMAGE_MONSTER_PACKET);
						infodata.type = CS_DAMAGE_MONSTER;
						infodata.monsterType = monster_character->monster_type;

						Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
						GameInstanceRef->client->SendToMonsterDamage(infodata);
					}
				}
				UStaticMeshComponent* sm = Cast<UStaticMeshComponent>((actors).Actor->GetRootComponent());

				if (sm)
				{
					sm->AddRadialImpulse(GetActorLocation(), 1000.f, 5000.f, ERadialImpulseFalloff::RIF_Linear, true);
				}
			}
		}

		is_ultimate_anim = false;
		EndAttacking();
	}
	ultimate_skill_cooldown = 1;
	ultimate_possible = false;
	UltimateCooltimeLoop();
}

void AMyCharacter::UltimateEffect()
{
	USkeletalMeshComponent* spawn_component = current_weapon->weapon_mesh;
	UNiagaraComponent* ultimate_effect = UNiagaraFunctionLibrary::SpawnSystemAttached(spawn_ultimate, spawn_component, TEXT("None"),
		FVector::ZeroVector, FRotator::ZeroRotator, FVector(1000,1000,1000), EAttachLocation::SnapToTarget, false, ENCPoolMethod::None, true, true);
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), ultimate_sound, GetActorLocation());
}

void AMyCharacter::LandEffect()
{
	UNiagaraFunctionLibrary::SpawnSystemAttached(bifrost, GetMesh(), TEXT("None"),
		FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::KeepRelativeOffset, true, true, ENCPoolMethod::None, true);
	if (!is_othercharacter)
	{
		AMainGamePlayerController* player_controller = Cast<AMainGamePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		DisableInput(player_controller);
		FTimerHandle handle;
		GetWorld()->GetTimerManager().SetTimer(handle, this, &AMyCharacter::EnableInputKey, 2, false);
	}
}

void AMyCharacter::SendEnterVehicle()
{
	TArray<AActor*> AllPlayers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), Aspace_ship::StaticClass(), AllPlayers);
	for (auto& ship : AllPlayers) {
		Aspace_ship* thisShip = Cast<Aspace_ship>(ship);
		if (thisShip->GetDistanceTo(this) < 500.f && thisShip->owner_session_id == mySessionID)
		{
			spaceship = thisShip;
			enter = 1;
			current_weapon->OnUnEquip();
			GetCharacterMovement()->GetPhysicsVolume()->bWaterVolume = false;
			GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
			thisShip->EnterCharacter(this);

			CS_CHANGE_CHARACTER_PACKET infodata2;
			infodata2.sessionID = mySessionID;
			infodata2.size = sizeof(CS_CHANGE_CHARACTER_PACKET);
			infodata2.type = CS_CHARACTER_CHANGE; // 캐릭터 변경시
			infodata2.character_type = CHARACTER_TYPE::SPACESHIP; // 전환할 타입


			Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
			GameInstanceRef->SendToChangeCharacterState(infodata2);
			GameInstanceRef->mycharacter_type = CHARACTER_TYPE::SPACESHIP;
			break;
		}
	
	}

	
	
}


void AMyCharacter::SendDash()
{
	if (dash_possible)
	{
		if (!(GetCharacterMovement()->IsFalling()) && !is_swimming)
		{
			CS_ATTACK_SKILL_PACKET infodata;
			infodata.attack_skill_type = ATTACK_SKILL_TYPE::DASHING;
			infodata.sessionID = mySessionID;
			infodata.size = sizeof(CS_ATTACK_SKILL_PACKET);
			infodata.type = CS_ATTACK_SKILL;

			Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
			GameInstanceRef->SendToAttackSkill(infodata);

			Dash(GetActorForwardVector());
			dash_skill_cooldown = 1;
			dash_possible = false;
			DashCooltimeLoop();
		}
	}
}
void AMyCharacter::Dash(FVector vec)
{
	is_dashing = true;
	is_dashing_client = true;
	const FVector foward_dir = vec;
	spawn_trail  = UNiagaraFunctionLibrary::SpawnSystemAttached(dash_trail, fx_loc,TEXT("None"),
		fx_loc->GetComponentLocation(), 
		FRotator(0,0, UKismetMathLibrary::MakeRotFromX(GetActorForwardVector()).Vector().Z), 
		EAttachLocation::KeepWorldPosition, false, true, ENCPoolMethod::None, true);
	this->LaunchCharacter(foward_dir * dash_distance, false , false);
	
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), dash_sound, spawn_location);

	camera_boom->bEnableCameraLag = true;
	camera_boom->CameraLagSpeed = 5;
	GetMesh()->SetVisibility(false);
	current_weapon->weapon_mesh->SetVisibility(false);
	FTimerHandle handle;
	GetWorld()->GetTimerManager().SetTimer(handle, FTimerDelegate::CreateLambda([&]()
		{
			is_dashing = false;
			is_dashing_client = false;
		
			GetMesh()->SetVisibility(true);
			current_weapon->weapon_mesh->SetVisibility(true);
		}), 0.4f, false);
	FTimerHandle handle2;
	GetWorld()->GetTimerManager().SetTimer(handle2, FTimerDelegate::CreateLambda([&]()
		{
			camera_boom->bEnableCameraLag = false;
		}), 0.4f, false);

	
}
void AMyCharacter::DashCooltimeLoop()
{
	if (dash_skill_cooldown > 0)
	{
		dash_skill_cooldown -= 0.1;
		FTimerHandle handle;
		GetWorld()->GetTimerManager().SetTimer(handle, this, &AMyCharacter::DashCooltimeLoop, 0.2f, false);
	}
	if (dash_skill_cooldown <= 0)
	{
		dash_possible = true;
	}


}

void AMyCharacter::SendDefense()
{
	if (cur_weapon == 0 && defense_possible)
	{
		CS_ATTACK_SKILL_PACKET infodata;
		infodata.attack_skill_type = ATTACK_SKILL_TYPE::DEFENSE;
		infodata.sessionID = mySessionID;
		infodata.size = sizeof(CS_ATTACK_SKILL_PACKET);
		infodata.type = CS_ATTACK_SKILL;
		infodata.cpitch = GetControlRotation().Pitch;
		infodata.cyaw = GetControlRotation().Yaw;
		infodata.croll = GetControlRotation().Roll;

		Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
		GameInstanceRef->SendToAttackSkill(infodata);

		defense_possible = false;
		DefenseAnim();
	}
}
void AMyCharacter::DefenseAnim()
{
	EndAttacking();
	PlayAnimMontage(defense_montage, 1, NAME_None);
	is_defense_anim = true;
	FTimerHandle handle;
	GetWorld()->GetTimerManager().SetTimer(handle, this, &AMyCharacter::Defense, 0.5f, false);
	FTimerHandle handle2;
	GetWorld()->GetTimerManager().SetTimer(handle2, this, &AMyCharacter::DefneseAnimEnd, 0.83f, false);
}
void AMyCharacter::Defense()
{
	if (cur_weapon == 0) 
	{
		skill_defense->SetHiddenInGame(false);
		is_defense = true;
		FTimerHandle handle;
		GetWorld()->GetTimerManager().SetTimer(handle, this, &AMyCharacter::DefenseOff, 6, false);
	}
}

void AMyCharacter::DefneseAnimEnd()
{
	is_defense_anim = false;
}
void AMyCharacter::DefenseOff()
{
	skill_defense->SetHiddenInGame(true);
	is_defense = false;
	EndAttacking();

	defense_skill_cooldown = 1;
	defense_possible = false;
	DefenseCooltimeLoop();
}
void AMyCharacter::DefenseCooltimeLoop()
{
	if (defense_skill_cooldown > 0)
	{
		defense_skill_cooldown -= 0.08;
		FTimerHandle handle;
		GetWorld()->GetTimerManager().SetTimer(handle, this, &AMyCharacter::DefenseCooltimeLoop, 0.3f, false);
	}
	if (defense_skill_cooldown <= 0)
	{
		defense_possible = true;
	}

}

void AMyCharacter::SendSpawnShip()
{
	bool was_added = false;
	Aspace_ship* findShip = NULL;
	TArray<AActor*> AllPlayers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), Aspace_ship::StaticClass(), AllPlayers);
	for (auto& player : AllPlayers) {
		Aspace_ship* thisShip = Cast<Aspace_ship>(player);
		if (mySessionID != thisShip->owner_session_id) continue;
		findShip = thisShip;
		was_added = true;
		break;
	}
	if (was_added)
	{
		if(findShip)
			findShip->Destroy();
	}
	FHitResult HitResult;
	FVector start = follow_camera->GetComponentLocation();
	FVector end = start + follow_camera->GetForwardVector() * 1000.f;
	FCollisionQueryParams CollisionParams;	
	bool spawn_able = !GetWorld()->UWorld::LineTraceSingleByChannel(HitResult, start, end,ECollisionChannel::ECC_Visibility);
	if (spawn_able) 
	{
		Aspace_ship* spawn_actor_ref = GetWorld()->SpawnActor<Aspace_ship>(ship_to_spawn, end, FRotator::ZeroRotator);
		if (spawn_actor_ref)
		{
			spawn_actor_ref->SetId(mySessionID);
			CS_SPAWN_SPACESHIP_PACKET infodata;
			infodata.x = end.X;
			infodata.y = end.Y;
			infodata.z = end.Z;
			infodata.pitch = 0;
			infodata.yaw = 0;
			infodata.roll = 0;
			infodata.size = sizeof(CS_SPAWN_SPACESHIP_PACKET);
			infodata.type = CS_SPAWN_SPACESHIP;
			infodata.owner_sessionID = mySessionID;

			Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
			GameInstanceRef->client->SendToSpawnShip(infodata);
		}
	}
	else
	{
		FVector hit_location = start;
		Aspace_ship* spawn_actor_ref = GetWorld()->SpawnActor<Aspace_ship>(ship_to_spawn, hit_location, FRotator::ZeroRotator);
		if (spawn_actor_ref)
		{
			spawn_actor_ref->SetId(mySessionID);
			CS_SPAWN_SPACESHIP_PACKET infodata;
			infodata.x = hit_location.X;
			infodata.y = hit_location.Y;
			infodata.z = hit_location.Z;
			infodata.pitch = 0;
			infodata.yaw = 0;
			infodata.roll = 0;
			infodata.size = sizeof(CS_SPAWN_SPACESHIP_PACKET);
			infodata.type = CS_SPAWN_SPACESHIP;
			infodata.owner_sessionID = mySessionID;

			Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
			GameInstanceRef->client->SendToSpawnShip(infodata);
		}
	}
}

void AMyCharacter::SendMissileLaunch()
{
	is_attack = true;

	if (missile_possible && cur_weapon == 1)
	{
		FindMonster();
		CS_ATTACK_SKILL_PACKET infodata;
		infodata.attack_skill_type = ATTACK_SKILL_TYPE::MISSILE;
		infodata.sessionID = mySessionID;
		infodata.size = sizeof(CS_ATTACK_SKILL_PACKET);
		infodata.type = CS_ATTACK_SKILL;
		infodata.cpitch = GetControlRotation().Pitch;
		infodata.cyaw = GetControlRotation().Yaw;
		infodata.croll = GetControlRotation().Roll;

		Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
		GameInstanceRef->SendToAttackSkill(infodata);
		missile_skill_cooldown = 1;
		missile_possible = false;
		MissileCooltimeLoop();
	}
}
void AMyCharacter::MissileCooltimeLoop()
{
	if (missile_skill_cooldown > 0)
	{
		missile_skill_cooldown -= 0.1;
		FTimerHandle handle;
		GetWorld()->GetTimerManager().SetTimer(handle, this, &AMyCharacter::MissileCooltimeLoop, 0.3f, false);
	}
	if (missile_skill_cooldown <= 0)
	{
		missile_possible = true;
	}
}
void AMyCharacter::SpawnMissile(Amonster* monster)
{
	if (missile_class != NULL)
	{
		class UWorld* const missile_spawn_world = GetWorld();

		if ((missile_spawn_world != NULL) && missile_target_monster)
		{
			FVector current_pos = spawn_missile->GetComponentLocation();

			FActorSpawnParameters actor_spawn_params;
			if (!is_swimming) {
				actor_spawn_params.SpawnCollisionHandlingOverride =
					ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
			}
			else
			{
				actor_spawn_params.SpawnCollisionHandlingOverride =
					ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			}
			actor_spawn_params.Owner = this;
			actor_spawn_params.Instigator = GetInstigator();
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), missile_sound, current_pos);
			class Amissile* fired_missile1 = missile_spawn_world->SpawnActor<Amissile>(missile_class, current_pos, FRotator(0, 0, 0), actor_spawn_params);
			class Amissile* fired_missile2 = missile_spawn_world->SpawnActor<Amissile>(missile_class, current_pos, FRotator(20, 0, 20), actor_spawn_params);
			class Amissile* fired_missile3 = missile_spawn_world->SpawnActor<Amissile>(missile_class, current_pos, FRotator(30, 0, 30), actor_spawn_params);
			class Amissile* fired_missile4 = missile_spawn_world->SpawnActor<Amissile>(missile_class, current_pos, FRotator(-20, 0, -20), actor_spawn_params);
			class Amissile* fired_missile5 = missile_spawn_world->SpawnActor<Amissile>(missile_class, current_pos, FRotator(-30, 0, -30), actor_spawn_params);

			if (is_othercharacter == false) 
			{
				fired_missile1->owner = true;
				fired_missile2->owner = true;
				fired_missile3->owner = true;
				fired_missile4->owner = true;
				fired_missile5->owner = true;
			}
			else
			{
				fired_missile1->owner = false;
				fired_missile2->owner = false;
				fired_missile3->owner = false;
				fired_missile4->owner = false;
				fired_missile5->owner = false;
			}
			fired_missile1->session_id = mySessionID;
			fired_missile2->session_id = mySessionID;
			fired_missile3->session_id = mySessionID;
			fired_missile4->session_id = mySessionID;
			fired_missile5->session_id = mySessionID;

			fired_missile1->damage = missile_damage;
			fired_missile2->damage = missile_damage;
			fired_missile3->damage = missile_damage;
			fired_missile4->damage = missile_damage;
			fired_missile5->damage = missile_damage;

			fired_missile1->LockOn(missile_target_monster);
			fired_missile2->LockOn(missile_target_monster);
			fired_missile3->LockOn(missile_target_monster);
			fired_missile4->LockOn(missile_target_monster);
			fired_missile5->LockOn(missile_target_monster);

			if (missile_skill_animation)
			{
				PlayAnimMontage(missile_skill_animation, 1, NAME_None);
			}
		}
	}
}

void AMyCharacter::FindMonster()
{
	class UWorld* const monster_in_world = GetWorld();

	if (monster_in_world)
	{
		float closet_distance = 100000000;
		for (TActorIterator<Amonster> ObstacleItr(monster_in_world); ObstacleItr; ++ObstacleItr)
		{
			FName PlayerTagName = FName(TEXT("Monster"));
			class Amonster* FoundMonster = *ObstacleItr;

			if (FoundMonster != nullptr)
			{
				if (FoundMonster->ActorHasTag(PlayerTagName))
				{
					if (closet_distance > (FoundMonster->GetActorLocation() - GetActorLocation()).Size())
					{
						closet_distance = (FoundMonster->GetActorLocation() - GetActorLocation()).Size();
						missile_target_monster = FoundMonster;
					}
				}
			}
		}
		SpawnMissile(missile_target_monster);
	}
}

void AMyCharacter::SendJump()
{
	if (world != NULL)
	{
		CS_ATTACK_SKILL_PACKET infodata;
		infodata.attack_skill_type = ATTACK_SKILL_TYPE::JUMP;
		infodata.sessionID = mySessionID;
		infodata.size = sizeof(CS_ATTACK_SKILL_PACKET);
		infodata.type = CS_ATTACK_SKILL;
		infodata.cpitch = GetControlRotation().Pitch;
		infodata.cyaw = GetControlRotation().Yaw;
		infodata.croll = GetControlRotation().Roll;
		infodata.jump_velocity = jump_velocity;

		Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
		GameInstanceRef->SendToAttackSkill(infodata);

		Jump();
		is_jumping = true;
	}
	
}

void AMyCharacter::SetVisibility()
{
	GetMesh()->SetVisibility(true);
}

void AMyCharacter::Healing(float del)
{
	if (GetVelocity().Size() == 0 && !is_attack)
	{
		healing_count += del;
		if (healing_count > 3.0f)				//3초동안 움직이지않고 공격하지 않을때
		{
			
			if ((health + healing) <= max_hp)
			{
				health += healing;
			}
			else
				healing_count = 0;
		}
	}
	else
	{
		is_attack = false;
		healing_count = 0;
	}
}

void AMyCharacter::AttackHP()
{
	if (health < max_hp) 
	{
		if ((health + atk_hp_up) < max_hp)
			health += atk_hp_up;
		else
			health = max_hp;
	}
}

void AMyCharacter::Targeting()
{
	if (!is_target_locked)
	{
		TArray<AActor*> IgnoreActors;
		FHitResult HitResult;
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesArray;
		ObjectTypesArray.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel2));
		UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), GetActorLocation(),
			(follow_camera->GetForwardVector() * 2000) + GetActorLocation(), 300,
			ObjectTypesArray,
			false,
			IgnoreActors,
			EDrawDebugTrace::Type::None,
			HitResult,
			true);
		if (HitResult.Actor.IsValid())
		{
			is_target_locked = true;
			target_monster = Cast<Amonster>(HitResult.Actor);
			FActorSpawnParameters actor_spawn_params;
			target_maker_object = world->SpawnActor<Atarget_maker>(target_maker,
				target_monster->GetActorLocation(), FRotator::ZeroRotator, actor_spawn_params);
			target_maker_object->AttachToActor(target_monster, FAttachmentTransformRules::SnapToTargetIncludingScale);
		}
		else
		{
			is_target_locked = false;
		}
	}
	else
	{
		is_target_locked = false;
		target_maker_object->Destroy();
		target_maker_object = NULL;
	}
}

FOnTimelineEvent AMyCharacter::interpFunction()
{
	AddMovementInput(GetActorForwardVector(),5000);
	float lerp = FMath::Lerp(90, 100, LerpTimeline.GetPlayRate());
	follow_camera->SetFieldOfView(lerp);
	return FOnTimelineEvent();
}

FOnTimelineEvent AMyCharacter::finishFunction()
{
	GetCharacterMovement()->MaxWalkSpeed = 5000;
	GetCharacterMovement()->MaxAcceleration = 5000;
	GetCharacterMovement()->RotationRate = FRotator(0, 0, 100000000.0f);
	GetMesh()->SetVisibility(true);
	return FOnTimelineEvent();
}

void AMyCharacter::Die(float killing_damage, FDamageEvent const& damage_event, AController* killer, AActor* damage_causer)
{
}

void AMyCharacter::SetCriticalPercent(int qunatity)
{
	if (qunatity > 0)
	{

		inventory_component->inventory_map.Add(0, qunatity);
		critical_percent = 2 + qunatity * 0.2;

	}
	else
		critical_percent = 2;
}
void AMyCharacter::AddCriticalPercent()
{
	if (inventory_component->inventory_map.Contains(0))
	{
		critical_percent += 0.2;
	}
}
void AMyCharacter::SetSpeed(int qunatity)
{
	if (qunatity > 0)
	{

		inventory_component->inventory_map.Add(1, qunatity);
		speed = 600 + qunatity * 5;
		GetCharacterMovement()->MaxWalkSpeed = 600 + qunatity * 5;

	}
	else
	{
		speed = 600;
	}
}
void AMyCharacter::AddSpeed()
{
	if (inventory_component->inventory_map.Contains(1))
	{
		speed += 5;
		GetCharacterMovement()->MaxWalkSpeed += 5;
	}
}

void AMyCharacter::SetAtk(int qunatity)
{
	if (qunatity > 0)
	{

		inventory_component->inventory_map.Add(2, qunatity);
		atk = 5 + qunatity * 0.3;

	}
	else
		atk = 5;
}
void AMyCharacter::AddAtk()
{
	if (inventory_component->inventory_map.Contains(2))
	{
		atk += 0.3;
	}
}
void AMyCharacter::SetMaxHp(int qunatity)
{
	if (qunatity > 0)
	{

		inventory_component->inventory_map.Add(3, qunatity);
		max_hp = 100 + qunatity * 10;

	}
	else
		max_hp = 100;

}
void AMyCharacter::AddMaxHp()
{
	if (inventory_component->inventory_map.Contains(3))
	{
		max_hp += 10;
	}
}
void AMyCharacter::SetHealing(int qunatity)
{
	if (qunatity > 0)
	{

		inventory_component->inventory_map.Add(4, qunatity);
		healing = qunatity * 0.005;

	}
	else
	{
		healing = 0;
	}

}
void AMyCharacter::AddHealing()
{
	if (inventory_component->inventory_map.Contains(4))
	{
		healing += 0.005;
	}
}
void AMyCharacter::SetSniperDamage(int qunatity)
{
	if (qunatity > 0)
	{

		inventory_component->inventory_map.Add(5, qunatity);
		sniper_damage = 40 + qunatity * 3;

	}
	else
		sniper_damage = 40;

}
void AMyCharacter::AddSniperDamge()
{
	if (inventory_component->inventory_map.Contains(5))
	{
		sniper_damage += 3;
	}
}
void AMyCharacter::SetAtkHpUp(int qunatity)
{
	if (qunatity > 0)
	{

		inventory_component->inventory_map.Add(6, qunatity);
		atk_hp_up =  qunatity * 1;

	}
	else
		atk_hp_up = 0;

}
void AMyCharacter::AddAtkHpUp()
{
	if (inventory_component->inventory_map.Contains(6))
	{
		atk_hp_up += 1;
	}
}
void AMyCharacter::SetLauncherDamage(int qunatity)
{
	if (qunatity > 0)
	{

		inventory_component->inventory_map.Add(7, qunatity);
		launcher_damage = 30 + qunatity * 1;

	}
	else
		launcher_damage = 30;
}
void AMyCharacter::AddLauncherDamage()
{
	if (inventory_component->inventory_map.Contains(7))
	{
		launcher_damage += 1;
	}
}
void AMyCharacter::SetLauncherRadius(int qunatity)
{
	if (qunatity > 0)
	{

		inventory_component->inventory_map.Add(8, qunatity);
		launcher_radius = 100 + qunatity * 30;
		launcher_particle_radius = 4 + qunatity * 0.2;
	}
	else
	{
		launcher_radius = 100;
		launcher_particle_radius = 4;
	}
}
void AMyCharacter::AddLauncherRadius()
{
	if (inventory_component->inventory_map.Contains(8))
	{
		launcher_radius += 30;
		launcher_particle_radius += 0.2;
	}
}
void AMyCharacter::SetJump(int qunatity)
{
	if (qunatity > 0)
	{

		inventory_component->inventory_map.Add(9, qunatity);
		jump_velocity = 600 + qunatity * 30;
		GetCharacterMovement()->JumpZVelocity = 600 + qunatity * 30;

	}
	else
	{
		jump_velocity = 600;
	}
}
void AMyCharacter::AddJump()
{
	if (inventory_component->inventory_map.Contains(9))
	{
		jump_velocity += 30;
		GetCharacterMovement()->JumpZVelocity += 30;
	}
}
void AMyCharacter::SetMissileDamage(int qunatity)
{
	if (qunatity > 0)
	{
		inventory_component->inventory_map.Add(10, qunatity);
		missile_damage = 15 + qunatity * 0.2;
	}
	else
	{
		missile_damage = 15;
	}
}
void AMyCharacter::AddMissileDamage()
{
	if (inventory_component->inventory_map.Contains(10))
	{
		missile_damage += 0.2;
	}
}
void AMyCharacter::SetSlashDamage(int qunatity)
{
	if (qunatity > 0)
	{
		inventory_component->inventory_map.Add(11, qunatity);
		slash_damage = 20 + qunatity * 1;
	}
	else
	{
		slash_damage = 20;
	}
}
void AMyCharacter::AddSlashDamage()
{
	if (inventory_component->inventory_map.Contains(11))
	{
		slash_damage += 1;
	}
}
void AMyCharacter::SetSlashSize(int qunatity)
{
	if (qunatity > 0)
	{
		inventory_component->inventory_map.Add(12, qunatity);
		slash_size = 4 + qunatity * 0.2;
	}
	else
	{
		slash_size = 4;
	}
}
void AMyCharacter::AddSlashSize()
{
	if (inventory_component->inventory_map.Contains(12))
	{
		slash_size += 0.2;
	}
}
void AMyCharacter::SetUltimateDamage(int qunatity)
{
	if (qunatity > 0)
	{
		inventory_component->inventory_map.Add(13, qunatity);
		ultimate_damage = 50 + qunatity * 2;
	}
	else
	{
		ultimate_damage = 50;
	}
}
void AMyCharacter::AddUltimateDamage()
{
	if (inventory_component->inventory_map.Contains(13))
	{
		ultimate_damage += 2;
	}
}

void AMyCharacter::EquipACoin()
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), coin_pickup_sound, GetActorLocation());
	EquipCoinAnim();
	EndAttacking();
	CS_GET_ITEM_PACKET infodata;
	infodata.item = DROP_ITEM::A_COIN;
	infodata.sessionID = mySessionID;
	infodata.size = sizeof(CS_GET_ITEM_PACKET);
	infodata.type = CS_GET_ITEM;

	Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GameInstanceRef->client->SendToDropCoin(infodata);

}
void AMyCharacter::EquipBCoin()
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), coin_pickup_sound, GetActorLocation());
	EquipCoinAnim();
	EndAttacking();
	CS_GET_ITEM_PACKET infodata;
	infodata.item = DROP_ITEM::B_COIN;
	infodata.sessionID = mySessionID;
	infodata.size = sizeof(CS_GET_ITEM_PACKET);
	infodata.type = CS_GET_ITEM;

	Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GameInstanceRef->client->SendToDropCoin(infodata);

}
void AMyCharacter::EquipCCoin()
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), coin_pickup_sound, GetActorLocation());
	EquipCoinAnim();
	CS_GET_ITEM_PACKET infodata;
	infodata.item = DROP_ITEM::C_COIN;
	infodata.sessionID = mySessionID;
	infodata.size = sizeof(CS_GET_ITEM_PACKET);
	infodata.type = CS_GET_ITEM;

	Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GameInstanceRef->client->SendToDropCoin(infodata);

}
void AMyCharacter::EquipCoinAnim()
{
	if (cur_weapon)
	{
		GetMesh()->HideBoneByName(FName("weapon_r"), EPhysBodyOp::PBO_None);
	}
	FTimerHandle handle;
	GetWorld()->GetTimerManager().SetTimer(handle, this, &AMyCharacter::EquipCoinAnimEnd, 1, false);
	
	PlayAnimMontage(coin_pickup_animation, 1, NAME_None);
}
void AMyCharacter::EquipCoinAnimEnd()
{
	if (cur_weapon)
	{
		GetMesh()->UnHideBoneByName(FName("weapon_r"));
	}
	else
		EndAttacking();
}