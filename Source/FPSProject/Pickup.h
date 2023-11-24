// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"


class USphereComponent;

UCLASS()
class FPSPROJECT_API APickup : public AActor
{
	GENERATED_BODY()

public:
	APickup();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int Score = 1;
	
protected:
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<USceneComponent> _Root;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> _Mesh;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<USphereComponent> _Collider;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<USoundBase> _PickupSound;
	
	virtual void BeginPlay() override;
	void PlayPickupAudio();
public:
	UFUNCTION()
	virtual void OnPickup(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

};
