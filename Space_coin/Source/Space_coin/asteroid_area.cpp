#include "asteroid_area.h"
#include "asteroid_one.h"
#include "asteroid_two.h"
#include "asteroid_three.h"
#include "Kismet/KismetMathLibrary.h"

Aasteroid_area::Aasteroid_area()
{
	PrimaryActorTick.bCanEverTick = true;

	box_collision = CreateDefaultSubobject<UBoxComponent>(TEXT("box_collision"));


	box_collision->SetBoxExtent(FVector(50000.f, 50000.f, 25000.f));

	box_collision->SetCollisionProfileName(TEXT("NoCollision"));

	asteroid_start = false;

	UObject* spawn_asteroid_one = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("Blueprint'/Game/SpaceCoinContent/Blueprint/Asteroid/asteroid_one_bp.asteroid_one_bp'")));
	bp_asteroid_one = Cast<UBlueprint>(spawn_asteroid_one);
	if (!spawn_asteroid_one) {
		return;
	}

	UClass* spawn_class_asteroid_one = spawn_asteroid_one->StaticClass();
	if (spawn_class_asteroid_one == NULL) {
		return;
	}

	UObject* spawn_asteroid_two = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("Blueprint'/Game/SpaceCoinContent/Blueprint/Asteroid/asteroid_two_bp.asteroid_two_bp'")));
	bp_asteroid_two = Cast<UBlueprint>(spawn_asteroid_two);
	if (!spawn_asteroid_two) {
		return;
	}

	UClass* spawn_class_asteroid_two = spawn_asteroid_two->StaticClass();
	if (spawn_class_asteroid_two == NULL) {
		return;
	}

	UObject* spawn_asteroid_three = Cast<UObject>(StaticLoadObject(UObject::StaticClass(), NULL, TEXT("Blueprint'/Game/SpaceCoinContent/Blueprint/Asteroid/asteroid_three_bp.asteroid_three_bp'")));
	bp_asteroid_three = Cast<UBlueprint>(spawn_asteroid_three);
	if (!spawn_asteroid_three) {
		return;
	}

	UClass* spawn_class_asteroid_three = spawn_asteroid_three->StaticClass();
	if (spawn_class_asteroid_three == NULL) {
		return;
	}

}

void Aasteroid_area::BeginPlay()
{
	Super::BeginPlay();
}

void Aasteroid_area::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FTimerHandle wait_handle;
	float wait_time = 10.f;
	GetWorld()->GetTimerManager().SetTimer(wait_handle, FTimerDelegate::CreateLambda([&]() {
		if (asteroid_start == false) {
			asteroid_start = true;

			FVector spawn_location = UKismetMathLibrary::RandomPointInBoundingBox(box_collision->GetRelativeLocation(), box_collision->GetScaledBoxExtent());
			FTransform spawn_transform = FTransform(spawn_location);
			FActorSpawnParameters params;
			params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			for (int i = 0; i < 50; ++i) {
				switch (FMath::RandRange(0, 3))
				{
				case 1:
					spawn_asteroid = GetWorld()->SpawnActor<Aasteroid_one>(bp_asteroid_one->GeneratedClass, spawn_transform, params);
					spawn_asteroid->SetLifeSpan(20.f);
					break;
				case 2:
					spawn_asteroid = GetWorld()->SpawnActor<Aasteroid_two>(bp_asteroid_two->GeneratedClass, spawn_transform, params);
					spawn_asteroid->SetLifeSpan(20.f);
					break;
				case 3:
					spawn_asteroid = GetWorld()->SpawnActor<Aasteroid_three>(bp_asteroid_three->GeneratedClass, spawn_transform, params);
					spawn_asteroid->SetLifeSpan(20.f);
					break;
				default:
					break;
				}
			}
		}
		}), wait_time, false);
}

