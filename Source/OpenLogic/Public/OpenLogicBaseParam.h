// Copyright 2022 NegativeNameSeller

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "OpenLogicBaseParam.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class OPENLOGIC_API UOpenLogicBaseParam : public UObject
{
	GENERATED_BODY() public:

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Param", meta = (ExposeOnSpawn))
		FString ParamType = "Exec";

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Param", meta = (ExposeOnSpawn))
		FColor ParamColor = FColor(255, 255, 255, 255);
	
};
