// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractComp.generated.h"


class AFPSProjectCharacter;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FPSPROJECT_API UInteractComp : public UActorComponent
{
	GENERATED_BODY()

public:

	UInteractComp();

protected:
	virtual void BeginPlay() override;

public:

	//Interact Functions
	TArray<AActor*> InteractableList;
	TObjectPtr<AFPSProjectCharacter> OwningCharacter;
	void AddInteractable(AActor* InterfacedActor);
	void RemoveInteractable(AActor* InterfacedActor);
	AActor* GetDesiredInteract();
	
	void Interact();
};
