// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FirstObject.generated.h"

class UHealthComponent;
class UArrowComponent;
class URotatingMovementComponent;
class UBoxComponent;

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

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UBoxComponent> _BoxComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UHealthComponent> _HealthComponent;
#pragma endregion


	
	UPROPERTY(EditDefaultsOnly)
	FRotator FRotationRate;

	
	UFUNCTION(BlueprintCallable, Category = "Rotating")
	void StartRotating();

	UFUNCTION(BlueprintCallable, Category = "Rotating")
	void AddRotationSpeed();
	
	UFUNCTION(BlueprintImplementableEvent , Category = "Rotating")
	void DiscoMode();
	UFUNCTION(BlueprintImplementableEvent , Category = "Rotating")
	void Float();
	bool bIsFloating = false;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


private:
	UFUNCTION()
	void Handle_ComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );
};
