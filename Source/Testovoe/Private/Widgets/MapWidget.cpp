// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/MapWidget.h"

#include "QuestManagerComponent.h"
#include "QuestTargetComponent.h"
#include "TestovoeGameMode.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Widgets/MarkerWidget.h"


void UMapWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (const auto GameMode = GetWorld()->GetAuthGameMode<ATestovoeGameMode>())
	{
		QuestManager = GameMode->QuestManager;
		for (auto Target : QuestManager->GetTargets())
		{
			QuestTargets.Add(Target, CreateWidget<UMarkerWidget>(this, MarkerWidgetClass));
			QuestTargets[Target]->SetMarkerIcon(Target->GetMarkerIcon());
			MarkerSlots.Add(Target, MarkerCanvas->AddChildToCanvas(QuestTargets[Target]));
			if (MarkerSlots[Target])
			{
				MarkerSlots[Target]->SetAnchors(FAnchors(0.5, 0.5));
				MarkerSlots[Target]->SetAlignment(FVector2D(0.5f, 0.5f));
				MarkerSlots[Target]->SetSize(FVector2D(32.f, 32.f));
				MarkerSlots[Target]->SetPosition(ConvertWorldToMap(Target->GetWorldLocation()));
			}
		}
	}
}

void UMapWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	for (auto MarkerSlotSlot : MarkerSlots)
	{
		if (MarkerSlotSlot.Key->GetDynamic())
			MarkerSlotSlot.Value->SetPosition(ConvertWorldToMap(MarkerSlotSlot.Key->GetWorldLocation()));
	}
}

void UMapWidget::NativeDestruct()
{
	Super::NativeDestruct();

	for (auto& Pair : QuestTargets)
	{
		if (Pair.Value)
		{
			Pair.Value->RemoveFromParent();
		}
	}

	QuestTargets.Empty();
	MarkerSlots.Empty();
}

FVector2D UMapWidget::ConvertWorldToMap(const FVector& WorldLocation) const
{
	return FVector2D(WorldLocation.Y * WorldToMapScale.X, WorldLocation.X * -WorldToMapScale.Y);
}
