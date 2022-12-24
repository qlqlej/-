// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine.h"
#include "launcher_projectile.generated.h"

UCLASS(config = Game)
class SPACE_COIN_API Alauncher_projectile : public AActor
{
	GENERATED_BODY()

		UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		class USphereComponent* collision_comp;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "ture"))
		class UProjectileMovementComponent* projectile_movment;

	UPROPERTY(EditAnywhere, Category = "FX")
		class UParticleSystem* explosion_particles;

	UPROPERTY(EditAnywhere, Category = "FX")
		class USoundCue* explosion_sound;

	




public:
	int session_id = -1;

	bool owner;

	float explosion_particle_range;
	// Sets default values for this actor's properties
	Alauncher_projectile();
	virtual void BeginPlay()override;
	UFUNCTION()
		void OnHit(UPrimitiveComponent* hit_comp, AActor* other_actor, UPrimitiveComponent* other_comp, FVector normal_impulse, const FHitResult& hit);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class Udamage_number_ui> damage_number_class;

	class Udamage_number_ui* damage_number_ui_object;

	UFUNCTION()
		void OnDetonate();
	UPROPERTY(EditAnywhere, Category = "Projectile")
		float radius;
	UPROPERTY(EditAnywhere, Category = "Projectile")
		float damage = 30;
};