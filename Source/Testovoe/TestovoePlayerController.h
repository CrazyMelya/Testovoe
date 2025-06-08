// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TestovoePlayerController.generated.h"

class UInputAction;
class UMapWidget;
class UQuestJournalWidget;
class UInputMappingContext;

/**
 *  Basic PlayerController class for a third person game
 *  Manages input mappings
 */
UCLASS(abstract)
class ATestovoePlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	
	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category ="Input", meta = (AllowPrivateAccess = "true"))
	TArray<UInputMappingContext*> DefaultMappingContexts;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_ToggleQuestJournal;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* IA_ToggleMap;

	/** Input mapping context setup */
	virtual void SetupInputComponent() override;

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UQuestJournalWidget> QuestJournalWidgetClass;

	UPROPERTY()
	UQuestJournalWidget* QuestJournalWidget;

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UMapWidget> MapWidgetClass;

	UPROPERTY()
	UMapWidget* MapWidget;

private:
	UFUNCTION()
	void ToggleMap();

	UFUNCTION()
	void ToggleQuestJournal();

	void CreateWidgets();
};
