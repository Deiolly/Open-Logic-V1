// Copyright 2022 NegativeNameSeller

#pragma once

#include "CoreMinimal.h"
#include "JsonObjectConverter.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "OpenLogicLibrary.generated.h"

UENUM(BlueprintType)
enum class EMyEnum : uint8
{
	NodeCompleted,
	Completed
};


/**
 * 
 */
UCLASS()
class OPENLOGIC_API UOpenLogicLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:



	UFUNCTION(BlueprintCallable, Category = "Open Logic Functions", Meta = (ExpandEnumAsExecs = "OutputPins"))
	void RunGraph(UPrimaryDataAsset* Graph, EMyEnum& OutputPins);
	
	
	UFUNCTION(BlueprintCallable, Category = "Payload", CustomThunk, meta = (CustomStructureParam = "InStruct"))
	static void StructToPayload(FString& Payload, bool& Success, const UStruct* InStruct);
	DECLARE_FUNCTION(execStructToPayload)
	{
		P_GET_PROPERTY_REF(FStrProperty, Json);
		P_GET_UBOOL_REF(Success);

		Stack.Step(Stack.Object, NULL);

		FProperty* Prop = Stack.MostRecentProperty;
		void* Ptr = Stack.MostRecentPropertyAddress;

		P_FINISH;

		Success = UOpenLogicLibrary::AnyStructToJsonString(Prop, Ptr, Json);
	}

	UFUNCTION(BlueprintCallable, Category = "Payload", CustomThunk, meta = (CustomStructureParam = "OutStruct"))
		static void PayloadToStruct(const FString& Payload, bool& Success, UStruct* & OutStruct);
	DECLARE_FUNCTION(execPayloadToStruct)
	{
		// P_GET_SOFTCLASS_REF(int32, Total);
		P_GET_PROPERTY(FStrProperty, Json);
		P_GET_UBOOL_REF(Success);

		Stack.Step(Stack.Object, NULL);

		FProperty* Prop = Stack.MostRecentProperty;
		void* Ptr = Stack.MostRecentPropertyAddress;

		P_FINISH;

		Success = UOpenLogicLibrary::JsonStringToAnyStruct(Prop, Ptr, Json);
	}

	static bool AnyStructToJsonString(FProperty* Property, void* ValuePtr, FString& Json);
	static TSharedRef<FJsonValue> AnyStructToJsonValue(FProperty* Property, void* ValuePtr);
	static bool JsonStringToAnyStruct(FProperty* Property, void* ValuePtr, const FString& Json);
	static TSharedRef<FJsonValue> JsonValueToAnyStruct(FProperty* Property, TSharedPtr<FJsonValue> Value);

};
