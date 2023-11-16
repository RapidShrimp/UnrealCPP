// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AI_Character.generated.h"

class UBehaviorTree;
class UAIPerceptionStimuliSourceComponent;

UCLASS()
class FPSPROJECT_API AAI_Character : public ACharacter
{
	GENERATED_BODY()

public:
	/*Set PathFollowAcceleration = true;
	// Sets default values for this character's properties
	// Rotation Rate
	// Max Walk Speed
*/
	AAI_Character();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "AI" )
	TObjectPtr<UBehaviorTree> BTree;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float ExplosionDamage = 10.0f;

	UFUNCTION(CallInEditor)
	void SelfDestruct();
public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
