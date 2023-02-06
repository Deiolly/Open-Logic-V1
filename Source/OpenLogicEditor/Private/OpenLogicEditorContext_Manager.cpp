// Copyright 2022 NegativeNameSeller

#include "OpenLogicEditorContext_Manager.h"
#include "OpenLogicEditorContext_LevelEd.h"

UOpenLogicEditorContext_LevelEd* UOpenLogicEditorContext_Manager::GetLevelEditorContext()
{
	if (LevelEditorContext == nullptr) {
		LevelEditorContext = NewObject<UOpenLogicEditorContext_LevelEd>();
		LevelEditorContext->Setup();
	}
	return LevelEditorContext;
}
