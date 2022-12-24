


#include "b_coin.h"
#include "MyCharacter.h"
// Sets default values
Ab_coin::Ab_coin()
{
	PrimaryActorTick.bCanEverTick = true;
	collision_comp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
}

// Called when the game starts or when spawned
void Ab_coin::BeginPlay()
{
	Super::BeginPlay();
	collision_comp->OnComponentBeginOverlap.AddDynamic(this, &Ab_coin::OnOverlapBegin);
}

// Called every frame
void Ab_coin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void Ab_coin::OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& hitResult)
{
	class AMyCharacter* player_character = Cast<AMyCharacter>(otherActor);
	if (player_character != nullptr && player_character->mySessionID == session_id)
	{
		SetActorEnableCollision(false);
		player_character->EquipBCoin();
		if (this->IsValidLowLevel())
			Destroy();
	}

}