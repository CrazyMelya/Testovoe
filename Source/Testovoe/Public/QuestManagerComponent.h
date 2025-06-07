// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestManagerComponent.generated.h"

class UQuestDataAsset;
class UQuestTargetComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnQuestStart, const FName&, QuestID, TArray<FQuestObjectiveInfo>, Objectives);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestCompleted, const FName&, QuestID);

USTRUCT()
struct FQuestProgress
{
	GENERATED_BODY()

	UPROPERTY()
	TMap<FName, bool> ObjectivesProgress;
	
	UPROPERTY()
	bool bComplete;
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
	TMap<FName, FQuestProgress> QuestsProgress;

	UPROPERTY(BlueprintAssignable)
	FOnQuestStart OnQuestStart;

	UPROPERTY(BlueprintAssignable)
	FOnQuestCompleted OnQuestCompleted;

	void QuestObjectiveComplete(const FName& QuestID, const FName& ObjectiveTag);

private:
	UFUNCTION()
	void StartQuests();

	TArray<UQuestDataAsset*> GetAllQuestAssets();
};
