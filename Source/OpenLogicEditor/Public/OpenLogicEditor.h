// Copyright 2022 NegativeNameSeller

#pragma once

#include "Modules/ModuleManager.h"

class FOpenLogicEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	TWeakObjectPtr<class UOpenLogicEditorContext_Manager> ContextManagerPtr;
	virtual UOpenLogicEditorContext_Manager& GetContextManager() const;
};
