// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "IInteract.generated.h"

/**
 * 
 */
UINTERFACE()
class UInteract : public UInterface
{
	GENERATED_BODY()
};

class IInteract
{
	GENERATED_BODY()

public:
	FString InteractPromptText = "";
	FLinearColor InteractPromptColour = {0,0,0,1};
	bool bCanInteract = false;
	
	bool GetCanInteract(){return bCanInteract;}
	void SetCanInteract(bool Interactibility){bCanInteract = Interactibility;}
	
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void Interact();
};
