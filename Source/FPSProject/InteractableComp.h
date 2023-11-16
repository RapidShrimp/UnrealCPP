// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableComp.generated.h"

class USphereComponent;

//
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class FPSPROJECT_API UInteractableComp : public UPrimitiveComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInteractableComp();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USphereComponent> _Collider;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FLinearColor InteractColour = FLinearColor{0,0,0,1};

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float InteractTime = 0;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FString InteractText = "" ;

	void DoParentInteract(AActor* Interacting);
	void SetCanInteract(bool CanInteract);
	
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float _InteractSphereSize = 75.0f;
private:

	bool bCanInteract = true;
	
	virtual void DestroyComponent(bool bPromoteChildren) override;
	virtual void OnAttachmentChanged() override;
	
	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
