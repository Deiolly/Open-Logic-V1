// Copyright 2022 NegativeNameSeller

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "OpenLogicTaskFactory.generated.h"

/**
 * 
 */
UCLASS()
class OPENLOGICFACTORY_API UOpenLogicTaskFactory : public UFactory
{
	GENERATED_BODY()

public:

	UOpenLogicTaskFactory();
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;

};
