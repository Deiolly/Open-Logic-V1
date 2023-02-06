// Copyright 2022 NegativeNameSeller

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "OpenLogicTaskFactoryNode.generated.h"

/**
 * 
 */
UCLASS()
class OPENLOGICFACTORY_API UOpenLogicTaskFactoryNode : public UFactory
{
	GENERATED_BODY()

public:

	UOpenLogicTaskFactoryNode();
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;

};
