#pragma once

#include "game_info.h"
#include "monster.h"
#include "second_swimming_monster.generated.h"

UCLASS()
class SPACE_COIN_API Asecond_swimming_monster : public Amonster
{
	GENERATED_BODY()

public:
	Asecond_swimming_monster();

protected:
	class Usecond_swimming_monster_anim* second_swimming_monster_anim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Light)
	class USpotLightComponent* water_light;

	bool move;
	FVector move_dest;
	FRotator move_rot;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	virtual void ChangeAnim(Emonster_anim anim);

	void MoveToLocation(const FVector& dest, const FRotator& rot);

	void Move(const FVector& dest, const FRotator& rot);

	void PlayAttack(short target, const FVector& target_loc);

	void PlayDeath();
};
