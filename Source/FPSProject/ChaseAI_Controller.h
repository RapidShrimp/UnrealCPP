// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ChaseAI_Controller.generated.h"

class UAIPerceptionStimuliSourceComponent;
class UAISenseConfig_Sight;
class UAISense;
class UAIPerceptionComponent;
struct FAIStimulus;
;
UCLASS()
class FPSPROJECT_API AChaseAI_Controller : public AAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AChaseAI_Controller();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UAIPerceptionComponent> _AIPerception;

	TObjectPtr<UAISenseConfig_Sight> SightConfig;

	TObjectPtr<UAIPerceptionStimuliSourceComponent> AIStimulus;
	void SetupStimulus();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION()
	void TargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	void SetupAIPerception();
	
	
};
