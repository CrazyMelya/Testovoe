// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DataAssets/QuestDataAsset.h"
#include "QuestTargetComponent.generated.h"

class UMarkerWidget;
class UWidgetComponent;
class UQuestManagerComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTargetCompleted, UQuestTargetComponent*, Target);

UCLASS(ClassGroup=(Quest), abstract, meta=(BlueprintSpawnableComponent), Blueprintable)
class TESTOVOE_API UQuestTargetComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UQuestTargetComponent();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Quest Target")
	FVector GetWorldLocation() const;

	UFUNCTION(BlueprintCallable, Category = "Quest Target")
	UTexture2D* GetMarkerIcon() const;

	bool GetDynamic() const { return bIsDynamic; }

	UFUNCTION(BlueprintCallable, Category = "Quest Target")
	void CompleteQuestObjective();

	UPROPERTY()
	UQuestManagerComponent* QuestManager = nullptr;

	FName GetObjectiveTag() const { return ObjectiveTag; }

	UFUNCTION(BlueprintCallable, Category = "Quest Target")
	FText GetObjectiveName() const { return ObjectiveName; }

	bool IsTargetActive() const { return !ActiveQuestID.IsNone(); }

protected:
	UFUNCTION()
	void OnQuestStart(const FName& QuestID, TArray<FQuestObjectiveInfo> Objectives);

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Quest Target")
	FName ObjectiveTag = NAME_None;;
	
	UPROPERTY()
	FName ActiveQuestID = NAME_None;;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Quest Target")
	bool bIsDynamic = false;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Quest Target")
	UTexture2D* MarkerIcon = nullptr;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Quest Target")
	FText ObjectiveName;


private:
	UPROPERTY()
	UWidgetComponent* MarkerWidgetComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Quest Target")
	TSubclassOf<UMarkerWidget> MarkerWidgetClass;

	void CreateMarkerWidgetComponent();

	void DestroyMarkerWidgetComponent();
};
