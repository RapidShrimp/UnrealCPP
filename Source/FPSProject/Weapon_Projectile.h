// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Weapon_Projectile.generated.h"

class AFPSProjectProjectile;

UCLASS()
class FPSPROJECT_API AWeapon_Projectile : public AWeapon
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AWeapon_Projectile();

	virtual bool Fire_Implementation() override;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FColor _WeaponColour = {0,0,0,0};

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<AFPSProjectProjectile> _Projectile;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
