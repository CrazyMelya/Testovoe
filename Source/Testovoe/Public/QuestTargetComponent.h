// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "QuestTargetComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTargetCompleted, UQuestTargetComponent*, Target);

UCLASS(ClassGroup=(Quest), meta=(BlueprintSpawnableComponent))
class TESTOVOE_API UQuestTargetComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UQuestTargetComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest")
	bool bIsDynamic = false;

	UPROPERTY(BlueprintAssignable, Category = "Quest")
	FOnTargetCompleted OnTargetCompleted;

	UFUNCTION(BlueprintCallable, Category = "Quest")
	void MarkCompleted();

	UFUNCTION(BlueprintCallable, Category = "Quest")
	bool IsCompleted() const { return bCompleted; }

	UFUNCTION(BlueprintCallable, Category = "Quest")
	FVector GetWorldLocation() const;

protected:
	bool bCompleted = false;
};
