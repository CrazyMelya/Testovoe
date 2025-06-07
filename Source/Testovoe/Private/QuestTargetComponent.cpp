// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestTargetComponent.h"


// Sets default values for this component's properties
UQuestTargetComponent::UQuestTargetComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UQuestTargetComponent::MarkCompleted()
{
	if (!bCompleted)
	{
		bCompleted = true;
		OnTargetCompleted.Broadcast(this);
	}
}

FVector UQuestTargetComponent::GetWorldLocation() const
{
	return GetOwner() ? GetOwner()->GetActorLocation() : FVector::ZeroVector;
}


