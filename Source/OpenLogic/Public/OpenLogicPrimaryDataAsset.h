// Copyright 2022 NegativeNameSeller

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "OpenLogicBaseTask.h"
#include "OpenLogicPrimaryDataAsset.generated.h"


USTRUCT(BlueprintType)
struct FPinID
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PinID")
		FGuid UniqueID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PinID")
		int PinID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PinID")
		FString PinName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PinID")
		TSubclassOf<UOpenLogicBaseParam> SwitchPinClass;
};


USTRUCT(BlueprintType)
struct FOLNode
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OLNode")
		TSubclassOf<UOpenLogicBaseTask> Task;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OLNode")
		FVector2D Position;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OLNode")
		FVector2D Size;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OLNode")
		TArray<FPinID> Input;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OLNode")
		TArray<FPinID> Output;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OLNode")
		FString Content;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OLNode")
		FString Description;

};


UCLASS()
class OPENLOGIC_API UOpenLogicPrimaryDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY() public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NodeAsset")
			TMap<FGuid, FOLNode> Node;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NodeAsset")
			TMap<FString, FGuid> Events;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NodeAsset")
			FVector2D EditorGraphPosition = FVector2D(0.0, 0.0);
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NodeAsset")
			float EditorZoomScale = 1.0;

};
