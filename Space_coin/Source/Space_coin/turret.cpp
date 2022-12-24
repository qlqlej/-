// Fill out your copyright notice in the Description page of Project Settings.


#include "turret.h"
#include "missile.h"
#include "Engine.h"

Aturret::Aturret(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	collision_comp = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("CollisionComp"));
	RootComponent = collision_comp;

	turret_mesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("TurretMesh"));
	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Game/StarterContent/Shapes/Shape_Tube"));
	turret_mesh->SetStaticMesh(MeshObj.Object);
	turret_mesh->SetupAttachment(RootComponent);
}

void Aturret::BeginPlay()
{
	Super::BeginPlay();
	InitMissileLaunch();
}

#pragma region Missile Logic
void Aturret::InitMissileLaunch()
{
	GetWorldTimerManager().SetTimer(missile_handle, this, &Aturret::SpawnMissile, 3.f, true);
}

void Aturret::SpawnMissile()
{
	if (missile_class != NULL)
	{
		class UWorld* const world = GetWorld();

		if (world != NULL)
		{
			FVector current_pos = GetActorLocation();
			FRotator current_rot = FRotator(0, 0, 0);

			FActorSpawnParameters spawnParams;
			spawnParams.Owner = this;
			spawnParams.Instigator = GetInstigator();

			class Amissile* fired_missile = world->SpawnActor<Amissile>(missile_class, current_pos, current_rot, spawnParams);

			if (fired_missile != nullptr)
			{
				FRotator meshRot = fired_missile->missile_mesh->GetComponentRotation();
				meshRot.Roll = 0.f;
				meshRot.Pitch = -90.f;
				meshRot.Yaw = 0.f;
				fired_missile->missile_mesh->SetRelativeRotation(meshRot);
			}
		}
	}
}
#pragma endregion

