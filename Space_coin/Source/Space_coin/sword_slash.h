// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraFunctionLibrary.h"
#include "sword_slash.generated.h"

/**
 * 
 */
UCLASS()
class SPACE_COIN_API Asword_slash : public AActor
{
	GENERATED_BODY()
public:
	int session_id = -1;

	bool owner;

	UPROPERTY(EditAnywhere, Category = "Projectile")
		float damage = 20;
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		class UBoxComponent* collision_box;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
		class UProjectileMovementComponent* ProjectileMovment;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class Udamage_number_ui> damage_number_class;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* sword_hit_sound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX")
		class UNiagaraSystem* spark;

	class Udamage_number_ui* damage_number_ui_object;

	UPROPERTY(EditAnywhere, Category = "Projectile")
		float speed = 4000;

	Asword_slash();
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& hitResult);
protected:
	virtual void BeginPlay() override;
};
