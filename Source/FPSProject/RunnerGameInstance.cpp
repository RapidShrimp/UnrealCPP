// Fill out your copyright notice in the Description page of Project Settings.


#include "RunnerGameInstance.h"

void URunnerGameInstance::CalculateBetterTime(float InNewTime)
{
	if(BestTime == 0)
	{
		BestTime = InNewTime;
	}
	else if(BestTime > InNewTime)
	{
		BestTime = InNewTime;
	}
}
