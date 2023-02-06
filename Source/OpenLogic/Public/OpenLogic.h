// Copyright 2022 NegativeNameSeller

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FOpenLogicModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;


private:

};
