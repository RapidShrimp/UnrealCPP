// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractPrompt.h"

void UInteractPrompt::SetInteractPrompt(FString NewInteractText, FLinearColor NewColour, float NewInteractTime)
{

	SetVisibility(ESlateVisibility::Visible);
	
	if(InteractText)
		InteractText->SetText(FText::FromString(NewInteractText));
	if(InteractBar)
		InteractBar->SetFillColorAndOpacity(NewColour);
	
	InteractionTime = NewInteractTime;
}

void UInteractPrompt::HideInteractPrompt()
{
	SetVisibility(ESlateVisibility::Hidden);
}
