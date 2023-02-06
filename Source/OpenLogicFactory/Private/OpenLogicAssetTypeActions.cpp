// Copyright 2022 NegativeNameSeller

#include "OpenLogicAssetTypeActions.h"

FOpenLogicAssetTypeActions::FOpenLogicAssetTypeActions(EAssetTypeCategories::Type InAssetCategory)
	: MyAssetCategory(InAssetCategory)
{
}

FColor FOpenLogicAssetTypeActions::GetTypeColor() const
{
	return FColor::Red;
}

void FOpenLogicAssetTypeActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor)
{
	FSimpleAssetEditor::CreateEditor(EToolkitMode::Standalone, EditWithinLevelEditor, InObjects);
}