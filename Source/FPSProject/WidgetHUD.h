// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetHUD.generated.h"

/**
 * 
 */
class UProgressBar;
class UTextBlock;
UCLASS(Abstract,BlueprintType)
class FPSPROJECT_API UWidgetHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	void UpdateHealth(float newHealthRatio);
	void UpdateScore(int newScore);

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthBar;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ScoreText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CurrentClip;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> MaxClip;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CurrentAmmo;
	
};
