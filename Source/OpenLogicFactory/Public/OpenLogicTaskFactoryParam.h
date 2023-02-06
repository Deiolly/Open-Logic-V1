// Copyright 2022 NegativeNameSeller

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "OpenLogicTaskFactoryParam.generated.h"

/**
 * 
 */
UCLASS()
class OPENLOGICFACTORY_API UOpenLogicTaskFactoryParam : public UFactory
{
	GENERATED_BODY()

public:

	UOpenLogicTaskFactoryParam();
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;

};
