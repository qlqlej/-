// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "monster.h"
#include "missile.generated.h"

UCLASS()
class SPACE_COIN_API Amissile : public AActor
{
	GENERATED_BODY()
private:


	bool has_target_position;
	bool has_no_target;
	class AActor* target;


	float delay_timer;

	bool has_finished_delay;
	
	Amonster* missile_target_monster;


	float lifetime_countdown;
	bool can_be_destroyed;
	void Explode();


	UFUNCTION()
		void OnHit(UPrimitiveComponent* hit_comp, AActor* other_actor, UPrimitiveComponent* other_comp, FVector normal_impulse, const FHitResult& hit);

public:

	Amissile(const FObjectInitializer& ObjectInitializer);

protected:


	virtual void BeginPlay() override;

	

public:
	int session_id = -1;

	bool owner;

	virtual void Tick(float DeltaTime) override;


	void DelayLogic(float dTime);
	void LockOn(Amonster* monster);
	void Homing();
	void Loop();


	
	void UpdateTarget();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
		class UBoxComponent* collision_comp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
		class UStaticMeshComponent* missile_mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
		class UProjectileMovementComponent* projectile_movement;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class Udamage_number_ui> damage_number_class;

	class Udamage_number_ui* damage_number_ui_object;

	UPROPERTY(EditDefaultsOnly, Category = "FX")
		class UParticleSystem* explosion_system;

	class UParticleSystemComponent* PlayExplosion(class UParticleSystem* explosion);

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
		class USoundCue* explosion_sound;

	class UAudioComponent* PlayExplosionSound(class USoundCue* sound);

	UPROPERTY(EditAnywhere, Category = "Projectile")
		float damage = 15;
};
