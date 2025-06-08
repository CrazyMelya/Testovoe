// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DataAssets/QuestDataAsset.h"
#include "QuestManagerComponent.generated.h"

class UQuestDataAsset;
class UQuestTargetComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnQuestStart, const FName&, QuestID, TArray<FQuestObjectiveInfo>, Objectives);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestCompleted, const FName&, QuestID);

USTRUCT(BlueprintType)
struct FQuestProgressInfo
{
	GENERATED_BODY()

	FQuestProgressInfo() {};
	FQuestProgressInfo(const UQuestDataAsset* Quest);

	UPROPERTY(BlueprintReadOnly)
	FText QuestName;

	UPROPERTY(BlueprintReadOnly)
	FText QuestDescription;

	UPROPERTY(BlueprintReadOnly)
	TMap<FName, UQuestTargetComponent*> QuestTargets;
	
	UPROPERTY(BlueprintReadOnly)
	TMap<FName, bool> ObjectivesProgress;
	
	UPROPERTY(BlueprintReadOnly)
	bool bComplete = false;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTOVOE_API UQuestManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UQuestManagerComponent();

	void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void StartQuest(UQuestDataAsset* Quest);

	UPROPERTY()
	TMap<FName, FQuestProgressInfo> QuestsProgress;

	UPROPERTY(BlueprintAssignable)
	FOnQuestStart OnQuestStart;

	UPROPERTY(BlueprintAssignable)
	FOnQuestCompleted OnQuestCompleted;

	void QuestObjectiveComplete(const FName& QuestID, const FName& ObjectiveTag);

	void AddTarget(const FName& QuestID, UQuestTargetComponent* QuestTarget);

	void RemoveTarget(const FName& QuestID, const UQuestTargetComponent* QuestTarget);

	TArray<UQuestTargetComponent*> GetAllTargets();

private:
	UFUNCTION()
	void StartQuests();

	TArray<UQuestDataAsset*> GetAllQuestAssets();
};
