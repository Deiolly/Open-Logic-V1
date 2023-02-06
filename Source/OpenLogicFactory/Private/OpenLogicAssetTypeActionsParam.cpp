// Copyright 2022 NegativeNameSeller

#include "OpenLogicAssetTypeActionsParam.h"

FOpenLogicAssetTypeActionsParam::FOpenLogicAssetTypeActionsParam(EAssetTypeCategories::Type InAssetCategory)
	: MyAssetCategory(InAssetCategory)
{
}

FColor FOpenLogicAssetTypeActionsParam::GetTypeColor() const
{
	return FColor::Red;
}

void FOpenLogicAssetTypeActionsParam::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor)
{
	FSimpleAssetEditor::CreateEditor(EToolkitMode::Standalone, EditWithinLevelEditor, InObjects);
}