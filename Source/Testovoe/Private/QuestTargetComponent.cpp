// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestTargetComponent.h"

#include "QuestManagerComponent.h"
#include "TestovoeGameMode.h"
#include "Components/WidgetComponent.h"
#include "DataAssets/QuestDataAsset.h"
#include "Kismet/GameplayStatics.h"


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

void UQuestTargetComponent::OnQuestStart(const FName& QuestID, TArray<FQuestObjectiveInfo> Objectives)
{
	for (auto Objective : Objectives)
	{
		if (ComponentTags.Contains(Objective.ObjectiveTag))
		{
			// CreateMarkerWidgetComponent();
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("Quest started: %s"), *QuestID.ToString()));
			QuestsInfo.Add(QuestID, Objective);
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
			if (MarkerWidgetComponent)
			{
				MarkerWidgetComponent->RegisterComponent();
				MarkerWidgetComponent->AttachToComponent(Owner->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
				MarkerWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
				MarkerWidgetComponent->SetDrawAtDesiredSize(true);
				
				if (MarkerWidgetClass)
				{
					MarkerWidgetComponent->SetWidgetClass(MarkerWidgetClass);
				}
				
				MarkerWidgetComponent->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
			}
		}
	}
}


