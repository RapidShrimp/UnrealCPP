// Fill out your copyright notice in the Description page of Project Settings.


#include "GameRule_Target.h"

#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UGameRule_Target::UGameRule_Target()
{

}

void UGameRule_Target::Init()
{
	if(_Target.Num() == 0)
	{
		TArray<AActor*> outActors;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("GameRuleTarget"), outActors);
		for(AActor* a : outActors)
		{
			_Target.Add(Cast<UTarget>(a->GetComponentByClass(UTarget::StaticClass())));
		}
	}

	_AmountRemaining = _Target.Num();
	for(UTarget* Target : _Target)
	{
		Target->OnTargetDestroyed.AddUniqueDynamic(this,&UGameRule_Target::Hand_TargetDestroyed);
	}

	Super::Init();
}

void UGameRule_Target::Hand_TargetDestroyed(AController* causer, int TargetValue)
{
	_AmountRemaining--;
	UE_LOG(LogTemp,Warning,TEXT("%d"),_AmountRemaining)
	BroadcastGameRulePointsScored(causer,TargetValue);
	if(_AmountRemaining== 0)
	{
		BroadcastGameRuleComplete();
	}
}


