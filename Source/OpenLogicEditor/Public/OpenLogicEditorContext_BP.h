// Copyright 2022 NegativeNameSeller

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "OpenLogicEditorContext_BP.generated.h"

class UOpenLogicEditorContext_LevelEd;

/**
 * 
 */
UCLASS()
class OPENLOGICEDITOR_API UOpenLogicEditorContext_BP : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

#pragma region GetContext
		UFUNCTION(BlueprintPure, Category = "OpenLogicEditor")
		static UOpenLogicEditorContext_LevelEd* GetOpenLogicEditorContext();
#pragma endregion

	
};
