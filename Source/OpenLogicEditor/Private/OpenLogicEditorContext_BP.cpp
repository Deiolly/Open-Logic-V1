// Copyright 2022 NegativeNameSeller

#include "OpenLogicEditorContext_BP.h"
#include "OpenLogicEditorContext_LevelEd.h"
#include "OpenLogicEditorContext_Manager.h"
#include "OpenLogicEditor.h"

#pragma region GetContexts

UOpenLogicEditorContext_LevelEd* UOpenLogicEditorContext_BP::GetOpenLogicEditorContext()
{
#if WITH_EDITOR


	FOpenLogicEditorModule& OpenLogicEditorScript = FModuleManager::Get().LoadModuleChecked<FOpenLogicEditorModule>(TEXT("OpenLogicEditor"));
	return OpenLogicEditorScript.GetContextManager().GetLevelEditorContext();
#endif
	return nullptr;
}