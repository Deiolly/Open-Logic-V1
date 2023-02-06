// Copyright 2022 NegativeNameSeller

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "OpenLogicEditorContext_Manager.generated.h"

class UOpenLogicEditorContext_LevelEd;

/**
 * 
 */
UCLASS()
class OPENLOGICEDITOR_API UOpenLogicEditorContext_Manager : public UObject
{
	GENERATED_BODY()
public:
	UOpenLogicEditorContext_LevelEd* GetLevelEditorContext();

protected:
	UPROPERTY() 
		UOpenLogicEditorContext_LevelEd* LevelEditorContext;

};
