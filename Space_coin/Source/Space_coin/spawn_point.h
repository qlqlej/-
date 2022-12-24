#pragma once

#include "game_info.h"
#include "patrol_point.h" 
#include "GameFramework/Actor.h"
#include "spawn_point.generated.h"

UCLASS()
class SPACE_COIN_API Aspawn_point : public AActor
{
	GENERATED_BODY()
	
public:	
	Aspawn_point();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
    TSubclassOf<class Amonster> spawn_type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	float spawn_time;  

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	bool infinity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (AllowPrivateAccess = "true"))
	TArray<Apatrol_point*> patrol_point_array;

	float spawn_duration;  
	bool spawn_enable; 
	
	class Amonster* spawn_monster;  

public:
	void Respawn(); 

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
