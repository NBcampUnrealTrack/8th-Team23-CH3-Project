//Teleporter.cpp

#include "Teleporter.h"
#include "T23Character.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"

ATeleporter::ATeleporter()
{
    PrimaryActorTick.bCanEverTick = false;

    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    SetRootComponent(SceneRoot);

    StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    StaticMeshComp->SetupAttachment(SceneRoot);

    TeleportVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("TeleportVolume"));
    TeleportVolume->SetupAttachment(SceneRoot);
}

void ATeleporter::BeginPlay()
{
    Super::BeginPlay();

    TeleportVolume->OnComponentBeginOverlap.AddDynamic(
        this,
        &ATeleporter::OnOverlapBegin);
}

void ATeleporter::OnOverlapBegin(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (!bCanTeleport || OtherActor == nullptr || TargetPortal == nullptr)
    {
        return;
    }

    if (OtherActor == this || OtherActor == TargetPortal)
    {
        return;
    }

    AT23Character* Character =
        Cast<AT23Character>(OtherActor);

    if (Character)
    {
        FVector TargetLocation =
            TargetPortal->GetActorLocation();

        bCanTeleport = false;

        Character->SetActorLocation(
            TargetLocation,
            false,
            nullptr,
            ETeleportType::TeleportPhysics);

        // 점수 시스템 시작
        Character->StartScoreSystem();

        TargetPortal->bCanTeleport = false;

        GetWorldTimerManager().SetTimer(
            TeleportCooldownTimerHandle,
            this,
            &ATeleporter::ResetTeleportCooldown,
            1.0f,
            false);

        GetWorldTimerManager().SetTimer(
            TargetPortal->TeleportCooldownTimerHandle,
            TargetPortal,
            &ATeleporter::ResetTeleportCooldown,
            1.0f,
            false);
    }
}

void ATeleporter::ResetTeleportCooldown()
{
    bCanTeleport = true;
}