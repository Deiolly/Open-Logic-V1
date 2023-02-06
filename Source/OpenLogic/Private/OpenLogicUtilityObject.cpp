// Copyright 2022 NegativeNameSeller

#include "OpenLogicUtilityObject.h"
#include "Engine.h"

TArray<FAssetData> UOpenLogicUtilityObject::GetAssetsByClass(const FString& Path, TSubclassOf<UObject> ObjectClass)
{
	TArray<FAssetData> AssetDatas;

	UObjectLibrary* ObjectLibrary = UObjectLibrary::CreateLibrary(ObjectClass, false, GIsEditor);

	ObjectLibrary->AddToRoot();
	int32 NumOfAssetDatas = ObjectLibrary->LoadAssetDataFromPath(Path);
	ObjectLibrary->GetAssetDataList(AssetDatas);
	return AssetDatas;
	
}
