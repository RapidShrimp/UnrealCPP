// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHealthComponentDeadSignature,AController*, causer);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FHealthComponentDamagedSignature, float,newHealth,float,maxHealth,float,healthChange);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FPSPROJECT_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealthComponent();
	UPROPERTY(BlueprintAssignable)
	FHealthComponentDamagedSignature OnHealthComponentDamaged;
	UPROPERTY(BlueprintAssignable)
	FHealthComponentDeadSignature OnHealthComponentDead;

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float _MaxHealth = 100;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	float _CurrentHealth;
	virtual  void BeginPlay() override;

	
private:
	UFUNCTION()
	void DamageTaken(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};
