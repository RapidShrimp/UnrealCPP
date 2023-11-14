// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractComp.generated.h"

class UInteractableComp;
class AFPSProjectCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FNoInteractsSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FSetInteractPromptSignature, FString, newInteractText, FLinearColor, newColour,float, newInteractTime);


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FPSPROJECT_API UInteractComp : public UActorComponent
{
	GENERATED_BODY()

public:

	UInteractComp();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintAssignable)
	FNoInteractsSignature OnNoInteract;
	
	UPROPERTY(BlueprintAssignable)
	FSetInteractPromptSignature OnSetInteractPrompt;
	
	void AddInteractable(AActor* InterfacedActor);
	void RemoveInteractable(AActor* InterfacedActor);
	void Interact();
	//Interact Functions
protected:
	TArray<TObjectPtr<AActor>> InteractableList;
	TObjectPtr<AActor> CurrentSelected;
	FTimerHandle UpdateTimer;
	TObjectPtr<AFPSProjectCharacter> OwningCharacter;
	AActor* GetDesiredInteract();
	void ShowInteract();
};
