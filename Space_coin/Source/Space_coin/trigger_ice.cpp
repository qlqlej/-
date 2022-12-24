#include "trigger_ice.h"
#include <chrono>
#include "Components/SphereComponent.h"
#include "MainGamePlayerController.h"
#include "game_instance.h"

using namespace chrono;

AMainGamePlayerController* pci;

Atrigger_ice::Atrigger_ice()
{
	PrimaryActorTick.bCanEverTick = true;

	volume_sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	volume_sphere->InitSphereRadius(8000.0f);
	volume_sphere->SetCollisionProfileName(TEXT("Trigger"));

	volume_sphere->OnComponentBeginOverlap.AddDynamic(this, &Atrigger_ice::OnOverlapBegin);
}

void Atrigger_ice::BeginPlay()
{
	Super::BeginPlay();

	pci = Cast<AMainGamePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void Atrigger_ice::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void Atrigger_ice::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		pci->SetLoadingUI();

		CS_CHANGE_MAP_PACKET info_data;
		info_data.size = sizeof(CS_CHANGE_MAP_PACKET);
		info_data.type = CS_CHANGE_MAP;
		int id = pci->ReturnSessionID();
		info_data.sessionID = id;
		info_data.map_type = MAP_TYPE::ICE;
		info_data.client_time = static_cast<unsigned>(duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count());
		Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
		GameInstanceRef->client->SendToChangeMap(info_data);
		GameInstanceRef->map_name = "SpaceLevel";
	
		UGameplayStatics::OpenLevel(this, "IcePlanet"); // ∏ ¿Ãµø
	}
}

