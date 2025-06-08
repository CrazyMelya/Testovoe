// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestManagerComponent.h"

#include "QuestTargetComponent.h"
#include "AssetRegistry/AssetRegistryModule.h"

#include "DataAssets/QuestDataAsset.h"

FQuestProgressInfo::FQuestProgressInfo(const UQuestDataAsset* Quest)
{
	if (Quest)
	{
		QuestName = Quest->QuestName;
		QuestDescription = Quest->Description;
		for (auto Objective : Quest->Objectives)
		{
			ObjectivesProgress.Add(Objective.ObjectiveTag, false);
		}
	}
}

// Sets default values for this component's properties
UQuestManagerComponent::UQuestManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UQuestManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ThisClass::StartQuests);
}

void UQuestManagerComponent::StartQuest(UQuestDataAsset* Quest)
{
	if (!Quest) return;

	QuestsProgress.Add(Quest->QuestID, FQuestProgressInfo(Quest));
	OnQuestStart.Broadcast(Quest->QuestID, Quest->Objectives);
}

void UQuestManagerComponent::QuestObjectiveComplete(const FName& QuestID, const FName& ObjectiveTag)
{
	if (FQuestProgressInfo* QuestProgress = QuestsProgress.Find(QuestID))
	{
		if (QuestProgress->ObjectivesProgress.Contains(ObjectiveTag))
		{
			QuestProgress->ObjectivesProgress[ObjectiveTag] = true;
		}
		bool QuestCompleted = true;
		for (auto ObjectiveProgress : QuestProgress->ObjectivesProgress)
		{
			if (ObjectiveProgress.Value == false)
			{
				QuestCompleted = false;
				break;
			}
		}
		if (QuestCompleted == true)
		{
			OnQuestCompleted.Broadcast(QuestID);
		}
	}
}

void UQuestManagerComponent::AddTarget(const FName& QuestID, UQuestTargetComponent* QuestTarget)
{
	if (QuestsProgress.Contains(QuestID))
		QuestsProgress[QuestID].QuestTargets.Add(QuestTarget->GetObjectiveTag(), QuestTarget);
}

void UQuestManagerComponent::RemoveTarget(const FName& QuestID, const UQuestTargetComponent* QuestTarget)
{
	if (QuestsProgress.Contains(QuestID))
		QuestsProgress[QuestID].QuestTargets.Remove(QuestTarget->GetObjectiveTag());
}

void UQuestManagerComponent::StartQuests()
{
	auto Quests = GetAllQuestAssets();
	for (auto Quest : Quests)
	{
		StartQuest(Quest);
	}
}

TArray<UQuestDataAsset*> UQuestManagerComponent::GetAllQuestAssets()
{
	TArray<UQuestDataAsset*> QuestAssets;
	
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	
	FARFilter Filter;
	Filter.PackagePaths.Add(FName("/Game/Quests"));
	Filter.bRecursivePaths = true;
	Filter.ClassPaths.Add(UQuestDataAsset::StaticClass()->GetClassPathName());
	
	TArray<FAssetData> AssetDataList;
	AssetRegistryModule.Get().GetAssets(Filter, AssetDataList);

	for (const FAssetData& AssetData : AssetDataList)
	{
		UQuestDataAsset* Quest = Cast<UQuestDataAsset>(AssetData.GetAsset());
		if (Quest)
		{
			QuestAssets.Add(Quest);
		}
	}

	return QuestAssets;
}

TArray<UQuestTargetComponent*> UQuestManagerComponent::GetAllTargets()
{
	TArray<UQuestTargetComponent*> Targets;
	for (auto QuestProgressPair : QuestsProgress)
	{
		TArray<UQuestTargetComponent*> IntermediateTargets;
		QuestProgressPair.Value.QuestTargets.GenerateValueArray(IntermediateTargets);
		Targets.Append(IntermediateTargets);
	}
	return Targets;
}
