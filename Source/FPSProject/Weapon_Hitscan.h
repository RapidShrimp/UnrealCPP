// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "GameFramework/Actor.h"
#include "Weapon_Hitscan.generated.h"

UCLASS()
class FPSPROJECT_API AWeapon_Hitscan : public AWeapon
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeapon_Hitscan();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float _Damage;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float _Range;

	virtual bool Fire_Implementation() override;
};
