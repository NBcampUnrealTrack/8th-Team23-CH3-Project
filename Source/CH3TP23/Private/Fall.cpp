// Fall.cpp

#include "Fall.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"



AFall::AFall()
{
	PrimaryActorTick.bCanEverTick = true;

    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    RootComponent = SceneRoot;

    SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
    SpawnArea->SetupAttachment(RootComponent);

    Timer = 0.0f;
}

void AFall::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    Timer += DeltaTime;

    if (Timer >= SpawnInterval && ActorClassToSpawn)
    {
        Timer = 0.0f;

        FVector SpawnLocation = UKismetMathLibrary::RandomPointInBoundingBox
        (
            SpawnArea->GetComponentLocation(), // 박스 중심 위치
            SpawnArea->GetScaledBoxExtent() // 박스 크기(반지름)
        );

        FVector Loc = GetActorLocation();
        Loc.X += FMath::RandRange(-200.f, 200.f);
        Loc.Y += FMath::RandRange(-200.f, 200.f);
        
        FRotator SpawnRotation = FRotator(FMath::RandRange(0.f, 360.f), FMath::RandRange(0.f, 360.f), FMath::RandRange(0.f, 360.f));
        
        GetWorld()->SpawnActor<AActor>(ActorClassToSpawn, Loc, FRotator::ZeroRotator);
        GetWorld()->SpawnActor<AActor>(ActorClassToSpawn, SpawnLocation, SpawnRotation);
    }
}

