// Copyright 2022 NegativeNameSeller

#pragma once

#include "CoreMinimal.h"
#include <Editor/UnrealEdTypes.h>
#include <Kismet/KismetSystemLibrary.h>
#include "SlateCore/Public/Input/Events.h"
#include "OpenLogicEditorContext_LevelEd.generated.h"

#pragma region Delegates

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOpenLogicEditorEventsBeginPIESignature, const bool, bIsSimulating);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOpenLogicEditorEventsBeginStandaloneLocalPlaySignature, const int32, ProcessID);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOpenLogicEditorEventsOnNodeEndedSignature, const FGuid&, NodeID, const FGuid&, OldNodeID, int32, PinID);

#pragma endregion


/**
 * 
 */
UCLASS()
class OPENLOGICEDITOR_API UOpenLogicEditorContext_LevelEd : public UObject
{
	GENERATED_BODY()

public:

#pragma region Setup

	virtual ~UOpenLogicEditorContext_LevelEd();

	void Setup();

#pragma endregion

#pragma region OnNodeEnded

	UPROPERTY(BlueprintAssignable)
		FOpenLogicEditorEventsOnNodeEndedSignature OnNodeEnded;

	void HandleOnNodeEnded(FGuid& NodeID, FGuid& OldNodeID, int32 PinID);

#pragma endregion

#pragma region OnPIE

	UPROPERTY()
		bool bIsInPIE = false;
	UPROPERTY()
		bool bIsSimulatingPIE = false;
	UPROPERTY(BlueprintAssignable)
		FOpenLogicEditorEventsBeginPIESignature OnBeginPIE;

	void HandleBeginPIE(const bool bIsSimulating);

	UPROPERTY(BlueprintAssignable)
		FOpenLogicEditorEventsBeginPIESignature OnEndPIE;

	void HandleEndPIE(const bool bIsSimulating);

#pragma endregion

};