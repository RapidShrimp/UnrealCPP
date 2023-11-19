// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameRule.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameRuleCompleteSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGameRulePointsScoredSignature,AController*,Controller,int,Points);

UCLASS(Abstract)
class FPSPROJECT_API UGameRule : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGameRule();

	FGameRuleCompleteSignature OnGameRuleComplete;
	FOnGameRulePointsScoredSignature OnGameRulePointsScored;
	
	UFUNCTION()
	virtual void Init();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void BroadcastGameRuleComplete();
	void BroadcastGameRulePointsScored(AController* Controller,int Points);
};
