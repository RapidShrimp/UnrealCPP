// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameRule.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameRuleCompleteSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGameRulePointScoredSignature, AController*,scorer,int,points);

UCLASS(Abstract)
class FPSPROJECT_API UGameRule : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGameRule();

	FGameRuleCompleteSignature OnGameRuleComplete;
	FGameRulePointScoredSignature OnGameRulePointsScored;

	UFUNCTION()
	virtual void Init();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void BroadcastGameRuleComplete();
	void BroadcastGameRulePointsScored(AController* scorer, int points);
};
