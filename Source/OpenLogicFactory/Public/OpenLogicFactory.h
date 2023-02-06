// Copyright 2022 NegativeNameSeller

#pragma once

#include "Modules/ModuleManager.h"

class FOpenLogicFactoryModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;


};
