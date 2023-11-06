// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetDash.h"

#include "Blueprint/WidgetTree.h"
#include "Components/Image.h"



void UWidgetDash::NativeConstruct()
{
	Super::NativeConstruct();
}

void UWidgetDash::Init(int MaxDashes)
{
	for(int i = 0; i < MaxDashes; i++)
	{
		UImage* NewImage = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass(),TEXT("ImageWidget"));
		NewImage->SetBrushFromTexture(DashFullImage);
		DashArr.Add(NewImage);
		
	}
	bInit = true;
}

void UWidgetDash::OnDashUpdate(int CurrentDashes, int MaxDashes)
{
	if(!bInit)
		Init(MaxDashes);
	UE_LOG(LogTemp,Warning,TEXT("DashArrItems %d"),DashArr.Num())

	for(int i = 0; i < DashArr.Num()-1; i++)
	{
		if(i <= CurrentDashes - 1)
			DashArr[i]->SetBrushFromTexture(DashFullImage);
		else
			DashArr[i]->SetBrushFromTexture(DashFullImage);

	}
	
}
