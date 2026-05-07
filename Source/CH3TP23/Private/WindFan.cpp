// WindFan.cpp


#include "WindFan.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

AWindFan::AWindFan()
{
	PrimaryActorTick.bCanEverTick = true;

    WindArea = CreateDefaultSubobject<UBoxComponent>(TEXT("WindArea"));
    RootComponent = WindArea;

}


void AWindFan::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);

    TArray<AActor*> OverlappingActors;
    WindArea->GetOverlappingActors(OverlappingActors, ACharacter::StaticClass());

    for (AActor* Actor : OverlappingActors) {
        if (ACharacter* Character = Cast<ACharacter>(Actor)) 
        {
            FVector LaunchDirection = GetActorForwardVector() * 500.0f;
            Character->LaunchCharacter(LaunchDirection, true, true);
        }
    }
}
