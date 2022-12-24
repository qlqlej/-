#include "trigger_sand.h"
#include <chrono>
#include "Components/SphereComponent.h"
#include "MainGamePlayerController.h"
#include "game_instance.h"

using namespace chrono;

AMainGamePlayerController* pcs;

Atrigger_sand::Atrigger_sand()
{
	PrimaryActorTick.bCanEverTick = true;

	volume_sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	volume_sphere->InitSphereRadius(7000.0f);
	volume_sphere->SetCollisionProfileName(TEXT("Trigger"));

	volume_sphere->OnComponentBeginOverlap.AddDynamic(this, &Atrigger_sand::OnOverlapBegin);
}

void Atrigger_sand::BeginPlay()
{
	Super::BeginPlay();

	pcs = Cast<AMainGamePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void Atrigger_sand::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void Atrigger_sand::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		pcs->SetLoadingUI();

		CS_CHANGE_MAP_PACKET info_data;
		info_data.size = sizeof(CS_CHANGE_MAP_PACKET);
		info_data.type = CS_CHANGE_MAP;
		int id = pcs->ReturnSessionID();
		info_data.sessionID = id;
		info_data.map_type = MAP_TYPE::SAND;
		info_data.client_time = static_cast<unsigned>(duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count());
		Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
		GameInstanceRef->client->SendToChangeMap(info_data);
		GameInstanceRef->map_name = "SpaceLevel";
	
		UGameplayStatics::OpenLevel(this, "SandPlanet"); // ∏ ¿Ãµø
	}

}