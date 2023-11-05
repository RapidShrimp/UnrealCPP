// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetDash.generated.h"


class UHorizontalBox;
class UImage;

UCLASS()
class FPSPROJECT_API UWidgetDash : public UUserWidget
{
	GENERATED_BODY()
protected:
	
	TArray<TObjectPtr<UImage>> DashesArr;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UImage* _ImageWidgetClass;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UTexture2D> DashFullImage;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UTexture2D> DashEmptyImage;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHorizontalBox> DashContainer;
public:
	void OnDashUpdate(int CurrentDashes, int MaxDashes);

private:
	bool bIsInit = false;
	void Init(int Dashes);
};
