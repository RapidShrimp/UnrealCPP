// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Fireable.h"
#include "GameFramework/Actor.h"
#include "InputAction.h"
#include "Weapon.generated.h"

class USkeletalMeshComponent;
class UArrowComponent;
class USphereComponent;
class USoundBase;
class AFPSProjectCharacter;

UCLASS(Abstract)
class FPSPROJECT_API AWeapon : public AActor , public  IFireable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeapon();
	
	virtual  bool Fire_Implementation() override;

	/** Attaches the actor to a FirstPersonCharacter */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void AttachWeapon(AFPSProjectCharacter* TargetCharacter);

	UFUNCTION(BlueprintCallable, Category="Weapon")
	void DropWeapon();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* FireMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Weapon")
	TObjectPtr<USoundBase> FireSound;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Weapon")
	int _MaxAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Weapon")
	int _MaxClipSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Weapon")
	int StartingAmmo;
	
	UFUNCTION(BlueprintCallable)
	bool AddAmmo(int InAmmo);
	
	UFUNCTION(BlueprintCallable)
	bool Reload();
	
protected:
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<USceneComponent> _Root;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<USkeletalMeshComponent> _SkeletonMesh;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UArrowComponent> _Arrow;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<USphereComponent> _SphereCollider;
	
	TObjectPtr<AFPSProjectCharacter> OwningCharacter;


	int _CurrentAmmo;
	int _CurrentClip;
	
	void PlayFireAudio();
	
	virtual void BeginPlay() override;
private:
	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
