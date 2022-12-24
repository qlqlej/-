#include "trigger_sand_to_space.h"
#include <chrono>
#include "Components/BoxComponent.h"
#include "MainGamePlayerController.h"
#include "game_instance.h"

using namespace chrono;

AMainGamePlayerController* pcss;

Atrigger_sand_to_space::Atrigger_sand_to_space()
{
	PrimaryActorTick.bCanEverTick = true;

	volume_box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	volume_box->SetBoxExtent(FVector(50000.0f, 50000.0f, 5000.0f));
	volume_box->SetCollisionProfileName(TEXT("Trigger"));

	volume_box->OnComponentBeginOverlap.AddDynamic(this, &Atrigger_sand_to_space::OnOverlapBegin);
}

void Atrigger_sand_to_space::BeginPlay()
{
	Super::BeginPlay();

	pcss = Cast<AMainGamePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void Atrigger_sand_to_space::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void Atrigger_sand_to_space::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (OtherActor->GetClass()->IsChildOf(Aspace_ship::StaticClass())) {
			pcss->SetLoadingUI();

			CS_CHANGE_MAP_PACKET info_data;
			info_data.size = sizeof(CS_CHANGE_MAP_PACKET);
			info_data.type = CS_CHANGE_MAP;
			int id = pcss->ReturnSessionID();
			info_data.sessionID = id;
			info_data.map_type = MAP_TYPE::SPACE;
			info_data.client_time = static_cast<unsigned>(duration_cast<milliseconds>(high_resolution_clock::now().time_since_epoch()).count());
			Ugame_instance* GameInstanceRef = Cast<Ugame_instance>(UGameplayStatics::GetGameInstance(GetWorld()));
			GameInstanceRef->client->SendToChangeMap(info_data);
			GameInstanceRef->map_name = "SandPlanet";
		
			UGameplayStatics::OpenLevel(this, "SpaceLevel"); // ∏ ¿Ãµø
		}
	}

}
