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

protected:
	UFUNCTION()
	void OnQuestStart(const FName& QuestID, TArray<FQuestObjectiveInfo> Objectives);

	UPROPERTY()
	UQuestManagerComponent* QuestManager;

	UPROPERTY()
	TMap<FName, FQuestObjectiveInfo> QuestsInfo;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Quest Target")
	bool bIsDynamic = false;

private:
	UPROPERTY()
	UWidgetComponent* MarkerWidgetComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Quest Target")
	TSubclassOf<UMarkerWidget> MarkerWidgetClass;

	void CreateMarkerWidgetComponent();

	FName CurrentQuestID;
	
	UPROPERTY()
	UTexture2D* MarkerIcon;
};
