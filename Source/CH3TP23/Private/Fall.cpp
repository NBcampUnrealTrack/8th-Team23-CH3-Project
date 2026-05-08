// Fall.cpp

#include "Fall.h"

AFall::AFall()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AFall::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (Timer >= SpawnInterval && ActorClassToSpawn)
    {
        Timer = 0.f;

        FVector Loc = GetActorLocation(); // À§Ä¡ ·£´ý ÁÂÇ¥ °è»ê
        Loc.X += FMath::RandRange(-200.f, 200.f);
        Loc.Y += FMath::RandRange(-200.f, 200.f);

        GetWorld()->SpawnActor<AActor>(ActorClassToSpawn, Loc, FRotator::ZeroRotator);
    }
}

