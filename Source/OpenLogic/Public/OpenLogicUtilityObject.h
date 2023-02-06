// Copyright 2022 NegativeNameSeller

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "OpenLogicUtilityObject.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class OPENLOGIC_API UOpenLogicUtilityObject : public UObject
{
	GENERATED_BODY() public:

	UFUNCTION(BlueprintCallable, Category = "CBluePrintLibrary")
		static TArray<FAssetData>  GetAssetsByClass(const FString& Path, TSubclassOf<UObject> ObjectClass);
};
