// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableComp.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FSetInteractPromptSignature, FString, newInteractText, FLinearColor, newColour,float, newInteractTime);

class USphereComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FPSPROJECT_API UInteractableComp : public UPrimitiveComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInteractableComp();

	UPROPERTY(BlueprintAssignable)
	FSetInteractPromptSignature OnSetInteractPrompt;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USphereComponent> _Collider;

	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanInteract;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _InteractSphereSize;
private:
	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
