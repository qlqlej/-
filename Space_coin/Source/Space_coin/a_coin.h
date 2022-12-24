// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "a_coin.generated.h"

UCLASS()
class SPACE_COIN_API Aa_coin : public AActor
{
	GENERATED_BODY()
	
public:	
	Aa_coin();
	int session_id;
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& hitResult);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
		class USphereComponent* collision_comp;
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
