// Fill out your copyright notice in the Description page of Project Settings.


#include "target_maker.h"
#include "Components/WidgetComponent.h"

Atarget_maker::Atarget_maker()
{
	targeting = CreateDefaultSubobject<UWidgetComponent>(TEXT("targeting"));
	static ConstructorHelpers::FClassFinder<Utargeting_ui> TargetingUI(TEXT("WidgetBlueprint'/Game/SpaceCoinContent/UI/targeting_wb.targeting_wb_C'"));
	if (TargetingUI.Succeeded()) {
		targeting->SetWidgetClass(TargetingUI.Class);
	}
	targeting->SetWidgetSpace(EWidgetSpace::Screen);
	targeting->SetDrawSize(FVector2D(64, 64));

}

void Atarget_maker::BeginPlay()
{
	Super::BeginPlay();
	targeting_ui = Cast<Utargeting_ui>(targeting->GetUserWidgetObject());
}