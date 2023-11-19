// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "CoinPickup.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCoinPickupSignature , AController*,Controller,int,Score);

UCLASS()
class FPSPROJECT_API ACoinPickup : public APickup
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACoinPickup();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FCoinPickupSignature OnCoinPickedUp;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void OnPickup(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
