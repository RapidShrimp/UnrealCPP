// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "InteractPrompt.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class FPSPROJECT_API UInteractPrompt : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> InteractText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> InteractBar;
	
	FLinearColor _InteractColour;

	//void UpdateInteract()
};
