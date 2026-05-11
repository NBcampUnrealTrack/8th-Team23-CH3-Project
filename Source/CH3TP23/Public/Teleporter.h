#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Teleporter.generated.h"

UCLASS()
class CH3TP23_API ATeleporter : public AActor
{
    GENERATED_BODY()

public:
    ATeleporter();

protected:
    virtual void BeginPlay() override;

protected:
    UPROPERTY(VisibleAnywhere, Category = "Teleporter")
    class USceneComponent* SceneRoot;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleporter")
    class UStaticMeshComponent* StaticMeshComp;

    UPROPERTY(VisibleAnywhere, Category = "Teleporter")
    class UBoxComponent* TeleportVolume;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleporter|Settings")
    class ATeleporter* TargetPortal;

    bool bCanTeleport = true;
    FTimerHandle TeleportCooldownTimerHandle;

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult);

    void ResetTeleportCooldown();
};