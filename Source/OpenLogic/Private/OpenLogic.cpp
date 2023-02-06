// Copyright 2022 NegativeNameSeller

#include "OpenLogic.h"

#define LOCTEXT_NAMESPACE "FOpenLogicModule"

void FOpenLogicModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FOpenLogicModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FOpenLogicModule, OpenLogic)