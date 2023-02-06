// Copyright 2022 NegativeNameSeller

#include "OpenLogicEditor.h"
#include "OpenLogicEditorContext_Manager.h"


#define LOCTEXT_NAMESPACE "FOpenLogicEditorModule"

void FOpenLogicEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	ContextManagerPtr = MakeWeakObjectPtr(const_cast<UOpenLogicEditorContext_Manager*>(GetDefault<UOpenLogicEditorContext_Manager>()));

}

void FOpenLogicEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	ContextManagerPtr = nullptr;

}

UOpenLogicEditorContext_Manager& FOpenLogicEditorModule::GetContextManager() const
{
	return *ContextManagerPtr;
}


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FOpenLogicEditorModule, OpenLogicEditor)