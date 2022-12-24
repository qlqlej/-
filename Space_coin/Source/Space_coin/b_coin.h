// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "b_coin.generated.h"

UCLASS()
class SPACE_COIN_API Ab_coin : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Ab_coin();
	int session_id;
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& hitResult);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
		class USphereComponent* collision_comp;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
