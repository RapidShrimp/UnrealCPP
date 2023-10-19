// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameRule.h"
#include "Target.h"
#include "GameRule_Target.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FPSPROJECT_API UGameRule_Target : public UGameRule
{
	GENERATED_BODY()

public:
	UGameRule_Target();

	virtual void Init() override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UTarget>> _Target;

	int _AmountRemaining;

	UFUNCTION()
	void Hand_TargetDestroyed(AController* causer, int TargetValue);
};
