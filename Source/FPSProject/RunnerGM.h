// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameRule.h"
#include "GameFramework/GameMode.h"
#include "RunnerGM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTimeChanged,int,NewTime);

UCLASS()
class FPSPROJECT_API ARunnerGM : public AGameMode
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARunnerGM();

	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
	
	FTimeChanged OnTimeChanged;
	
protected:
	TArray<TObjectPtr<AActor>> _PlayerStarts;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	TArray<TObjectPtr<AController>> _PlayerControllers;
	int _PlayerScore;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<TObjectPtr<UGameRule>> _GameRuleManagers;
	int _GameRulesLeft;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category=MatchManagement)
	int _CountdownTimer;
	FTimerHandle _TimerDecreaseCountdown;
	
	UFUNCTION()
	void DecreaseCountdown();
	UFUNCTION()
	void Handle_GameRuleCompleted();
	UFUNCTION()
	void Handle_GameRulPointsScored(AController* Controller,int Points);
	
	virtual void BeginPlay() override;

	virtual void HandleMatchIsWaitingToStart() override;
	virtual void HandleMatchHasStarted() override;
	virtual void HandleMatchHasEnded() override;

	virtual void OnMatchStateSet() override;

	virtual bool ReadyToStartMatch_Implementation() override;
	virtual bool ReadyToEndMatch_Implementation() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
