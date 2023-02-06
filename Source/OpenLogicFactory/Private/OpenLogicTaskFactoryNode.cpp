// Copyright 2022 NegativeNameSeller

#include "OpenLogicTaskFactoryNode.h"
#include "OpenLogicBaseTask.h"
#include "OpenLogicBaseTaskBlueprint.h"
#include "AssetTypeCategories.h"
#include "Kismet2/KismetEditorUtilities.h"

UOpenLogicTaskFactoryNode::UOpenLogicTaskFactoryNode()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UOpenLogicBaseTask::StaticClass();
}

UObject* UOpenLogicTaskFactoryNode::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext)
{
	if (FKismetEditorUtilities::CanCreateBlueprintOfClass(SupportedClass) == true)
	{
		UOpenLogicBaseTaskBlueprint* Task = CastChecked<UOpenLogicBaseTaskBlueprint>(FKismetEditorUtilities::CreateBlueprint(UOpenLogicBaseTask::StaticClass(), InParent, InName, BPTYPE_Normal, UOpenLogicBaseTaskBlueprint::StaticClass(), UBlueprintGeneratedClass::StaticClass(), CallingContext));
		return Task;
	}
	else {return nullptr;}
}