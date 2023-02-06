// Copyright 2022 NegativeNameSeller

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OpenLogicRuntimeInstancer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOpenLogicRuntimeOnNodeExecutedEvent, const FGuid&, NodeID, int32, PinID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOpenLogicRuntimeOnNodeEndedEvent, const FGuid&, NodeID);

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OPENLOGIC_API UOpenLogicRuntimeInstancer : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenLogicRuntimeInstancer();

	UPROPERTY(BlueprintAssignable, Category = "OpenLogicRuntimeDelegate")
		FOpenLogicRuntimeOnNodeExecutedEvent OnNodeExecuted;

	UPROPERTY(BlueprintAssignable, Category = "OpenLogicRuntimeDelegate")
		FOpenLogicRuntimeOnNodeEndedEvent OnNodeEnded;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Instancer", meta = (ExposeOnSpawn))
		UOpenLogicPrimaryDataAsset* GraphAsset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Instancer", meta = (ExposeOnSpawn))
		bool Run;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Instancer", meta = (ExposeOnSpawn))
		FString StartEvent;
	UPROPERTY(BlueprintReadWrite, Category = "Runtime")
		UOpenLogicRuntimeWorker* Instance;
	UFUNCTION(BlueprintCallable, Category = "Runtime")
		UOpenLogicRuntimeWorker* CreateInstance();



};
