// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestManagerComponent.generated.h"

class UQuestDataAsset;
class UQuestTargetComponent;

USTRUCT()
struct FQuestProgress
{
	GENERATED_BODY()

	UPROPERTY()
	FName QuestID;
	
	UPROPERTY()
	bool bComplete;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTOVOE_API UQuestManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UQuestManagerComponent();
	
	UFUNCTION(BlueprintCallable)
	void StartQuest(UQuestDataAsset* Quest);

	UPROPERTY()
	TArray<FQuestProgress> QuestProgress;
};
