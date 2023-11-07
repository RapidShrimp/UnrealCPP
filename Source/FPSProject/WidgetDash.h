// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetDash.generated.h"


class UImage;
class UHorizontalBox;
class UTexture2D;

UCLASS()
class FPSPROJECT_API UWidgetDash : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UTexture2D> DashFullImage;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UTexture2D> DashEmptyImage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UImage> DashImage;

	
	virtual void NativeConstruct() override;

	void SetBrush(bool IsFull);
};
