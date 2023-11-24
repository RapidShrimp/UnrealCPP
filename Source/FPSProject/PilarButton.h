// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IInteract.h"
#include "GameFramework/Actor.h"
#include "PilarButton.generated.h"

class UActivator;
class UInteractableComp;

UCLASS()
class FPSPROJECT_API APilarButton : public AActor , public IInteract
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APilarButton();

	void BeginPlay() override;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<USceneComponent> _Root;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> _Mesh;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UInteractableComp> _InteractComp;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UActivator> _Activator;

	virtual void Interact_Implementation(AActor* Interacting) override;
};
