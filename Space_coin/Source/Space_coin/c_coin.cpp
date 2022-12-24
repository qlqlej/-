// Fill out your copyright notice in the Description page of Project Settings.


#include "c_coin.h"
#include "MyCharacter.h"
// Sets default values
Ac_coin::Ac_coin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	collision_comp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));

}

// Called when the game starts or when spawned
void Ac_coin::BeginPlay()
{
	Super::BeginPlay();
	collision_comp->OnComponentBeginOverlap.AddDynamic(this, &Ac_coin::OnOverlapBegin);

}

// Called every frame
void Ac_coin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void Ac_coin::OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& hitResult)
{
	class AMyCharacter* player_character = Cast<AMyCharacter>(otherActor);
	if (player_character != nullptr && player_character->mySessionID == session_id)
	{
		SetActorEnableCollision(false);
		player_character->EquipCCoin();
		if (this->IsValidLowLevel())
			Destroy();
	}

}