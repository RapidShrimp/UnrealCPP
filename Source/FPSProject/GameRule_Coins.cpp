// Fill out your copyright notice in the Description page of Project Settings.


#include "GameRule_Coins.h"

#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UGameRule_Coins::UGameRule_Coins()
{

}

void UGameRule_Coins::Init()
{
	Super::Init();
	if(_Coins.Num() == 0)
	{
		TArray<AActor*> outActors;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Coin"), outActors);
		for(AActor* a : outActors)
		{
			_Coins.Add(Cast<ACoinPickup>(a->GetComponentByClass(ACoinPickup::StaticClass())));
		}
	}

	CoinsRemaining = _Coins.Num();
	for(ACoinPickup* Coin : _Coins)
	{
		Coin->OnCoinPickedUp.AddUniqueDynamic(this,&UGameRule_Coins::Handle_OnCoinPickup);
	}

}

void UGameRule_Coins::Handle_OnCoinPickup(AController* causer, int CoinValue)
{
	UE_LOG(LogTemp,Warning,TEXT("PICKUP"))
	CoinsRemaining--;
	BroadcastGameRulePointsScored(causer,CoinValue);
	if(CoinsRemaining==0)
	{
		BroadcastGameRuleComplete();
	}
}


