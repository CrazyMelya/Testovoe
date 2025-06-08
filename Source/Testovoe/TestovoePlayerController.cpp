// Copyright Epic Games, Inc. All Rights Reserved.


#include "TestovoePlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "TestovoeGameMode.h"
#include "Widgets/MapWidget.h"
#include "Widgets/QuestJournalWidget.h"

void ATestovoePlayerController::BeginPlay()
{
	Super::BeginPlay();

	CreateWidgets();
}

void ATestovoePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Add Input Mapping Contexts
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
		{
			Subsystem->AddMappingContext(CurrentContext, 0);
		}
	}
	if (auto EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInput->BindAction(IA_ToggleQuestJournal, ETriggerEvent::Triggered, this, &ThisClass::ToggleQuestJournal);
		EnhancedInput->BindAction(IA_ToggleMap, ETriggerEvent::Triggered, this, &ThisClass::ToggleMap);
	}
}

void ATestovoePlayerController::ToggleMap()
{
	if (!MapWidget) return;

	if (MapWidget->IsInViewport())
	{
		MapWidget->RemoveFromParent();
		bShowMouseCursor = false;
		SetInputMode(FInputModeGameOnly());
		GetPawn()->EnableInput(this);
	}
	else
	{
		MapWidget->AddToViewport();
		bShowMouseCursor = true;
		SetInputMode(FInputModeGameAndUI());
		GetPawn()->DisableInput(this);
	}
}

void ATestovoePlayerController::ToggleQuestJournal()
{
	if (!QuestJournalWidget) return;

	if (QuestJournalWidget->IsInViewport())
	{
		QuestJournalWidget->RemoveFromParent();
		bShowMouseCursor = false;
		SetInputMode(FInputModeGameOnly());
		GetPawn()->EnableInput(this);
	}
	else
	{
		if (auto GameMode = GetWorld()->GetAuthGameMode<ATestovoeGameMode>())
		{
			QuestJournalWidget->SetQuestProgress(GameMode->QuestManager->QuestsProgress);
			QuestJournalWidget->AddToViewport();
			bShowMouseCursor = true;
			SetInputMode(FInputModeGameAndUI());
			GetPawn()->DisableInput(this);
		}
	}
}

void ATestovoePlayerController::CreateWidgets()
{
	if (!QuestJournalWidget)
		QuestJournalWidget = CreateWidget<UQuestJournalWidget>(this, QuestJournalWidgetClass, FName("QuestJournal"));

	if (!MapWidget)
		MapWidget = CreateWidget<UMapWidget>(this, MapWidgetClass, FName("Map"));
}
