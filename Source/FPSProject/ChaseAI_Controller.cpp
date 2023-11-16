// Fill out your copyright notice in the Description page of Project Settings.


#include "ChaseAI_Controller.h"

#include "AI_Character.h"
#include "FPSProjectCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AChaseAI_Controller::AChaseAI_Controller()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	SetupAIPerception();
}

void AChaseAI_Controller::BeginPlay()
{
	Super::BeginPlay();
}

void AChaseAI_Controller::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if(AAI_Character* AI = Cast<AAI_Character>(InPawn))
	{
		RunBehaviorTree(AI->BTree);
	}
}



void AChaseAI_Controller::TargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if(AFPSProjectCharacter* Player = Cast<AFPSProjectCharacter>(Actor) )
	{
		Blackboard->SetValueAsBool("CanSeePlayer",Stimulus.WasSuccessfullySensed());
	}
}

void AChaseAI_Controller::SetupAIPerception()
{
	_AIPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception Comp"));
	SetPerceptionComponent(*_AIPerception);
	
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SightConfig->SightRadius = 500.0f;
	SightConfig->LoseSightRadius = SightConfig->SightRadius + 50.0f;
	SightConfig->PeripheralVisionAngleDegrees = 90;
	SightConfig->SetMaxAge(5);
	SightConfig->AutoSuccessRangeFromLastSeenLocation = 900.0f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals= true;
	
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddUniqueDynamic(this,&AChaseAI_Controller::TargetPerceptionUpdated);
	SetupStimulus();

}

void AChaseAI_Controller::SetupStimulus()
{
	AIStimulus = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus"));
	AIStimulus->RegisterForSense(TSubclassOf<UAISense_Sight>());
	AIStimulus->RegisterWithPerceptionSystem();
}



