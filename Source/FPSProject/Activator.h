// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Activator.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FActivatedSignature, AActor*, Interacting);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeactivatedSignature);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FPSPROJECT_API UActivator : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UActivator();

	UPROPERTY(BlueprintAssignable)
	FActivatedSignature OnActivated;

	UPROPERTY(BlueprintAssignable)
	FDeactivatedSignature OnDeactivated;

	void CallActivate();
	void CallDeactivate();
};
