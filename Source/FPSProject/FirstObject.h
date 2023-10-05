// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FirstObject.generated.h"

class UArrowComponent;
class URotatingMovementComponent;

UCLASS(Abstract)
class FPSPROJECT_API AFirstObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFirstObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
#pragma	region Components
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<USceneComponent> _Root;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> _Mesh;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UArrowComponent> _Arrow;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<URotatingMovementComponent> _RotationComp;
#pragma endregion


	
	UPROPERTY(EditDefaultsOnly)
	FRotator FRotationRate;

	
	UFUNCTION(BlueprintCallable, Category = "Rotating")
	void StartRotating();

	UFUNCTION(BlueprintImplementableEvent , Category = "Rotating")
	void DiscoMode();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
