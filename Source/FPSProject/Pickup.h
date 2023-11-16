// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCoinPickupSignature , AController*,Controller,int,Score);

class USphereComponent;

UCLASS()
class FPSPROJECT_API APickup : public AActor
{
	GENERATED_BODY()

public:
	APickup();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int Score = 1;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> _Mesh;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<USphereComponent> _Collider;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FCoinPickupSignature OnCoinPickedUp;
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void PickupCoin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

};
