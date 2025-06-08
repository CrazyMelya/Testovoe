// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestTargetComponent.h"

#include "QuestManagerComponent.h"
#include "TestovoeGameMode.h"
#include "Components/WidgetComponent.h"
#include "Widgets/MarkerWidget.h"


// Sets default values for this component's properties
UQuestTargetComponent::UQuestTargetComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UQuestTargetComponent::BeginPlay()
{
	Super::BeginPlay();

	if (const ATestovoeGameMode* GameMode = GetWorld()->GetAuthGameMode<ATestovoeGameMode>())
	{
		QuestManager = GameMode->QuestManager;
		if (QuestManager)
		{
			QuestManager->OnQuestStart.AddDynamic(this, &ThisClass::OnQuestStart);
		}
	}
}

FVector UQuestTargetComponent::GetWorldLocation() const
{
	return GetOwner() ? GetOwner()->GetActorLocation() : FVector::ZeroVector;
}

UTexture2D* UQuestTargetComponent::GetMarkerIcon() const
{
	return MarkerIcon;
}

void UQuestTargetComponent::CompleteQuestObjective()
{
	if (!ActiveQuestID.IsNone())
	{
		QuestManager->QuestObjectiveComplete(ActiveQuestID, ObjectiveTag);
		ActiveQuestID = NAME_None;
		DestroyMarkerWidgetComponent();
	}
}

void UQuestTargetComponent::OnQuestStart(const FName& QuestID, TArray<FQuestObjectiveInfo> Objectives)
{
	for (auto Objective : Objectives)
	{
		if (ObjectiveTag == Objective.ObjectiveTag)
		{
			QuestManager->AddTarget(QuestID, this);
			CreateMarkerWidgetComponent();
			if (ActiveQuestID.IsNone())
				ActiveQuestID = QuestID;
		}
	}
}

void UQuestTargetComponent::CreateMarkerWidgetComponent()
{
	if (!MarkerWidgetComponent)
	{
		if (AActor* Owner = GetOwner())
		{
			MarkerWidgetComponent = NewObject<UWidgetComponent>(Owner);
			if (MarkerWidgetComponent && MarkerWidgetClass)
			{
				MarkerWidgetComponent->RegisterComponent();
				MarkerWidgetComponent->AttachToComponent(Owner->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
				MarkerWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
				MarkerWidgetComponent->SetDrawAtDesiredSize(true);
				MarkerWidgetComponent->SetWidgetClass(MarkerWidgetClass);
				
				MarkerWidgetComponent->SetRelativeLocation(FVector(0.f, 0.f, 150.f));
				Cast<UMarkerWidget>(MarkerWidgetComponent->GetWidget())->SetMarkerIcon(MarkerIcon);
			}
		}
	}
}

void UQuestTargetComponent::DestroyMarkerWidgetComponent()
{
	MarkerWidgetComponent->Deactivate();
	MarkerWidgetComponent->UnregisterComponent();
	MarkerWidgetComponent->DestroyComponent();
	MarkerWidgetComponent = nullptr;
}


