// Copyright 2022 NegativeNameSeller

#include "OpenLogicAssetTypeActionsNode.h"

FOpenLogicAssetTypeActionsNode::FOpenLogicAssetTypeActionsNode(EAssetTypeCategories::Type InAssetCategory)
	: MyAssetCategory(InAssetCategory)
{
}

FColor FOpenLogicAssetTypeActionsNode::GetTypeColor() const
{
	return FColor::Red;
}

void FOpenLogicAssetTypeActionsNode::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor)
{
	FSimpleAssetEditor::CreateEditor(EToolkitMode::Standalone, EditWithinLevelEditor, InObjects);
}