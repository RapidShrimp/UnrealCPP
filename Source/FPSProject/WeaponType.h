// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPSProjectProjectile.h"
#include "Engine/DataAsset.h"
#include "WeaponType.generated.h"

/**
 * 
 */

UCLASS(BlueprintType)
class FPSPROJECT_API UWeaponType : public UDataAsset
{
	GENERATED_BODY()


public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<USkeletalMesh> _WeaponMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USoundBase> FireSound;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _Damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _ReloadTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _TimeBetweenShots;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _ChargeTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int _ClipSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int _InitialAmmo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Hitscan")
	float _Range;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Projectile")
	TSubclassOf<AFPSProjectProjectile> _Projectile;

};
