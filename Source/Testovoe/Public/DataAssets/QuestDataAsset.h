// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "QuestDataAsset.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FQuestObjectiveInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName ObjectiveTag;
};

UCLASS(BlueprintType)
class TESTOVOE_API UQuestDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName QuestID;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText QuestName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FQuestObjectiveInfo> Objectives;
};

