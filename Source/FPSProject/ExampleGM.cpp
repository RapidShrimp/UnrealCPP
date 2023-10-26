// Fill out your copyright notice in the Description page of Project Settings.


#include "ExampleGM.h"


// Sets default values
AExampleGM::AExampleGM()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AExampleGM::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}

void AExampleGM::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
}

void AExampleGM::DecreaseCountdown()
{
}

void AExampleGM::Handle_GameRuleCompleted()
{
}

void AExampleGM::Handle_GameRulePointsScored(AController* scorer, int points)
{
	if(scorer)
	{
		
	}
}

void AExampleGM::HandleMatchIsWaitingToStart()
{
	Super::HandleMatchIsWaitingToStart();
}

void AExampleGM::HandleMatchHasStarted()
{
	Super::HandleMatchHasStarted();
}

void AExampleGM::HandleMatchHasEnded()
{
	Super::HandleMatchHasEnded();
}

void AExampleGM::OnMatchStateSet()
{
	Super::OnMatchStateSet();
}

bool AExampleGM::ReadyToStartMatch_Implementation()
{
	return Super::ReadyToStartMatch_Implementation();
}

bool AExampleGM::ReadyToEndMatch_Implementation()
{
	return Super::ReadyToEndMatch_Implementation();
}

// Called when the game starts or when spawned
void AExampleGM::BeginPlay()
{
	Super::BeginPlay();
	TArray<UActorComponent*> outComponents;
	GetComponents(outComponents);
	for(UActorComponent* comp : outComponents)
	{
		if (UGameRule* rule = Cast<UGameRule>(comp))
		{
			_GameRuleManagers.Add(rule);
			rule->Init();
			rule->OnGameRuleComplete.AddUniqueDynamic(this, &AExampleGM::Handle_GameRuleCompleted);
			rule->OnGameRulePointsScored.AddUniqueDynamic(this, &AExampleGM::Handle_GameRulePointsScored);
		}
	}
}

// Called every frame
void AExampleGM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

