// Copyright 2022 NegativeNameSeller

#include "OpenLogicTaskFactory.h"
#include "OpenLogicPrimaryDataAsset.h"
#include "AssetTypeCategories.h"

UOpenLogicTaskFactory::UOpenLogicTaskFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UOpenLogicPrimaryDataAsset::StaticClass();
}

UObject* UOpenLogicTaskFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UOpenLogicPrimaryDataAsset>(InParent, InClass, InName, Flags);
}