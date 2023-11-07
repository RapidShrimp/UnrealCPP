// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetHUD.generated.h"

class UHorizontalBox;
class UImage;
/**
 * 
 */
class UInteractPrompt;
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
	void UpdateAmmoCounters(int CurrentAmmo,int ClipSize,int CurrentClip);
	void UpdateDash(int DashesLeft,int MaxDashes);
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthBar;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ScoreText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UInteractPrompt> InteractPrompt ;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CurrentClipText;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> MaxClipText;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CurrentAmmoText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHorizontalBox> DashUI;
	
};
