// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Fireable.h"
#include "GameFramework/Actor.h"
#include "InputAction.h"
#include "Weapon.generated.h"

class USkeletalMeshComponent;
class UArrowComponent;
class AFPSProjectCharacter;

UCLASS(Abstract)
class FPSPROJECT_API AWeapon : public AActor , public  IFireable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeapon();
	
	UFUNCTION()
	virtual  bool Fire_Implementation() override;

	/** Attaches the actor to a FirstPersonCharacter */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void AttachWeapon(AFPSProjectCharacter* TargetCharacter);

	UFUNCTION(BlueprintCallable, Category="Weapon")
	void DropWeapon(AFPSProjectCharacter* TargetCharacter);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* FireMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* FireAction;
	
protected:
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<USceneComponent> _Root;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<USkeletalMeshComponent> _SkeletonMesh;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UArrowComponent> _Arrow;
	
	TObjectPtr<AFPSProjectCharacter> Character;
public:

};
