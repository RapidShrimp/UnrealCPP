// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Fireable.h"
#include "IInteract.h"
#include "GameFramework/Actor.h"
#include "WeaponType.h"

#include "InputAction.h"
#include "Weapon.generated.h"

class UInteractableComp;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnUpdateAmmoCountersUpdate, int, CurrentAmmo, int, ClipSize, int,
                                               CurrentClip);

class USkeletalMeshComponent;
class UArrowComponent;
class USphereComponent;
class USoundBase;
class AFPSProjectCharacter;

UCLASS(Abstract)
class FPSPROJECT_API AWeapon : public AActor , public  IFireable, public IInteract
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeapon();
	UFUNCTION(BlueprintCallable)
	virtual void Init();

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FOnUpdateAmmoCountersUpdate OnAmmoCountersUpdate;
	
	virtual  bool Fire_Implementation() override;
	virtual  bool Reload_Implementation() override;
	virtual  void Interact_Implementation(AActor* Interacting) override;

	/** Attaches the actor to a FirstPersonCharacter */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void AttachWeapon(AFPSProjectCharacter* TargetCharacter);

	UFUNCTION(BlueprintCallable, Category="Weapon")
	void DropWeapon();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* FireMappingContext;
	
	UFUNCTION(BlueprintCallable)
	bool AddAmmo(int InAmmo);

protected:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<USceneComponent> _Root;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<USkeletalMeshComponent> _SkeletonMesh;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UArrowComponent> _Arrow;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<USphereComponent> _SphereCollider;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UInteractableComp> _InteractionComp;
	
	TObjectPtr<AFPSProjectCharacter> OwningCharacter;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UWeaponType> _TypeData;
	TObjectPtr<USoundBase> _FireSound;

	float _Damage;
	float _ReloadTime;
	int _MaxClipSize;
	float ReloadTime;
	int _CurrentClip;
	int _CurrentAmmo;
	
	void PlayFireAudio();
	
	virtual void BeginPlay() override;
private:
	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};
