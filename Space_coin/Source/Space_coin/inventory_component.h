// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "inventory_component.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACE_COIN_API Uinventory_component : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	Uinventory_component();

	TMap<int32, int32> inventory_map;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddtoInventory(int32 itemid, int32 quantity);
};
