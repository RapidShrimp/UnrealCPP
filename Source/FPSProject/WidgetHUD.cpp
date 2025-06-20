﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetHUD.h"

#include "InteractPrompt.h"
#include "WidgetDash.h"

#include "Components/HorizontalBox.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UWidgetHUD::NativeConstruct()
{
	Super::NativeConstruct();
	if(HealthBar)
		HealthBar->SetPercent(1);
	if(CoinsText)
		CoinsText->SetText(FText::FromString(""));
	if(InteractPrompt)
		InteractPrompt->SetVisibility(ESlateVisibility::Hidden);
} 

void UWidgetHUD::UpdateHealth(float newHealthRatio)
{
	if(HealthBar)
	{
		HealthBar->SetPercent(newHealthRatio);
		UE_LOG(LogTemp,Warning,TEXT("HEALTH CHANGED, %f"), newHealthRatio);
	}
}

void UWidgetHUD::UpdatePoints(int newScore)
{
	if(CoinsText)
		CoinsText->SetText(FText::FromString(FString::Printf(TEXT("Coins: %d"), newScore)));
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

void UWidgetHUD::UpdateDash(int DashesLeft, int MaxDashes)
{
	if(DashUI)
	{
		int i = 0;
		bool IsFull;
		for (UWidget* Widget: DashUI->GetAllChildren())
		{
			if(UWidgetDash* DashWidget = Cast<UWidgetDash>(Widget))
			{
				IsFull = i < DashesLeft;
				DashWidget->SetBrush(IsFull);
				i+=1;
			}
		}
		
	}
}

void UWidgetHUD::InteractPromptHide()
{
	if(!InteractPrompt)
		return;
	InteractPrompt->SetVisibility(ESlateVisibility::Hidden);
}

void UWidgetHUD::SetInteractPrompt(FString NewInteractText, FLinearColor NewColour, float NewInteractTime)
{
	if(!InteractPrompt)
		return;
	InteractPrompt->SetInteractPrompt(NewInteractText,NewColour,NewInteractTime);
	InteractPrompt->SetVisibility(ESlateVisibility::Visible);
}
