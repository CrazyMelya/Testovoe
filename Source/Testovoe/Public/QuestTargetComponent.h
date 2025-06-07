// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DataAssets/QuestDataAsset.h"
#include "QuestTargetComponent.generated.h"

class UWidgetComponent;
class UQuestManagerComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTargetCompleted, UQuestTargetComponent*, Target);

UCLASS(ClassGroup=(Quest), meta=(BlueprintSpawnableComponent))
class TESTOVOE_API UQuestTargetComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UQuestTargetComponent();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest Target")
	bool bIsDynamic = false;

	UFUNCTION(BlueprintCallable, Category = "Quest Target")
	FVector GetWorldLocation() const;

protected:
	UFUNCTION()
	void OnQuestStart(const FName& QuestID, TArray<FQuestObjectiveInfo> Objectives);

	UPROPERTY()
	UQuestManagerComponent* QuestManager;

	UPROPERTY()
	TMap<FName, FQuestObjectiveInfo> QuestsInfo;

private:
	UPROPERTY()
	UWidgetComponent* MarkerWidgetComponent;

	UPROPERTY(EditAnywhere, Category = "Quest Target")
	TSubclassOf<UUserWidget> MarkerWidgetClass;

	void CreateMarkerWidgetComponent();
};
