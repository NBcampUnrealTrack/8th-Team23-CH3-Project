#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "T23Interface.h"
#include "Door.generated.h"

UCLASS()
class CH3TP23_API ADoor : public AActor, public IT23Interface
{
	GENERATED_BODY()
	
public:	
	
	ADoor();

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;

public:	
	
	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation();

};
