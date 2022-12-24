#include "ui_player_hp.h"
#include "Components/Image.h"
#include "MyCharacter.h"
#include "MainGamePlayerController.h"

void Uui_player_hp::NativeConstruct()
{
	Super::NativeConstruct();

	material_instance = Cast<UMaterialInstance>(StaticLoadObject(UMaterialInstance::StaticClass(), NULL,
		TEXT("MaterialInstanceConstant'/Game/SpaceCoinContent/Material/CircleProgressBar/circle_progress_bar_mt_Inst.circle_progress_bar_mt_Inst'")));

	dynamic_material_instance = UMaterialInstanceDynamic::Create(material_instance, this);

	myCharacter = Cast<AMyCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	dynamic_material_instance->SetScalarParameterValue("percent", myCharacter->max_hp * 0.01f);  // player hp¶û ¿¬°á

	hp_image->SetBrushFromMaterial(dynamic_material_instance);
}

void Uui_player_hp::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	dynamic_material_instance->SetScalarParameterValue("percent", myCharacter->health / myCharacter->max_hp);  // player hp¶û ¿¬°á
	
	hp_image->SetBrushFromMaterial(dynamic_material_instance);	
}

