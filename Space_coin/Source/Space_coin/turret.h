// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "turret.generated.h"

UCLASS()
class SPACE_COIN_API Aturret : public AActor
{
	GENERATED_BODY()

private:
	FTimerHandle missile_handle;

public:

	Aturret(const FObjectInitializer& ObjectInitializer);

protected:

	virtual void BeginPlay() override;

public:

	void InitMissileLaunch();
	void SpawnMissile();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
		class UBoxComponent* collision_comp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
		class UStaticMeshComponent* turret_mesh;

	UPROPERTY(EditDefaultsOnly, Category = "Turret Projectiles")
		TSubclassOf<class Amissile> missile_class;

};
