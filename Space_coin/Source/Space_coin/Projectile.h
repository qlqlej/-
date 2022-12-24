// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraFunctionLibrary.h"
#include "Projectile.generated.h"

DECLARE_DELEGATE(FOnHitDelegate)

UCLASS()
class SPACE_COIN_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();

protected:
	virtual void BeginPlay() override;

public:	

	int session_id = -1;

	bool owner;
	bool critical;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* hit_sound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX")
		class UNiagaraSystem* spark;


	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		class USphereComponent* collision_sphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
		class UProjectileMovementComponent* ProjectileMovment;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class Udamage_number_ui> damage_number_class;

	class Udamage_number_ui* damage_number_ui_object;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class Udamage_number_ui> critical_damage_number_class;

	class Udamage_number_ui* critical_damage_number_ui_object;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* hit_comp, AActor* other_actor, UPrimitiveComponent* other_comp, FVector normal_impulse, const FHitResult& hit);

	UPROPERTY(EditAnywhere, Category = "Projectile")
		float critical_percent = 2;
	UPROPERTY(EditAnywhere, Category = "Projectile")
		float damage = 5;
	UPROPERTY(EditAnywhere, Category = "Projectile")
		float speed = 40000;

	FOnHitDelegate hit_delegate;
};
