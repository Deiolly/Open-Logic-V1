// Copyright 2022 NegativeNameSeller


#include "OpenLogicLibrary.h"


UENUM(BlueprintType)

void UOpenLogicLibrary::RunGraph(UPrimaryDataAsset* Graph, EMyEnum& OutputPins) {
	FString s = "ss";
	UE_LOG(LogTemp, Warning, TEXT("%s"), *s);

	
}

bool UOpenLogicLibrary::AnyStructToJsonString(FProperty* Property, void* ValuePtr, FString& Json)
{
	bool Success = false;
	if (!Property || ValuePtr == NULL)
	{
		return Success;
	}
	TSharedRef<TJsonWriter<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>> JsonWriter = TJsonWriterFactory<TCHAR, TPrettyJsonPrintPolicy<TCHAR>>::Create(&Json, 0);
	// convert to json
	auto JsonValue = UOpenLogicLibrary::AnyStructToJsonValue(Property, ValuePtr);
	// serialize
	if (JsonValue->Type == EJson::Object)
	{
		Success = FJsonSerializer::Serialize(JsonValue->AsObject().ToSharedRef(), JsonWriter);
	}
	else if (JsonValue->Type == EJson::Array)
	{
		Success = FJsonSerializer::Serialize(JsonValue->AsArray(), JsonWriter);
	}
	JsonWriter->Close();
	return Success;
}
TSharedRef<FJsonValue> UOpenLogicLibrary::AnyStructToJsonValue(FProperty* Property, void* ValuePtr)
{
	if (ValuePtr == NULL || Property == NULL)
	{
		return MakeShareable(new FJsonValueNull());
	}
	// array
	else if (FArrayProperty* arrayProperty = CastField<FArrayProperty>(Property))
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		auto Helper = FScriptArrayHelper::CreateHelperFormInnerProperty(arrayProperty->Inner, ValuePtr);
		for (int32 ArrayIndex = 0; ArrayIndex < Helper.Num(); ArrayIndex++)
		{
			Array.Add(UOpenLogicLibrary::AnyStructToJsonValue(arrayProperty->Inner, Helper.GetRawPtr(ArrayIndex)));
		}
		return MakeShareable(new FJsonValueArray(Array));
	}
	// set
	else if (FSetProperty* setProperty = CastField<FSetProperty>(Property))
	{
		TArray<TSharedPtr<FJsonValue>> Array;
		auto Helper = FScriptSetHelper::CreateHelperFormElementProperty(setProperty->ElementProp, ValuePtr);
		for (int32 ArrayIndex = 0; ArrayIndex < Helper.Num(); ++ArrayIndex)
		{
			Array.Add(UOpenLogicLibrary::AnyStructToJsonValue(setProperty->ElementProp, Helper.GetElementPtr(ArrayIndex)));
		}
		return MakeShareable(new FJsonValueArray(Array));
	}
	// map 
	else if (FMapProperty* mapProperty = CastField<FMapProperty>(Property))
	{
		TSharedRef<FJsonObject> JsonObject = MakeShared<FJsonObject>();
		auto Helper = FScriptMapHelper::CreateHelperFormInnerProperties(mapProperty->KeyProp, mapProperty->ValueProp, ValuePtr);
		for (int32 ArrayIndex = 0; ArrayIndex < Helper.Num(); ++ArrayIndex)
		{
			FString KeyStr;
			auto Key = UOpenLogicLibrary::AnyStructToJsonValue(mapProperty->KeyProp, Helper.GetKeyPtr(ArrayIndex));
			if (!Key->TryGetString(KeyStr))
			{
				mapProperty->KeyProp->ExportTextItem(KeyStr, Helper.GetKeyPtr(ArrayIndex), nullptr, nullptr, 0);
				if (KeyStr.IsEmpty())
				{
					UE_LOG(LogTemp, Warning, TEXT("AnyStructToJsonValue : Error serializing key in map property at index %i, using empty string as key"), ArrayIndex);
				}
			}
			auto Val = UOpenLogicLibrary::AnyStructToJsonValue(mapProperty->ValueProp, Helper.GetValuePtr(ArrayIndex));
			JsonObject->SetField(KeyStr, Val);
		}
		return MakeShareable(new FJsonValueObject(JsonObject));
	}
	// struct
	else if (FStructProperty* structProperty = CastField<FStructProperty>(Property))
	{
		TSharedRef<FJsonObject> JsonObject = MakeShared<FJsonObject>();
		for (TFieldIterator<FProperty> It(structProperty->Struct); It; ++It)
		{
			FProperty* Prop = *It;
			JsonObject->SetField(Prop->GetAuthoredName(), UOpenLogicLibrary::AnyStructToJsonValue(Prop, Prop->ContainerPtrToValuePtr<void*>(ValuePtr)));
		}
		return MakeShareable(new FJsonValueObject(JsonObject));
	}
	// object
	else if (FObjectProperty* objectProperty = CastField<FObjectProperty>(Property))
	{
		void* PropValue = objectProperty->GetObjectPropertyValue(ValuePtr);
		if (PropValue == NULL)
		{
			return MakeShareable(new FJsonValueNull());
		}
		if (objectProperty->PropertyClass->IsNative())
		{
			auto Value = FJsonObjectConverter::UPropertyToJsonValue(Property, ValuePtr, 0, 0);
			return Value.ToSharedRef();
		}
		TSharedRef<FJsonObject> JsonObject = MakeShared<FJsonObject>();
		for (TFieldIterator<FProperty> It(objectProperty->PropertyClass); It; ++It)
		{
			FProperty* Prop = *It;
			JsonObject->SetField(Prop->GetAuthoredName(), UOpenLogicLibrary::AnyStructToJsonValue(Prop, Prop->ContainerPtrToValuePtr<void*>(PropValue)));
		}
		return MakeShareable(new FJsonValueObject(JsonObject));
	}
	// scalar
	else
	{
		auto Value = FJsonObjectConverter::UPropertyToJsonValue(Property, ValuePtr, 0, 0);
		return Value.ToSharedRef();


	}



}
bool UOpenLogicLibrary::JsonStringToAnyStruct(FProperty* Property, void* ValuePtr, const FString& Json)
{
	bool Success = false;
	if (!Property || !ValuePtr || Json.IsEmpty())
	{
		return Success;
	}
	TSharedPtr<FJsonValue> JsonValue;
	TSharedRef<TJsonReader<> > JsonReader = TJsonReaderFactory<>::Create(Json);
	if (FJsonSerializer::Deserialize(JsonReader, JsonValue) && JsonValue.IsValid())
	{
		auto InJsonValue = UOpenLogicLibrary::JsonValueToAnyStruct(Property, JsonValue);
		if ((InJsonValue->Type == EJson::Array && InJsonValue->AsArray().Num() != 0) || (InJsonValue->Type == EJson::Object && InJsonValue->AsObject()->Values.Num() != 0))
		{
			Success = FJsonObjectConverter::JsonValueToUProperty(InJsonValue, Property, ValuePtr, 0, 0);
		}
	}
	return Success;
}
TSharedRef<FJsonValue> UOpenLogicLibrary::JsonValueToAnyStruct(FProperty* Property, TSharedPtr<FJsonValue> Value)
{
	if (!Value.IsValid() || Value->IsNull() || Property == NULL)
	{
		return MakeShareable(new FJsonValueNull());
	}
	// array
	else if (FArrayProperty* arrayProperty = CastField<FArrayProperty>(Property))
	{
		TArray<TSharedPtr<FJsonValue>> OutArray;
		if (Value->Type == EJson::Array)
		{
			auto InArray = Value->AsArray();
			for (int32 ArrayIndex = 0; ArrayIndex < InArray.Num(); ArrayIndex++)
			{
				OutArray.Add(UOpenLogicLibrary::JsonValueToAnyStruct(arrayProperty->Inner, InArray[ArrayIndex]));
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("JsonValueToAnyStruct: error while converting JsonValue to array, type %i is invalid with array property, returning empty array"), Value->Type);
		}
		return MakeShareable(new FJsonValueArray(OutArray));
	}
	// set
	else if (FSetProperty* setProperty = CastField<FSetProperty>(Property))
	{
		TArray<TSharedPtr<FJsonValue>> OutSet;
		if (Value->Type == EJson::Array)
		{
			auto InSet = Value->AsArray();
			for (int32 ArrayIndex = 0; ArrayIndex < InSet.Num(); ArrayIndex++)
			{
				OutSet.Add(UOpenLogicLibrary::JsonValueToAnyStruct(setProperty->ElementProp, InSet[ArrayIndex]));
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("JsonValueToAnyStruct: error while converting JsonValue to set, type %i is invalid with set property, returning empty set"), Value->Type);
		}
		return MakeShareable(new FJsonValueArray(OutSet));
	}
	// map
	else if (FMapProperty* mapProperty = CastField<FMapProperty>(Property))
	{
		TSharedRef<FJsonObject> OutMap = MakeShared<FJsonObject>();
		if (Value->Type == EJson::Object)
		{
			auto InMap = Value->AsObject();
			for (auto Val : InMap->Values)
			{
				OutMap->SetField(Val.Key, UOpenLogicLibrary::JsonValueToAnyStruct(mapProperty->ValueProp, Val.Value));
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("JsonValueToAnyStruct: error while converting JsonValue to map, type %i is invalid with map property, returning empty object"), Value->Type);
		}
		return MakeShareable(new FJsonValueObject(OutMap));
	}
	// struct
	else if (FStructProperty* structProperty = CastField<FStructProperty>(Property))
	{
		TSharedRef<FJsonObject> OutObject = MakeShared<FJsonObject>();
		if (Value->Type == EJson::Object)
		{
			auto InObject = Value->AsObject();
			for (TFieldIterator<FProperty> It(structProperty->Struct); It; ++It)
			{
				FProperty* Prop = *It;
				if (InObject->HasField(Prop->GetAuthoredName()))
				{
					OutObject->SetField(Prop->GetName(), UOpenLogicLibrary::JsonValueToAnyStruct(Prop, InObject->Values.Find(Prop->GetAuthoredName())->ToSharedRef()));
				}
				else if (InObject->HasField(Prop->GetName()))
				{
					OutObject->SetField(Prop->GetName(), UOpenLogicLibrary::JsonValueToAnyStruct(Prop, InObject->Values.Find(Prop->GetName())->ToSharedRef()));
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("JsonValueToAnyStruct: error while converting JsonValue to struct, type %i is invalid with struct property, returning empty object"), Value->Type);
		}
		return MakeShareable(new FJsonValueObject(OutObject));
	}
	// object
	else if (FObjectProperty* objectProperty = CastField<FObjectProperty>(Property))
	{
		TSharedRef<FJsonObject> OutObject = MakeShared<FJsonObject>();
		if (objectProperty->PropertyClass->IsNative())
		{
			return Value.ToSharedRef();
		}
		if (Value->Type == EJson::Object)
		{
			auto InObject = Value->AsObject();
			for (TFieldIterator<FProperty> It(objectProperty->PropertyClass); It; ++It)
			{
				FProperty* Prop = *It;
				if (InObject->HasField(Prop->GetAuthoredName()))
				{
					OutObject->SetField(Prop->GetName(), UOpenLogicLibrary::JsonValueToAnyStruct(Prop, InObject->Values.Find(Prop->GetAuthoredName())->ToSharedRef()));
				}
				else if (InObject->HasField(Prop->GetName()))
				{
					OutObject->SetField(Prop->GetName(), UOpenLogicLibrary::JsonValueToAnyStruct(Prop, InObject->Values.Find(Prop->GetName())->ToSharedRef()));
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("JsonValueToAnyStruct: error while converting JsonValue to object, type %i is invalid with object property, returning empty object"), Value->Type);
		}
		return MakeShareable(new FJsonValueObject(OutObject));
	}
	// scalar
	else
	{
		return Value.ToSharedRef();
	}
}