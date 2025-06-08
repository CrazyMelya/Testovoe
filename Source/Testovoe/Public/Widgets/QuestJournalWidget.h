// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestManagerComponent.h"
#include "Blueprint/UserWidget.h"
#include "QuestJournalWidget.generated.h"

/**
 * 
 */
UCLASS()
class TESTOVOE_API UQuestJournalWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void SetQuestProgress(const TMap<FName, FQuestProgressInfo>& QuestProgress);
};
