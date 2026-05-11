//FallingObject.cpp

#include "FallingObject.h"

AFallingObject::AFallingObject()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AFallingObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFallingObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

