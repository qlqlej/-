// Fill out your copyright notice in the Description page of Project Settings.

#include "space_ship.h"
#include "MyCharacter.h"
#include "game_instance.h"
#include "weapon.h"
#include "Math/TransformNonVectorized.h"
#include "Engine/StaticMeshSocket.h"

// Sets default values
Aspace_ship::Aspace_ship()
{
	camera_boom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	camera_boom->SetupAttachment(RootComponent);
	camera_boom->SetRelativeLocation(FVector(-16.798845f, 100.0f, -3.130483f));
	camera_boom->SetRelativeRotation(FRotator(0.0f, -20.0f, 0.0f));
	camera_boom->TargetArmLength = 1000.0f;
	camera_boom->TargetOffset.Z = 100;
	camera_boom->bUsePawnControlRotation = false;
	camera_boom->bInheritRoll = false;
	camera_boom->bEnableCameraLag = true;
	camera_boom->bEnableCameraRotationLag = true;
	camera_boom->CameraLagSpeed = 1;
	camera_boom->CameraRotationLagSpeed = 5;
	camera_boom->CameraLagMaxDistance = 500;


	follow_camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	follow_camera->SetupAttachment(camera_boom, USpringArmComponent::SocketName);
	follow_camera->bUsePawnControlRotation = false;

	PrimaryActorTick.bCanEverTick = true;

}

void Aspace_ship::ProcessKeyPitch(float rate)
{
	if (!is_openlevel)
	{
		if (FMath::Abs(rate) > .2f)
			ProcessPitch(rate * 2.f);
	}
}

void Aspace_ship::ProcessKeyRoll(float rate)
{
	if (!is_openlevel)
	{
		ProcessRoll(rate);
	}
}

void Aspace_ship::ProcessKeyYaw(float rate)
{
	if (!is_openlevel)
	{
		if (FMath::Abs(rate) > .2f)
			ProcessYaw(rate * 2.f);
	}
}

void Aspace_ship::ProcessKeyThrottle(float rate)
{
	//
	if (!is_openlevel)
	{
		if (rate)
		{
			float deltaseconds = UGameplayStatics::GetWorldDeltaSeconds(GetWorld()) * 10;
			is_thorttle = true;
			const float current_acc = rate * acceleration;
			const float new_forward_speed = current_acc * deltaseconds;
			current_foward_speed = FMath::Clamp(current_foward_speed + new_forward_speed, min_speed, max_speed);
			speed = current_foward_speed;
			current_speed = speed * deltaseconds;
			const FVector local_move = FVector(speed * deltaseconds, 0.f, 0.f);
			AddActorLocalOffset(local_move, true);
			if (current_speed)
			{
				UGameplayStatics::PlayWorldCameraShake(GetWorld(), MyShake, GetActorLocation(), 0, 5000, 3, true);
			}
		}
		else
		{
			is_thorttle = false;
			current_speed = 0;
		}
	}
}

void Aspace_ship::ProcessMouseYInput(float value)
{
	if (!is_openlevel) 
	{
		ProcessPitch(value);
	}
}

void Aspace_ship::ProcessMouseXInput(float value)
{
	if (!is_openlevel)
	{
		ProcessYaw(value);
	}
}

void Aspace_ship::ProcessRoll(float value)
{
	b_intentional_roll = FMath::Abs(value) > 0.f;

	if (b_intentional_pitch && !b_intentional_roll) return;

	const float target_roll_speed = b_intentional_roll ?  (value * roll_rate_multiplier):(GetActorRotation().Roll * -0.5f);

	current_roll_speed = FMath::FInterpTo(current_roll_speed, target_roll_speed, GetWorld()->GetDeltaSeconds(), 2.f);
}

void Aspace_ship::ProcessPitch(float value)
{
	b_intentional_pitch = FMath::Abs(value) > 0.f;
	const float target_pitch_speed = value * ptich_rate_multiplier;
	current_pitch_speed = FMath::FInterpTo(current_pitch_speed, target_pitch_speed, GetWorld()->GetDeltaSeconds(), 2.f);
}

void Aspace_ship::ProcessYaw(float value)
{
	b_intentional_yaw = FMath::Abs(value) > 0.f;
	const float target_yaw_speed = value * yaw_rate_multiplier;
	current_yaw_speed = FMath::FInterpTo(current_yaw_speed, target_yaw_speed, GetWorld()->GetDeltaSeconds(), 2.f);
}


void Aspace_ship::EnterCharacter(AMyCharacter* character)
{
	
	owner_character = character;
	character->GetCharacterMovement()->StopMovementImmediately();
	character->SetActorEnableCollision(false);
	character->current_weapon->SetActorEnableCollision(false);
	character->current_weapon->SetActorHiddenInGame(true);
	character->GetCharacterMovement()->GravityScale = 0;
	character->SetActorHiddenInGame(true);
	if (character->Controller && !character->is_othercharacter)
	{
		FVector newtransfrom_location = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetActorTransform().GetLocation();
		FQuat newtransfrom_rotation = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetActorTransform().GetRotation();
		FTransform newtransform;
		newtransform.SetLocation(newtransfrom_location);
		newtransform.SetRotation(newtransfrom_rotation);
		newtransform.SetScale3D(FVector(1, 1, 1));
		follow_camera->SetWorldTransform(newtransform);
		character->Controller->Possess(this);
		FLatentActionInfo LatentInfo;
		LatentInfo.CallbackTarget = this;
		UKismetSystemLibrary::MoveComponentTo(follow_camera, FVector(0, 0, 0), FRotator(0, 0, 0), false, false, 1, false, EMoveComponentAction::Move, LatentInfo);
	}
	

}

void Aspace_ship::SendExit()
{
	UWorld* MyWorld = GetWorld();
	FString CurrentMapName = MyWorld->GetMapName();
	if (current_foward_speed < 5 && !(CurrentMapName == FString(TEXT("SpaceLevel"))))
	{
		CS_CHANGE_CHARACTER_PACKET infodata2;
		infodata2.sessionID = (owner_character)->mySessionID;
		infodata2.size = sizeof(CS_CHANGE_CHARACTER_PACKET);
		infodata2.type = CS_CHARACTER_CHANGE; // 캐릭터 변경시
		infodata2.character_type = CHARACTER_TYPE::HUMAN; // 전환할 타입
		if (owner_character->cur_weapon == 1)
		{
			infodata2.weapon_type = WEAPON_TYPE::GUN;
		}
		else
		{
			infodata2.weapon_type = WEAPON_TYPE::SWORD;
		}

		Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
		GameInstanceRef->mycharacter_type = CHARACTER_TYPE::HUMAN;
		GameInstanceRef->SendToChangeCharacterState(infodata2);
		Exit();
	}
}
void Aspace_ship::Exit()
{
	if (owner_character)
	{
		FHitResult HitResult;
		SetActorRotation(FRotator(0, GetActorRotation().Yaw, 0));
		follow_camera->SetWorldRotation(FRotator(0, GetActorRotation().Yaw, 0));
		FVector start = GetActorLocation();
		FVector end = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - 1000000);
		FCollisionQueryParams CollisionParams;
		GetWorld()->UWorld::LineTraceSingleByChannel(HitResult, start, end, ECollisionChannel::ECC_Visibility);
		
		owner_character->SetActorEnableCollision(true);
		owner_character->SetActorLocation(FVector(HitResult.Location.X, HitResult.Location.Y, HitResult.Location.Z + 100));
		owner_character->SetActorRotation(FRotator(0, follow_camera->GetComponentRotation().Yaw,0));
		owner_character->GetCharacterMovement()->GravityScale = 1;
		if (owner_character->InWater)
		{
			owner_character->waterZ = 1627;
			owner_character->GetCharacterMovement()->GetPhysicsVolume()->bWaterVolume = true;
			owner_character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Swimming);
		}
		if (Controller)
		{
			FVector newtransfrom_location = follow_camera->GetComponentTransform().GetLocation();
			FQuat newtransfrom_rotation = follow_camera->GetComponentTransform().GetRotation();
			FTransform newtransform;
			newtransform.SetLocation(newtransfrom_location);
			newtransform.SetRotation(newtransfrom_rotation);
			newtransform.SetScale3D(FVector(1, 1, 1));
			owner_character->follow_camera->SetWorldTransform(newtransform);

			Controller->Possess((owner_character));
			owner_character->enter = 0;
			if (owner_character->cur_weapon == 1)
			{
				owner_character->OnChangeGun();
			}
			else
			{
				owner_character->OnChangeSword();
			}

			FLatentActionInfo LatentInfo;
			LatentInfo.CallbackTarget = owner_character;
			UKismetSystemLibrary::MoveComponentTo(owner_character->follow_camera, FVector(0, 0, 0), FRotator(0, 0, 0), false, false, 1.0f, false, EMoveComponentAction::Move, LatentInfo);
			
			owner_character->LandEffect();

			FTimerHandle handle2;
			GetWorld()->GetTimerManager().SetTimer(handle2, this, &Aspace_ship::ExitUnHidden, 1.15f, false);
		}
	}
}

void Aspace_ship::ExitUnHidden()
{
	owner_character->current_weapon->SetActorEnableCollision(true);
	owner_character->SetActorHiddenInGame(false);
	owner_character->current_weapon->SetActorHiddenInGame(false);
	owner_character->StartAnim();
	owner_character = NULL;
	Destroy();
}

void Aspace_ship::UnOpenLevel()
{
	is_openlevel = false;
}

void Aspace_ship::BeginPlay()
{
	Super::BeginPlay();
}

void Aspace_ship::Tick(float DeltaTime)
{
	//가속 계산
	
	if (owner_character != NULL)
	{
		hp = owner_character->health;
	}
	FRotator DeltaRotation(0, 0, 0);
	DeltaRotation.Roll = current_roll_speed * DeltaTime;
	DeltaRotation.Yaw = current_yaw_speed * DeltaTime;
	DeltaRotation.Pitch = current_pitch_speed * DeltaTime;

	AddActorLocalRotation(DeltaRotation); 

	
	if (!is_thorttle&&speed > 0  )
	{
		float deltaseconds = UGameplayStatics::GetWorldDeltaSeconds(GetWorld()) * 10;
		const float new_forward_speed = 100 * deltaseconds;
		current_foward_speed = FMath::Clamp(current_foward_speed - new_forward_speed, min_speed, max_speed);
		speed = current_foward_speed;
;
		const FVector local_move = FVector(speed * deltaseconds, 0.f, 0.f);
		AddActorLocalOffset(local_move, true);
	}
	Super::Tick(DeltaTime);
}

void Aspace_ship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &Aspace_ship::ProcessMouseXInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &Aspace_ship::ProcessKeyRoll);
	PlayerInputComponent->BindAxis("LookUp", this, &Aspace_ship::ProcessMouseYInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &Aspace_ship::ProcessKeyPitch);
	PlayerInputComponent->BindAxis("MoveRight", this, &Aspace_ship::ProcessKeyYaw);
	PlayerInputComponent->BindAxis("Throttle", this, &Aspace_ship::ProcessKeyThrottle);

	PlayerInputComponent->BindAction("EnterVehicle",IE_Pressed, this, &Aspace_ship::SendExit);
}

