// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetDash.h"

#include "Components/Image.h"

void UWidgetDash::OnDashUpdate(int CurrentDashes, int MaxDashes)
{
	if(!bIsInit)
		Init(MaxDashes);

	for (int i = 0; i != DashesArr.Num()-1 ; i++)
	{
	}
}

void UWidgetDash::Init(int Dashes)
{
	for(int i = 1; i < Dashes; i++)
	{
		//Create widget image;
		//UImage* Image = CreateWidget<UImage>(this,_ImageWidgetClass,FName("Dash Image"));

	}
	bIsInit = true;
}
