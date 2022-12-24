// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "public_character.generated.h"

UCLASS()
class SPACE_COIN_API Apublic_character : public ACharacter
{
	GENERATED_BODY()

public:
	Apublic_character();

	USkeletalMeshComponent* GetSpecificPawnMesh() const;

	FName GetWeaponAttachPoint() const;

	UPROPERTY(BlueprintReadWrite)
		bool is_othercharacter;

	void EquipWeapon(class Aweapon* weapon);

	void WeaponAttack();

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Health)
		float health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "anim")
	
		
	int cur_weapon = 1;

	UPROPERTY(EditDefaultsOnly, Category = Animation)
		UAnimMontage* gun_idle;
	UPROPERTY(EditDefaultsOnly, Category = Animation)
		UAnimMontage* sword_idle;

	void StartAttack();

	UPROPERTY(EditDefaultsOnly,BlueprintREadOnly, Category = Animation)
	class	UAnimMontage* attack_anim;

	bool during_attack = false;
	int combo_cnt;
	bool bis_attack_button_when_attack;
	UFUNCTION(BlueprintCallable)
		void EndAttacking();
	UFUNCTION(BlueprintCallable)
	void AttackInputChecking();
	class Aweapon* current_weapon;
protected:
	UPROPERTY(EditDefaultsOnly, Category = inventory)
	FName weapon_attachpoint;

	TArray<class Aweapon*> inventory;


	void AddWeapon(class Aweapon* weapon);

	void SetCurrentWeapon(class Aweapon* new_weapon, class Aweapon* last_weapon);

	UPROPERTY(EditDefaultsOnly, Category = inventory)
		TArray<TSubclassOf<class Aweapon>>DefaultInventoryClasses;

	void SpawnDefaultsInventory();

	UPROPERTY(EditDefaultsOnly, Category = Pawn)
		UAnimMontage* be_hit_anim;
	UPROPERTY(EditDefaultsOnly, Category = Pawn)
		UAnimMontage* be_hit_sword_anim;
	UPROPERTY(EditDefaultsOnly, Category = Pawn)
		UAnimMontage* death_anim;

	virtual void OnHit(float damage_taken, struct FDamageEvent const& damage_event, class APawn* pawn_instrigator, class AActor* damage_causer);


	void OnDieAnimationEnd();
};
