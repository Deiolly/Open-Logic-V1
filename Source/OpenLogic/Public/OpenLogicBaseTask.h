// Copyright 2022 NegativeNameSeller

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Tickable.h"
#include "OL_BaseWidget.h"
#include "OpenLogicBaseParam.h"
#include "OpenLogicBaseTask.generated.h"

UENUM(BlueprintType)
enum class EPinType : uint8
{
	Input,
	Output
};

UENUM(BlueprintType)
enum class ENodeType : uint8
{
	Function,
	Event
};

USTRUCT(BlueprintType)
struct FPinData
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PinData")
		EPinType PinType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PinData")
		FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PinData")
		FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PinData")
		TSubclassOf<UOpenLogicBaseParam> ParamClass;
};


USTRUCT(BlueprintType)
struct FNodeInfo
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Info")
		FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Info")
		FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PinData")
		TArray<FString> Categories;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Info")
		float NodeHeight = 120;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Info")
		FColor TaskColor = FColor(255, 255, 255, 255);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Info")
		TArray<FPinData> Pins;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Info")
		TSubclassOf<UOL_BaseWidget> ContentWidget;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Info")
		ENodeType NodeType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Info")
		bool makePayload;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Info")
		TArray<FString> AddInLibrary;
};

/**
 * 
 */

struct FOLNode;

UCLASS(Blueprintable, hidecategories = ("Hidden"))
class OPENLOGIC_API UOpenLogicBaseTask : public UObject
{
	GENERATED_BODY() public:



	// UWorld Link
		virtual UWorld* GetWorld() const override;


	UFUNCTION(BlueprintPure, Category = "Task")
	UOpenLogicRuntimeWorker* GetRuntimeWorker();

	UFUNCTION(BlueprintPure, Category = "Task")
	int32 GetInputPinNum();

	UFUNCTION(BlueprintPure, Category = "Task")
	int32 GetOutputPinNum();
	

	// Base Events
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Task")
	void OnEditorNodeConstruct();

	UFUNCTION(BlueprintNativeEvent, Category = "Task")
	void OnTaskPreconstruct(AActor* Actor);

	UFUNCTION(BlueprintNativeEvent, Category = "DDL")
	void DynamicLinkLocalVariables();

	UFUNCTION(BlueprintNativeEvent, Category = "Task")
	void OnTaskActivated(AActor* Actor);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Task")
	void OnTaskCompleted(AActor* Actor);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Task")
	void OnEditorNodeSaved();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Task")
	void OnEditorNodeCommit();

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Base", meta = (EditCondition = "bShowBaseProperties", EditConditionHides))
		bool bShowBaseProperties = true;



	// Base Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node", meta = (EditCondition = "bShowBaseProperties", EditConditionHides))
		FNodeInfo NodeInfo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hidden")
		class UOpenLogicRuntimeWorker* RuntimeWorker;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hidden")
		FGuid NodeID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hidden")
		class UOpenLogicBaseTask* PreviousNode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hidden")
		TMap<int32, class UOpenLogicBaseParam*> OutParam;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hidden")
		FString RuntimePayload;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hidden")
		class UNodeBaseWidget* EditorNode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hidden")
		int32 NumInputPins;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hidden")
		int32 NumOutputPins;




};
