// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetDash.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Image.h"



void UWidgetDash::NativeConstruct()
{
	Super::NativeConstruct();
}

void UWidgetDash::SetBrush(bool IsFull)
{
	if(!DashImage)
		return;
	if(IsFull)
		DashImage->SetBrushFromTexture(DashFullImage);
	else
		DashImage->SetBrushFromTexture(DashEmptyImage);
}


