// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Space_coin/public_character.h"
#include "GameFramework/Actor.h"
#include "NiagaraFunctionLibrary.h"
#include "weapon.generated.h"

UCLASS()
class SPACE_COIN_API Aweapon : public AActor
{
	GENERATED_BODY()
	
public:	
	bool owner;
	bool critical;

	UPROPERTY(VisibleDefaultsOnly, Category = Weapon)
		USkeletalMeshComponent* weapon_mesh;

	Aweapon(const class FObjectInitializer& objectinitalizer);

	void SetOwningPawn(Apublic_character* new_owner);

	void AttachMeshToPawn();

	void OnEquip(const Aweapon* last_weapon);

	void OnUnEquip();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* sword_hit_sound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX")
		class UNiagaraSystem* spark;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class Udamage_number_ui> damage_number_class;

	UPROPERTY(EditAnywhere, Category = "Projectile")
		float damage;
	UPROPERTY(EditAnywhere, Category = "Weapon")
		float critical_percent = 2;

	class Udamage_number_ui* damage_number_ui_object;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class Udamage_number_ui> critical_damage_number_class;

	class Udamage_number_ui* critical_damage_number_ui_object;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor)override;
private:

	UPROPERTY(VisibleAnyWhere, Category = "Collision")
		class USphereComponent* weapon_collision;

	float inPlayRate;
protected:
	class Apublic_character* my_pawn;
};
