// Copyright 2022 NegativeNameSeller


#include "OpenLogicBaseTask.h"

UWorld* UOpenLogicBaseTask::GetWorld() const
{
	if (GIsEditor && !GIsPlayInEditorWorld) return nullptr;
	else if (GetOuter()) return GetOuter()->GetWorld();
	else return nullptr;
}


void UOpenLogicBaseTask::OnEditorNodeConstruct_Implementation()
{}

void UOpenLogicBaseTask::DynamicLinkLocalVariables_Implementation()
{}

void UOpenLogicBaseTask::OnTaskPreconstruct_Implementation(AActor* Actor)
{}

void UOpenLogicBaseTask::OnTaskActivated_Implementation(AActor* Actor)
{}

void UOpenLogicBaseTask::OnTaskCompleted_Implementation(AActor* Actor)
{}

void UOpenLogicBaseTask::OnEditorNodeSaved_Implementation()
{}

void UOpenLogicBaseTask::OnEditorNodeCommit_Implementation()
{}

UOpenLogicRuntimeWorker* UOpenLogicBaseTask::GetRuntimeWorker()
{
	return RuntimeWorker;
}

int32 UOpenLogicBaseTask::GetInputPinNum()
{
	return NumInputPins;
}

int32 UOpenLogicBaseTask::GetOutputPinNum()
{
	return NumOutputPins;
}
