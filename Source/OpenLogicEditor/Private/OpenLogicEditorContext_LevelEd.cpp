// Copyright 2022 NegativeNameSeller

#include "OpenLogicEditorContext_LevelEd.h"
#include <GameFramework/Actor.h>
#include <Editor.h>
#include <LevelEditor.h>
#include <EdMode.h>
#include "Framework/Application/SlateApplication.h"
#include <EditorViewportClient.h>
#include <LevelEditorViewport.h>
#include <PhysicsEngine/PhysicsSettings.h>
#include "SlateCore/Public/Input/Events.h"
#include <EditorModeManager.h>
#include <EditorModeTools.h>



#pragma region Setup

UOpenLogicEditorContext_LevelEd::~UOpenLogicEditorContext_LevelEd()
{
#if WITH_EDITOR
	UE_LOG(LogTemp, Log, TEXT("UOpenLogicEditorContext_LevelEditor:: Cleanup"));

	if (!GEditor) return;

	FEditorDelegates::BeginPIE.RemoveAll(this);
	FEditorDelegates::EndPIE.RemoveAll(this);
	FEditorDelegates::PausePIE.RemoveAll(this);
	FEditorDelegates::ResumePIE.RemoveAll(this);

#endif // WITH_EDITOR
}


void UOpenLogicEditorContext_LevelEd::Setup()
{
#if WITH_EDITOR
	if (!GEditor) {
		UE_LOG(LogTemp, Error, TEXT("UOpenLogicEditorContext_LevelEditor::Setup() Failed to get a valid GEditor, this is a showstopper!!"));
		return;
	}
	FEditorDelegates::BeginPIE.AddUObject(this, &UOpenLogicEditorContext_LevelEd::HandleBeginPIE);
	FEditorDelegates::EndPIE.AddUObject(this, &UOpenLogicEditorContext_LevelEd::HandleEndPIE);


#endif // WITH_EDITOR
}

#pragma endregion

#pragma region HandleLevelActorEvents

void UOpenLogicEditorContext_LevelEd::HandleOnNodeEnded(FGuid& ID, FGuid& OldNodeID, int32 PinID)
{
	OnNodeEnded.Broadcast(ID, OldNodeID, PinID);
}

#pragma region PIE

void UOpenLogicEditorContext_LevelEd::HandleBeginPIE(const bool bIsSimulating)
{
	bIsInPIE = true;
	bIsSimulatingPIE = bIsSimulating;
	OnBeginPIE.Broadcast(bIsSimulating);
}

void UOpenLogicEditorContext_LevelEd::HandleEndPIE(const bool bIsSimulating)
{
	bIsInPIE = false;
	bIsSimulatingPIE = bIsSimulating;
	OnEndPIE.Broadcast(bIsSimulating);
}

#pragma endregion