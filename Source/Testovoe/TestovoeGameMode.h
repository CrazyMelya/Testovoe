// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TestovoeGameMode.generated.h"

/**
 *  Simple GameMode for a third person game
 */
UCLASS(abstract)
class ATestovoeGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	/** Constructor */
	ATestovoeGameMode();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UQuestManagerComponent* QuestManager;
	
};



