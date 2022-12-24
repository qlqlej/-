#include "fog_water.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "MyCharacter.h"
#include "game_instance.h"

Afog_water::Afog_water()
{
	PrimaryActorTick.bCanEverTick = true;

	fog = CreateDefaultSubobject<UExponentialHeightFogComponent>(TEXT("fog"));
	fog->SetFogDensity(0.1);
	fog->SetStartDistance(50000.0);

	fog->SetVolumetricFog(true);
	fog->SetVolumetricFogScatteringDistribution(0.001);
	fog->SetVolumetricFogExtinctionScale(0.2);
}

void Afog_water::BeginPlay()
{
	Super::BeginPlay();
	
}

void Afog_water::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
	switch (GameInstanceRef->mycharacter_type)
	{
	case CHARACTER_TYPE::HUMAN:
	{
		AMyCharacter* thisPlayer = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if (thisPlayer->is_swimming == true && thisPlayer->GetActorLocation().Z < 1300.0) {  
			fog->SetVisibility(false);
		}
		else {
			fog->SetVisibility(true);
		}
		break;
	}
	case CHARACTER_TYPE::SPACESHIP:
	{
		fog->SetVisibility(true);
		break;
	}
	default:
		break;
	}
}

