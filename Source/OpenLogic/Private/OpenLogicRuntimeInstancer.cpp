// Copyright 2022 NegativeNameSeller

#include "OpenLogicRuntimeInstancer.h"
#include "Runtime/Engine/Public/EngineGlobals.h"
#include "OpenLogicPrimaryDataAsset.h"
#include "OpenLogicRuntimeWorker.h"

// Sets default values for this component's properties
UOpenLogicRuntimeInstancer::UOpenLogicRuntimeInstancer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenLogicRuntimeInstancer::BeginPlay()
{
	Super::BeginPlay(); 
	
	CreateInstance();
	Instance->CreateNodes();
	if (Run == true)
	{
		Instance->RunInstance();
	}

	
}


// Called every frame
void UOpenLogicRuntimeInstancer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
} 

UOpenLogicRuntimeWorker* UOpenLogicRuntimeInstancer::CreateInstance()
{
	TArray<FGuid> MapKeys;
	GraphAsset->Node.GetKeys(MapKeys);

	TArray<FOLNode> MapValues;
	GraphAsset->Node.GenerateValueArray(MapValues);
	
	Instance = NewObject<UOpenLogicRuntimeWorker>(this);
	Instance->AssetNodeID = MapKeys;
	Instance->AssetNodeData = MapValues;
	Instance->Asset = GraphAsset;
	Instance->RegisteredEvent = GraphAsset->Events;
	Instance->BeginEvent = StartEvent;
	Instance->ComponentParent = this;
	Instance->Component = this;

	return Instance;
}

