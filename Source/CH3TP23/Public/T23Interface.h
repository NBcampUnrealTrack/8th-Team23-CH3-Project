#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "T23Interface.generated.h"


UINTERFACE(MinimalAPI)
class UT23Interface : public UInterface
{
	GENERATED_BODY()
};


class CH3TP23_API IT23Interface
{
	GENERATED_BODY()

	
public:

	virtual void Interact() = 0;
};
