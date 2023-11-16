// Fill out your copyright notice in the Description page of Project Settings.


#include "GameRule.h"


// Sets default values for this component's properties
UGameRule::UGameRule()
{

}

void UGameRule::Init()
{
}

// Called when the game starts
void UGameRule::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void UGameRule::BroadcastGameRuleComplete()
{
}

void UGameRule::BroadcastGameRulePointsScored(AController* scorer, int points)
{
}


