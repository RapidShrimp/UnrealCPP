// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon_Hitscan.h"

#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AWeapon_Hitscan::AWeapon_Hitscan()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	_Damage = 10.0f;
	_Range = 50.0f;
}

bool AWeapon_Hitscan::Fire_Implementation()
{
	FVector StartLoc = _Arrow->GetComponentLocation();
	FVector EndLoc = StartLoc + _Arrow->GetForwardVector() * _Range;
	FHitResult Hit;
	if(UKismetSystemLibrary::LineTraceSingle(GetWorld(),StartLoc,EndLoc,
	UEngineTypes::ConvertToTraceType(ECC_Visibility),
	true,{this, GetOwner()},EDrawDebugTrace::ForDuration,
	Hit,true,FLinearColor::Red,FLinearColor::Green, 5.0f))
{
	UGameplayStatics::ApplyDamage(Hit.GetActor(),_Damage,GetInstigator()->GetController(),this,UDamageType::StaticClass());
		return  true;
}
	return false;
}


