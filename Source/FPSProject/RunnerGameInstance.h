// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RunnerGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class FPSPROJECT_API URunnerGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	float BestTime;
	
	UFUNCTION(BlueprintCallable)
	void CalculateBetterTime(float InNewTime);
};
