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
protected:

	bool bInit = false;
	
public:

	TArray<TObjectPtr<UImage>> DashArr;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UTexture2D> DashFullImage;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UTexture2D> DashEmptyImage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UHorizontalBox> DashContainer;

	
	virtual void NativeConstruct() override;

	void Init(int MaxDashes);
	
	TObjectPtr<UImage> BaseImageClass;
	void OnDashUpdate(int CurrentDashes, int MaxDashes);

};
