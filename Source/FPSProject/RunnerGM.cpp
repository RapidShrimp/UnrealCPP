// Fill out your copyright notice in the Description page of Project Settings.


#include "RunnerGM.h"

#include "PController.h"

// Sets default values
ARunnerGM::ARunnerGM()
{
}

void ARunnerGM::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}

void ARunnerGM::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
}

// Called when the game starts or when spawned
void ARunnerGM::BeginPlay()
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
			rule->OnGameRuleComplete.AddUniqueDynamic(this, &ARunnerGM::Handle_GameRuleCompleted);
			rule->OnGameRulePointsScored.AddUniqueDynamic(this, &ARunnerGM::Handle_GameRulPointsScored);
		}
	}

	GetWorld()->GetTimerManager().SetTimer(_TimerDecreaseCountdown,this,&ARunnerGM::DecreaseCountdown,1,true);
}

void ARunnerGM::DecreaseCountdown()
{
	_CountdownTimer--;
	if(_CountdownTimer == 0)
	{
		UE_LOG(LogTemp,Warning,TEXT("Round Over"));
	}
	OnTimeChanged.Broadcast(_CountdownTimer);
}

void ARunnerGM::Handle_GameRuleCompleted()
{
}

void ARunnerGM::Handle_GameRulPointsScored(AController* Controller, int Points)
{
	// Get Current Player Points
	// Add New Points
	
	_PlayerScore += Points;
	if(APController* PlayerController = Cast<APController>(Controller))
	{
		PlayerController->HandlePointsUpdate(_PlayerScore);
	}
}


void ARunnerGM::HandleMatchIsWaitingToStart()
{
	Super::HandleMatchIsWaitingToStart();
}

void ARunnerGM::HandleMatchHasStarted()
{
	Super::HandleMatchHasStarted();
}

void ARunnerGM::HandleMatchHasEnded()
{
	Super::HandleMatchHasEnded();
}

void ARunnerGM::OnMatchStateSet()
{
	Super::OnMatchStateSet();
}

bool ARunnerGM::ReadyToStartMatch_Implementation()
{
	return Super::ReadyToStartMatch_Implementation();
}

bool ARunnerGM::ReadyToEndMatch_Implementation()
{
	return Super::ReadyToEndMatch_Implementation();
}



// Called every frame
void ARunnerGM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

