// Fill out your copyright notice in the Description page of Project Settings.


#include "Activator.h"


// Sets default values for this component's properties
UActivator::UActivator()
{
}

void UActivator::CallActivate()
{
	if(GetOwner()==nullptr)
		return;
	OnActivated.Broadcast(GetOwner());
}

void UActivator::CallDeactivate()
{
	OnDeactivated.Broadcast();
}
