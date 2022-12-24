#include "trigger_water.h"
#include <chrono>
#include "Components/SphereComponent.h"
#include "MainGamePlayerController.h"
#include "game_instance.h"

using namespace chrono;

AMainGamePlayerController* pcw;

Atrigger_water::Atrigger_water()
{
	PrimaryActorTick.bCanEverTick = true;

	volume_sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	volume_sphere->InitSphereRadius(14000.0f);
	volume_sphere->SetCollisionProfileName(TEXT("Trigger"));

	volume_sphere->OnComponentBeginOverlap.AddDynamic(this, &Atrigger_water::OnOverlapBegin);
}

void Atrigger_water::BeginPlay()
{
	Super::BeginPlay();

	pcw = Cast<AMainGamePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void Atrigger_water::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void Atrigger_water::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		pcw->SetLoadingUI();

		CS_CHANGE_MAP_PACKET info_data;
		info_data.size = sizeof(CS_CHANGE_MAP_PACKET);
		info_data.type = CS_CHANGE_MAP;
		int id = pcw->ReturnSessionID();
		info_data.sessionID = id;
		info_data.map_type = MAP_TYPE::WATER;
		info_data.client_time = static_cast<unsigned>(duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count());
		Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
		GameInstanceRef->client->SendToChangeMap(info_data);
		GameInstanceRef->map_name = "SpaceLevel";
	
		UGameplayStatics::OpenLevel(this, "WaterPlanet");
	}
}

