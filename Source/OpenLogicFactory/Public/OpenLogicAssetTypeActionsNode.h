// Copyright 2022 NegativeNameSeller

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"
#include "OpenLogicBaseTask.h"



class FOpenLogicAssetTypeActionsNode : public FAssetTypeActions_Base
{
public:
	FOpenLogicAssetTypeActionsNode(EAssetTypeCategories::Type InAssetCategory);

	virtual FColor GetTypeColor() const override;
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;

	// IAssetTypeActions Implementation
	virtual FText GetName() const override { return FText::FromName(TEXT("OpenLogicTaskNode")); }
	virtual UClass* GetSupportedClass() const override { return UOpenLogicBaseTask::StaticClass(); }
	virtual uint32 GetCategories() override { return MyAssetCategory; }

private:
	EAssetTypeCategories::Type MyAssetCategory;
};
