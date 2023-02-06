// Copyright 2022 NegativeNameSeller

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <OpenLogicPrimaryDataAsset.cpp>
#include <OpenLogicBaseTask.h>
#include <OpenLogicRuntimeInstancer.h>
#include "OpenLogicRuntimeWorker.generated.h"
/**
 *
 */
UCLASS(Blueprintable)
class OPENLOGIC_API UOpenLogicRuntimeWorker : public UObject
{
GENERATED_BODY() public:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Base", meta = (ExposeOnSpawn))
		TArray<FGuid> AssetNodeID;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Base", meta = (ExposeOnSpawn))
		TArray<FOLNode> AssetNodeData;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Base", meta = (ExposeOnSpawn))
		class UOpenLogicPrimaryDataAsset* Asset;


	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Base", meta = (ExposeOnSpawn))
		TMap<FString, FGuid> RegisteredEvent;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Base")
		TMap<FGuid, UOpenLogicBaseTask*> CalledNode;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Base", meta = (ExposeOnSpawn))
		FString BeginEvent;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Runtime")
		bool isInstanceActive = false;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Runtime")
		UOpenLogicRuntimeInstancer* ComponentParent;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Runtime", meta = (ExposeOnSpawn))
		UActorComponent* Component;





	UFUNCTION(BlueprintCallable, Category = "Runtime")
		void CreateNodes();

	UFUNCTION(BlueprintCallable, Category = "Runtime")
		void RunInstance();
	UFUNCTION(BlueprintCallable, Category = "Runtime")
		void GlobalCall(FString Event);
	UFUNCTION(BlueprintCallable, Category = "Runtime")
		void NodeEnded(UOpenLogicBaseTask* BaseTask, int32 PinID);
	UFUNCTION(BlueprintCallable, Category = "DDL", meta = (DeterminesOutputType = "ParamClass"))
		UOpenLogicBaseParam* CreateParam(UOpenLogicBaseTask* Node, TSubclassOf<class UOpenLogicBaseParam> ParamClass, int32 OutputPin)
	{
		UOpenLogicBaseParam* OutObj = Node->OutParam.FindChecked(OutputPin);
		return OutObj;
	}

	UFUNCTION(BlueprintPure, Category = "DDL", meta = (DeterminesOutputType = "ParamClass"))
		UOpenLogicBaseParam* GetParam(UOpenLogicBaseTask* Node, TSubclassOf<class UOpenLogicBaseParam> ParamClass, int32 InputPin)
	{
		int32 SelfID = AssetNodeID.Find(Node->NodeID);
		FOLNode& SelfData = AssetNodeData[SelfID];

		FGuid OutUniqueID = SelfData.Input[InputPin].UniqueID;

		if (OutUniqueID.IsValid() && CalledNode.Contains(OutUniqueID)) {
			UOpenLogicBaseTask* Element = CalledNode[OutUniqueID];

			int32 OutPinID = SelfData.Input[InputPin].PinID;
			int32 OutID = AssetNodeID.Find(OutUniqueID);
			FOLNode& OutData = AssetNodeData[OutID];
			
			if (Element->OutParam.Contains(OutPinID)) {
				UOpenLogicBaseParam* param = Element->OutParam.FindChecked(OutPinID);
				return param;
			}
		}
		return nullptr;
	}
};
