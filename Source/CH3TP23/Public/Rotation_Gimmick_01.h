//Rotation_Gimmick_01.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Rotation_Gimmick_01.generated.h"

UCLASS()
class CH3TP23_API ARotation_Gimmick_01 : public AActor
{
	GENERATED_BODY()
	
public:	
	ARotation_Gimmick_01();

protected:

public:	
	virtual void Tick(float DeltaTime) override;

};
