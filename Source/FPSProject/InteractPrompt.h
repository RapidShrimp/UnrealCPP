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

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> InteractText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> InteractBar;
	
	FLinearColor InteractColour;
	float InteractionTime;
	
public:
	void SetInteractPrompt(FString NewInteractText, FLinearColor NewColour, float NewInteractTime);
	void HideInteractPrompt();
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void InteractStart();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void InteractCancel();
};
