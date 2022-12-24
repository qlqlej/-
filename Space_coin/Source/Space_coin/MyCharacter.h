// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "space_ship.h"
#include "public_character.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/InputComponent.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/DataTable.h"
#include "Components/TimeLineComponent.h"
#include "skill_cooltime_ui.h"
#include "monster.h"
#include "inventory_component.h"
#include "MyCharacter.generated.h"

USTRUCT(BlueprintType)
struct FCharacterInfo :public FTableRowBase
{
	GENERATED_BODY()
public:
	FCharacterInfo()
	{
		dash_cooltime = 5;
	}
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float dash_cooltime;
};

class UNiagaraComponent;

UCLASS()
class SPACE_COIN_API AMyCharacter : public Apublic_character
{
	GENERATED_BODY()

public:
	int mySessionID = -1;
	FName myName;
	bool use;


	FVector ultimate_vec;
	FRotator slash_rot;

	float dash_skill_cooldown;
	float sniper_skill_cooldown;
	float launcher_skill_cooldown;
	float missile_skill_cooldown;
	float ultimate_skill_cooldown;
	float defense_skill_cooldown;
	float slash_skill_cooldown;

	AMyCharacter();

	UPROPERTY(BlueprintReadWrite)
		bool is_aiming;

	UFUNCTION(BlueprintImplementableEvent)
		void ShowSniperOverlay();

	UFUNCTION(BlueprintImplementableEvent)
		void HideSniperOverlay();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Light)
	class USpotLightComponent* water_light;
	

	void ToggleAiming();

	virtual void PostInitializeComponents() override;

	
	virtual void Die(float killing_damage, struct FDamageEvent const& damage_event, AController* killer, AActor* damage_causer);

	FString GetCurrentMapName();

	void ReSpawn();

	unsigned int HashCode(const char* str);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
		USpringArmComponent* camera_boom;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
		UCameraComponent* follow_camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
		UCameraComponent* scope_camera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UCameraShakeBase> be_hit_camera_shake;


	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
		TSubclassOf<Aspace_ship> ship_to_spawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX")
		class UNiagaraSystem* spark;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX")
		class UNiagaraSystem* sniper_spark;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX")
		class UNiagaraSystem* bifrost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX")
		class UNiagaraSystem* dash_trail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX")
		UNiagaraComponent* spawn_trail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX")
		UNiagaraSystem* spawn_ultimate;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class Udamage_number_ui> damage_number_class;

	class Udamage_number_ui* damage_number_ui_object;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Timeline")
		UCurveFloat* CurveFloat;

	FOnTimelineEvent interpFunction();
	FOnTimelineEvent finishFunction();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI)
		class UWidgetComponent* ui_player_name;

	class Uplayer_name_ui* ui_player_name_ui;

	FTimeline LerpTimeline;

	void UnHideGun();
	void HideGun();
	UPROPERTY(BlueprintReadWrite)
		bool in_water_shoot;
	UPROPERTY(BlueprintReadWrite)
		bool InWater;

	void AddControllerYaw(float Axis);
	void AddControllerPitch(float Axis);

	void TurnRightLeft(bool is_turn_right, bool is_turn_left);
	UPROPERTY(BlueprintReadWrite)
		bool turn_right;
	UPROPERTY(BlueprintReadWrite)
		bool turn_left;

	float prev_yaw = 0;

	void MoveForward(float Axis);
	void MoveRight(float Axis);
	
	void SendOnFire();
	void OnFireGun(FRotator rot);
	
	void OnFireSniper(FRotator rot);
	void SniperCooltimeLoop();

	void SendOnLauncher();
	void OnLauncherProjectile(FRotator);
	void LauncherCooltimeLoop();
	
	const USkeletalMeshSocket* weaponSocket;
	void SendEnterVehicle();
	void EnterSpaceShip();

	void LandEffect();

	void SendOnChangeGun();
	void OnChangeGun();
	void SendOnChangeSword();
	void OnChangeSword();

	Amonster* missile_target_monster;
	Amonster* target_monster;
	void SendMissileLaunch();
	void SpawnMissile(Amonster* monster);
	void MissileCooltimeLoop();

	void SendOnUltimate();
	void OnUltimate(FVector vec);
	void UltimateCooltimeLoop();
	void UltimateLaunch();
	void UltimateEffect();
	void EndUltimateAnim();

	void SendDefense();
	void Defense();
	void DefenseOff();
	void DefenseAnim();
	void DefneseAnimEnd();
	void DefenseCooltimeLoop();

	void SendOnSlash();
	void OnSlash();
	void SlashCooltimeLoop();
	void SlashAnim(FRotator rot);
	void SlashAnimEnd();

	void SetVisibility();

	void EnableInputKey();
	
	void SendDash();
	void Dash(FVector rot);
	void DashCooltimeLoop();

	void SendJump();

	void Targeting();

	void DieAnimaition();

	void Healing(float del);
	
	void BeHit();

	void AttackHP();
	UPROPERTY(BlueprintReadWrite)
		bool is_attack;


	
	float healing_count;

	void FindMonster();

	void SpendMoney(int32 pmoney);

	void EquipACoin();
	void EquipBCoin();
	void EquipCCoin();
	void EquipCoinAnim();
	void EquipCoinAnimEnd();

	void AddScreenDamage();
	void AddScreenDeath();
	void StartAnim();

	void OnDamaged();

	UPROPERTY(BlueprintReadWrite)
	int32 money;

	UPROPERTY(BlueprintReadWrite)
		int32 a_coin;
	UPROPERTY(BlueprintReadWrite)
		int32 b_coin;
	UPROPERTY(BlueprintReadWrite)
		int32 c_coin;

	bool dash_possible;
	bool sniper_possible;
	bool launcher_possible;
	bool missile_possible;
	bool ultimate_possible;
	bool defense_possible;
	bool slash_possible;

	int32 sniper_bullet_count = 0;

	bool is_ultimate_anim;
	bool is_defense_anim;
	bool is_slash_anim;
	float dash_distance = 40000;

	bool is_respawning;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int enter = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool run;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector  velocity_blend;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float  speed_blend;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FRotator  rotation_blend;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool  in_air;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool  is_dashing;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool  is_dashing_client;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool is_swimming;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float swimming_speed_blend;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool other_player_swimming;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float waterZ;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool is_jumping;

	UFUNCTION()
		void SendSpawnShip();
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool  is_defense;
	UPROPERTY(BlueprintReadWrite)
		bool is_target_locked;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FTimerHandle missile_handle;

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AProjectile> projectile;
	class AProjectile* projectile_object;
	UPROPERTY(EditDefaultsOnly, Category = Slash)
		TSubclassOf<class Asword_slash> slash;
	class Asword_slash* slash_object;
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class Alauncher_projectile> launcher_projectile;
	class Alauncher_projectile* launcher_projectile_object;
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class Asniper_projectile> sniper_projectile;
	class Asniper_projectile* sniper_projectile_object;
	UPROPERTY(VisibleAnywhere, Category = Inventory)
		Uinventory_component* inventory_component;
	UPROPERTY(EditDefaultsOnly, Category = TargetMaker)
		TSubclassOf<class Atarget_maker> target_maker;
	class Atarget_maker* target_maker_object;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* fire_sound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* sniper_sound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* missile_sound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* launcher_sound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* dash_sound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* ultimate_sound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* coin_pickup_sound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* behit_sound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class USoundBase* death_sound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UAnimMontage* coin_pickup_animation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UAnimMontage* fire_animation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UAnimMontage* slash_animation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UAnimMontage* dash_montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UAnimMontage* ultimate_montage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UAnimMontage* defense_montage;
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USceneComponent* muzzle_location;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UAnimMontage* death_animation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UAnimMontage* gun_start_animation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UAnimMontage* sword_start_animation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector gun_offset;
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* gun_mesh;
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* hands_mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UArrowComponent* fx_loc;
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		class USkeletalMeshComponent* spawn_missile;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UAnimMontage* walk_right_animation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UAnimMontage* walk_left_animation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
		class UAnimMontage* missile_skill_animation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBlendSpace* blend_space;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class Udamage_indicator_ui> screen_damage_class;
	class Udamage_indicator_ui* screen_damage_ui_object;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class Udeath_ui> screen_death_class;
	class Udeath_ui* screen_death_ui_object;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
		class UBoxComponent* collision_comp;
	
	// Static Mesh Component for Turret Class
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Mesh")
		class UStaticMeshComponent* turret_mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shiled")
		class UStaticMeshComponent* skill_defense;
	// Missile Blueprint Class To Fire
	UPROPERTY(EditDefaultsOnly, Category = "Turret Projectiles")
		TSubclassOf<class Amissile> missile_class;



	class UAnimInstance* anim_instance;

	class UWorld* world;
	FRotator spawn_rotation;
	FVector spawn_location;

	Aspace_ship* spaceship;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		float critical_percent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		float speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		float atk;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		float max_hp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		float healing;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		float sniper_damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		float atk_hp_up;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		float launcher_damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		float launcher_radius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		float launcher_particle_radius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		float jump_velocity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		float missile_damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		float slash_damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		float slash_size;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		float ultimate_damage;
	
	void SetCriticalPercent(int qunatity);
	void AddCriticalPercent();
	void SetSpeed(int qunatity);
	void AddSpeed();
	void SetAtk(int qunatity);
	void AddAtk();
	void SetMaxHp(int qunatity);
	void AddMaxHp();
	void SetHealing(int qunatity);
	void AddHealing();
	void SetSniperDamage(int qunatity);
	void AddSniperDamge();
	void SetAtkHpUp(int qunatity);
	void AddAtkHpUp();
	void SetLauncherDamage(int qunatity);
	void AddLauncherDamage();
	void SetLauncherRadius(int qunatity);
	void AddLauncherRadius();
	void SetJump(int qunatity);
	void AddJump();
	void SetMissileDamage(int qunatity);
	void AddMissileDamage();
	void SetSlashDamage(int qunatity);
	void AddSlashDamage();
	void SetSlashSize(int qunatity);
	void AddSlashSize();
	void SetUltimateDamage(int qunatity);
	void AddUltimateDamage();
};
