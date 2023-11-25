// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetSwitch.generated.h"

class UHealthComponent;
class UActivator;

UCLASS()
class FPSPROJECT_API ATargetSwitch : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATargetSwitch();
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<USceneComponent> _Root;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> _Mesh;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UActivator> _Activator;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UHealthComponent> _HealthComp;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UFUNCTION()
	void Handle_TargetHit(float NewHealth,float CurrentHealth,float MaxHealth);
};
