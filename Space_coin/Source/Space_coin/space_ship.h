// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/Character.h"
#include "Camera/CameraShake.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "space_ship.generated.h"

class AMyCharacter;
UCLASS()
class SPACE_COIN_API Aspace_ship : public ACharacter
{
	GENERATED_BODY()

public:
	Aspace_ship();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
		USpringArmComponent* camera_boom;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
		UCameraComponent* follow_camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flight")
	float acceleration{ 30.0f };
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flight")
	float max_speed{ 2000.f };
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flight")
	float min_speed{ 0 };

	UPROPERTY(EditAnywhere, Category = "Flight")
	float roll_rate_multiplier{ 200.f };
	UPROPERTY(EditAnywhere, Category = "Flight")
	float ptich_rate_multiplier{ 200.f };
	UPROPERTY(EditAnywhere, Category = "Flight")
	float yaw_rate_multiplier{ 200.f };


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flight")
	float current_foward_speed{ 0 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Flight")
		float current_speed{ 0 };
	float speed{0};

	UPROPERTY()
		AMyCharacter* owner_character;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UMatineeCameraShake> MyShake;

	float hp;
	float current_yaw_speed;
	float current_pitch_speed;
	float current_roll_speed;

	bool b_intentional_pitch{ false };
	bool b_intentional_yaw{ false };
	bool b_intentional_roll{ false };

	int owner_session_id = -1;
	
	bool is_openlevel;

	bool is_thorttle;
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void EnterCharacter(AMyCharacter* character);
	void SendExit();
	void Exit();

	void ExitUnHidden();

	void UnOpenLevel();

	short GetId() { return owner_session_id; }
	void SetId(short id) { owner_session_id = id; }
protected:

	void ProcessKeyPitch(float rate);
	void ProcessKeyRoll(float rate);
	void ProcessKeyYaw(float rate);

	void ProcessKeyThrottle(float rate);

	void ProcessMouseYInput(float value);
	void ProcessMouseXInput(float value);

	void ProcessRoll(float value);
	void ProcessPitch(float value);
	void ProcessYaw(float value);


	virtual void BeginPlay() override;


	

};
