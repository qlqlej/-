#include "spawn_point.h"
#include "monster.h"

Aspawn_point::Aspawn_point()
{
	PrimaryActorTick.bCanEverTick = true;

	spawn_enable = true;

	spawn_time = 1.f;
	spawn_duration = 0.f;

	infinity = false;  

	spawn_monster = nullptr;
}

void Aspawn_point::Respawn()
{
	if(!IsValid(spawn_type)) {
		return;
	}

	spawn_monster = nullptr;

	if (infinity) { 
		return;
	}

	spawn_enable = true; 
}

void Aspawn_point::BeginPlay()
{
	Super::BeginPlay();
	
}

void Aspawn_point::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsValid(spawn_type)) {
		spawn_duration += DeltaTime;

		if (spawn_duration >= spawn_time) {
			spawn_duration = 0.f;

			if (!infinity) {
				if (spawn_enable) {
					spawn_enable = false;

					FActorSpawnParameters params;
					params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

					spawn_monster = GetWorld()->SpawnActor<Amonster>(spawn_type, GetActorLocation(), GetActorRotation(), params);

					spawn_monster->SetSpawnPoint(this);

					for (Apatrol_point* point : patrol_point_array) {
						spawn_monster->AddPatrolPoint(point);
					}
				}
			}
			else { 
				FActorSpawnParameters params;
				params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
				spawn_monster = GetWorld()->SpawnActor<Amonster>(spawn_type, GetActorLocation(), GetActorRotation(), params);

				spawn_monster->SetSpawnPoint(this);

				for (Apatrol_point* point : patrol_point_array) {
					spawn_monster->AddPatrolPoint(point);
				}
			}

			
		}
	}
}

