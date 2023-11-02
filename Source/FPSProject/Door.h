// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

class UBoxComponent;

UCLASS()
class FPSPROJECT_API ADoor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADoor();

protected:
	void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<USceneComponent> _Root;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> _Mesh;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UBoxComponent> _Collider;
	
	

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bIsUnlocked;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FVector DoorOffset;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	FVector StartLocation;

	UFUNCTION(BlueprintCallable)
	void DoorLock(bool UnLocked);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OpenDoor();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void CloseDoor();

private:
	void OnCompBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void OnCompEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,int32 OtherBodyIndex);
};
