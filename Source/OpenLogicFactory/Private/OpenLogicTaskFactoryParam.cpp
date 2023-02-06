// Copyright 2022 NegativeNameSeller

#include "OpenLogicTaskFactoryParam.h"
#include "OpenLogicBaseParam.h"
#include "OpenLogicBaseTaskParamBlueprint.h"
#include "AssetTypeCategories.h"
#include "Kismet2/KismetEditorUtilities.h"

UOpenLogicTaskFactoryParam::UOpenLogicTaskFactoryParam()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UOpenLogicBaseParam::StaticClass();
}

UObject* UOpenLogicTaskFactoryParam::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext)
{
	if (FKismetEditorUtilities::CanCreateBlueprintOfClass(SupportedClass) == true)
	{
		UOpenLogicBaseTaskParamBlueprint* Task = CastChecked<UOpenLogicBaseTaskParamBlueprint>(FKismetEditorUtilities::CreateBlueprint(UOpenLogicBaseParam::StaticClass(), InParent, InName, BPTYPE_Normal, UOpenLogicBaseTaskParamBlueprint::StaticClass(), UBlueprintGeneratedClass::StaticClass(), CallingContext));
		return Task;
	}
	else {return nullptr;}
}