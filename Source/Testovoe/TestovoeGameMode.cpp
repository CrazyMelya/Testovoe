// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestovoeGameMode.h"

#include "QuestManagerComponent.h"

ATestovoeGameMode::ATestovoeGameMode()
{
	// stub
	QuestManager = CreateDefaultSubobject<UQuestManagerComponent>(TEXT("QuestManager"));
}
