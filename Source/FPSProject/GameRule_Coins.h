// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoinPickup.h"
#include "GameRule.h"
#include "GameRule_Coins.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGameRuleCoinPickedUp, AController*,scorer,int,points);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FPSPROJECT_API UGameRule_Coins : public UGameRule
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGameRule_Coins();

	FGameRuleCoinPickedUp OnCoinPickup;	
	void Init() override;
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<ACoinPickup>> _Coins;

	int CoinsRemaining;

	UFUNCTION()
	void Handle_OnCoinPickup(AController* causer, int CoinValue);


};
