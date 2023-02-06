// Copyright 2022 NegativeNameSeller

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"
#include "OpenLogicPrimaryDataAsset.h"



class FOpenLogicAssetTypeActions : public FAssetTypeActions_Base
{
public:
	FOpenLogicAssetTypeActions(EAssetTypeCategories::Type InAssetCategory);

	virtual FColor GetTypeColor() const override;
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;

	// IAssetTypeActions Implementation
	virtual FText GetName() const override { return FText::FromName(TEXT("OpenLogicGraph")); }
	virtual UClass* GetSupportedClass() const override { return UOpenLogicPrimaryDataAsset::StaticClass(); }
	virtual uint32 GetCategories() override { return MyAssetCategory; }

private:
	EAssetTypeCategories::Type MyAssetCategory;
};
