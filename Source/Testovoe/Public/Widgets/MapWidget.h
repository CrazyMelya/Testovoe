// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MapWidget.generated.h"

class UCanvasPanelSlot;
class UCanvasPanel;
class UMarkerWidget;
class UQuestTargetComponent;
class UQuestManagerComponent;
/**
 * 
 */
UCLASS()
class TESTOVOE_API UMapWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void NativeDestruct() override;

protected:
	UPROPERTY(BlueprintReadOnly)
	TMap<UQuestTargetComponent*, UMarkerWidget*> QuestTargets;

	UPROPERTY(BlueprintReadOnly)
	TMap<UQuestTargetComponent*, UCanvasPanelSlot*> MarkerSlots;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMarkerWidget> MarkerWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Map")
	FVector2D WorldToMapScale = FVector2D(1.0f, 1.0f);
	
	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* MarkerCanvas;

private:
	UPROPERTY()
	UQuestManagerComponent* QuestManager;

	FVector2D ConvertWorldToMap(const FVector& WorldLocation) const;
};
