// Copyright 2022 NegativeNameSeller

#include "OpenLogicRuntimeWorker.h"

#if WITH_EDITOR

	#include "OpenLogicEditor.h"
	#include "OpenLogicEditorContext_Manager.h"
	#include "OpenLogicEditorContext_LevelEd.h"

#endif

void UOpenLogicRuntimeWorker::CreateNodes()
{
	for (FGuid& ID : AssetNodeID)
	{
		int32 NodeIndex = AssetNodeID.Find(ID);
		FOLNode& NodeData = AssetNodeData[NodeIndex];

		UOpenLogicBaseTask* BaseObject = NewObject<UOpenLogicBaseTask>(this, NodeData.Task);
		BaseObject->NodeID = ID;
		BaseObject->RuntimePayload = NodeData.Content;
		BaseObject->RuntimeWorker = this;
		CalledNode.Add(ID, BaseObject);

		uint8 InputPins = 0;

		uint8 Len = BaseObject->NodeInfo.Pins.Num();
		for (uint8 i = 0; i < Len; ++i)
		{
			FPinData Data = BaseObject->NodeInfo.Pins[i];
			if (Data.ParamClass != nullptr) {
				if (Data.PinType == EPinType::Output) {
					UOpenLogicBaseParam* OutObj = NewObject<UOpenLogicBaseParam>(BaseObject, Data.ParamClass);
					uint8 Pin = i - InputPins;

					BaseObject->OutParam.Add(Pin, OutObj);
				}
				else {
					if (Data.PinType == EPinType::Input) {
						InputPins++;
					}
				}
			}
			else {
				if (Data.PinType == EPinType::Input) {
					InputPins++;
				}
			}
		}

		BaseObject->OnTaskPreconstruct(Component->GetOwner());
	}
}
void UOpenLogicRuntimeWorker::RunInstance() {
	isInstanceActive = true;

	for (FGuid& ID : AssetNodeID)
	{
		UOpenLogicBaseTask* Task = CalledNode[ID];
		Task->DynamicLinkLocalVariables();
	}
	// Checking if BeginEvent is specified, if true, starting it
	if (BeginEvent != "") {

		GlobalCall(BeginEvent);
	}


}

void UOpenLogicRuntimeWorker::NodeEnded(UOpenLogicBaseTask* BaseTask, int32 PinID) {
	BaseTask->OnTaskCompleted(Component->GetOwner());

	if (ComponentParent != nullptr)
	{
		ComponentParent->OnNodeEnded.Broadcast(BaseTask->NodeID);
	}

	FGuid NodeID = BaseTask->NodeID;
	int32 NodeIndex = AssetNodeID.Find(NodeID);
	FOLNode& NodeData = AssetNodeData[NodeIndex];
	FPinID NodePinID = NodeData.Output[PinID];
	if (NodePinID.UniqueID.IsValid() == true) {
		FGuid NewNodeID1 = NodePinID.UniqueID;
		if (CalledNode.Contains(NewNodeID1)) {
			UOpenLogicBaseTask* Task = CalledNode[NewNodeID1];
			Task->PreviousNode = BaseTask;
			Task->OnTaskActivated(Component->GetOwner());

			if (ComponentParent != nullptr)
			{
				ComponentParent->OnNodeExecuted.Broadcast(NewNodeID1, PinID);
			}

			#if WITH_EDITOR

			FOpenLogicEditorModule& OpenLogicEditorScript = FModuleManager::Get().LoadModuleChecked<FOpenLogicEditorModule>(TEXT("OpenLogicEditor"));
			UOpenLogicEditorContext_LevelEd* LevelEditor = OpenLogicEditorScript.GetContextManager().GetLevelEditorContext();
			LevelEditor->HandleOnNodeEnded(NewNodeID1, BaseTask->NodeID, PinID);

#			endif
		}


	}
	else {
		return;
	}


}

void UOpenLogicRuntimeWorker::GlobalCall(FString Event) {
	if (isInstanceActive == true) {
		if (Event != "") {
			// Preparing GlobalCall
			FGuid* EventID = RegisteredEvent.Find(Event);
			int32 NodeIndex = AssetNodeID.Find(*EventID);
			FOLNode& NodeData = AssetNodeData[NodeIndex];

			if (CalledNode.Contains(*EventID))
			{
				UOpenLogicBaseTask* Task = CalledNode[*EventID];
				Task->OnTaskActivated(Component->GetOwner());

				if (ComponentParent != nullptr)
				{
					ComponentParent->OnNodeExecuted.Broadcast(*EventID, 0);
				}

				return;
			}


		}
	}
}
