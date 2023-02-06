// Copyright 2022 NegativeNameSeller

#include "OpenLogicFactory.h"
#include "IAssetTools.h"
#include "AssetToolsModule.h"
#include "OpenLogicAssetTypeActions.h"
#include "OpenLogicAssetTypeActionsNode.h"
#include "OpenLogicAssetTypeActionsParam.h"

#define LOCTEXT_NAMESPACE "FOpenLogicFactoryModule"

void FOpenLogicFactoryModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	EAssetTypeCategories::Type gameAssetCategory = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("OpenLogic")), FText::FromName(TEXT("OpenLogic")));

	TSharedPtr<IAssetTypeActions> actionType = MakeShareable(new FOpenLogicAssetTypeActions(gameAssetCategory));
	AssetTools.RegisterAssetTypeActions(actionType.ToSharedRef());

	TSharedPtr<IAssetTypeActions> actionTypeNode = MakeShareable(new FOpenLogicAssetTypeActionsNode(gameAssetCategory));
	AssetTools.RegisterAssetTypeActions(actionTypeNode.ToSharedRef());
	
	TSharedPtr<IAssetTypeActions> actionTypeParam = MakeShareable(new FOpenLogicAssetTypeActionsParam(gameAssetCategory));
	AssetTools.RegisterAssetTypeActions(actionTypeParam.ToSharedRef());
}

void FOpenLogicFactoryModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.


}



#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FOpenLogicFactoryModule, OpenLogicFactory)