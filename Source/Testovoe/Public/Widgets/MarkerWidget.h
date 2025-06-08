// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MarkerWidget.generated.h"

/**
 * 
 */
UCLASS()
class TESTOVOE_API UMarkerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetMarkerIcon(UTexture2D* InMarkerIcon);
	
protected:
	UPROPERTY(BlueprintReadOnly)
	UTexture2D* MarkerIcon;
	
};
