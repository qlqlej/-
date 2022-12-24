

#include "a_coin.h"
#include "MyCharacter.h"

Aa_coin::Aa_coin()
{
 
	PrimaryActorTick.bCanEverTick = true;
	collision_comp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
}


void Aa_coin::BeginPlay()
{
	Super::BeginPlay();
	collision_comp->OnComponentBeginOverlap.AddDynamic(this, &Aa_coin::OnOverlapBegin);
}


void Aa_coin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void Aa_coin::OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& hitResult)
{
	class AMyCharacter* player_character = Cast<AMyCharacter>(otherActor);
	if (player_character != nullptr && player_character->mySessionID == session_id)
	{
		SetActorEnableCollision(false);
		player_character->EquipACoin();
		if (this->IsValidLowLevel())
			Destroy();
	}

}
