#include "Door.h"


ADoor::ADoor()
{
 	
	PrimaryActorTick.bCanEverTick = false;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	RootComponent = MeshComp;
  

   

}


void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ADoor::Interact_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Open the door"));
}