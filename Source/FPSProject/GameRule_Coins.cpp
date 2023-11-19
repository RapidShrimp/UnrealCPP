// Fill out your copyright notice in the Description page of Project Settings.


#include "GameRule_Coins.h"

#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UGameRule_Coins::UGameRule_Coins()
{
	CoinsRemaining = 0;
}

void UGameRule_Coins::Init()
{
	if(_Coins.Num() == 0)
	{
		TArray<AActor*> outActors;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Coin"), outActors);

		for(AActor* Coin : outActors)
		{
			if(ACoinPickup* VerifiedCoin =Cast<ACoinPickup>(Coin))
			{
				_Coins.AddUnique(VerifiedCoin);
				 VerifiedCoin->OnCoinPickedUp.AddUniqueDynamic(this,&UGameRule_Coins::Handle_OnCoinPickup);
			}
		}
		CoinsRemaining = _Coins.Num();
	}

	Super::Init();

}

void UGameRule_Coins::Handle_OnCoinPickup(AController* causer, int CoinValue)
{
	CoinsRemaining--;
	OnGameRulePointsScored.Broadcast(causer,CoinValue);
	BroadcastGameRulePointsScored(causer,CoinValue);
	if(CoinsRemaining==0)
	{
		BroadcastGameRuleComplete();
	}
}


