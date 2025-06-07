// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestManagerComponent.h"

#include "AssetRegistry/AssetRegistryModule.h"
#include "DataAssets/QuestDataAsset.h"
#include "Kismet/GameplayStatics.h"

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

	OnQuestStart.Broadcast(Quest->QuestID, Quest->Objectives);
}

void UQuestManagerComponent::QuestObjectiveComplete(const FName& QuestID, const FName& ObjectiveTag)
{
	if (FQuestProgress* QuestProgress = QuestsProgress.Find(QuestID))
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

void UQuestManagerComponent::StartQuests()
{
	auto Quests = GetAllQuestAssets();
	for (auto Quest : Quests)
	{
		FQuestProgress NewQuestProgress;
		for (auto Objective : Quest->Objectives)
		{
			NewQuestProgress.ObjectivesProgress.Add(Objective.ObjectiveTag, false);
		}
		QuestsProgress.Add(Quest->QuestID, NewQuestProgress);
		OnQuestStart.Broadcast(Quest->QuestID, Quest->Objectives);
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

	// Получаем ассеты
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
