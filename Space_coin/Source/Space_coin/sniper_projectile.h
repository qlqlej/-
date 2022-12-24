// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "sniper_projectile.generated.h"

UCLASS()
class SPACE_COIN_API Asniper_projectile : public AActor
{
	GENERATED_BODY()
	
public:	
	int session_id = -1;

	bool owner;

	Asniper_projectile();

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* projectile_collision;

	UPROPERTY(EditDefaultsOnly)
	class UProjectileMovementComponent* projectile_movement;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* projectile_mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UParticleSystemComponent* projectile_particles;

	UPROPERTY(EditDefaultsOnly)
	float projectile_speed;

	UPROPERTY(EditDefaultsOnly)
	float gravity_delay;
	
	UPROPERTY(EditDefaultsOnly)
	float gravity_scale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX")
		class UNiagaraSystem* spark;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX")
		class UNiagaraSystem* trail;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class Udamage_number_ui> damage_number_class;

	class Udamage_number_ui* damage_number_ui_object;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* hit_comp, AActor* other_actor, UPrimitiveComponent* other_comp, FVector normal_impulse, const FHitResult& hit);

	void ApplyGravity();

	UPROPERTY(EditAnywhere, Category = "Projectile")
		float damage = 40;

};
