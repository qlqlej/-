#pragma once

#include "game_info.h"
#include "monster.h"
#include "second_sand_monster.generated.h"
 
UCLASS()
class SPACE_COIN_API Asecond_sand_monster : public Amonster
{
	GENERATED_BODY()

public:
	Asecond_sand_monster();

protected:
	class Usecond_sand_monster_anim* second_sand_monster_anim;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Animaions)
	UAnimMontage* hit_montage;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	virtual void ChangeAnim(Emonster_anim anim);

	void MoveToLocation(const FVector& dest, float yaw);

	void PlayAttack(short target, const FVector& target_loc);

	void PlayHit();

	void PlayDeath();

	void EnableWeaponCollision(bool enable);

	UFUNCTION()
	void WeaponBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void WeaponEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


};
