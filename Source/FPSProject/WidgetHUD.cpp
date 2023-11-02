// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetHUD.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UWidgetHUD::NativeConstruct()
{
	Super::NativeConstruct();
	if(HealthBar)
		HealthBar->SetPercent(1);
	if(ScoreText)
		ScoreText->SetText(FText::FromString("Score"));
} 

void UWidgetHUD::UpdateHealth(float newHealthRatio)
{
	if(HealthBar)
	{
		HealthBar->SetPercent(newHealthRatio);
		UE_LOG(LogTemp,Warning,TEXT("HEALTH CHANGED, %f"), newHealthRatio);
	}
}

void UWidgetHUD::UpdateScore(int newScore)
{
	if(ScoreText)
		ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"), newScore)));
}

void UWidgetHUD::UpdateAmmoCounters(int CurrentAmmo, int ClipSize, int CurrentClip)
{
	if(CurrentAmmoText)
		CurrentAmmoText->SetText(FText::FromString(FString::Printf(TEXT("%d"), CurrentAmmo)));
	if(MaxClipText)
		MaxClipText->SetText(FText::FromString(FString::Printf(TEXT("%d"), ClipSize)));
	if(CurrentClipText)
		CurrentClipText->SetText(FText::FromString(FString::Printf(TEXT("%d"), CurrentClip)));
}
