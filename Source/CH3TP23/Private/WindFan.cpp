// WindFan.cpp


#include "WindFan.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

AWindFan::AWindFan()
{
	PrimaryActorTick.bCanEverTick = true;

    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    SetRootComponent(SceneRoot);

    StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    StaticMeshComp->SetupAttachment(SceneRoot);

    WindArea = CreateDefaultSubobject<UBoxComponent>(TEXT("WindArea"));
    WindArea->SetupAttachment(SceneRoot);
}

void AWindFan::BeginPlay()
{
    Super::BeginPlay();

    WindArea->OnComponentBeginOverlap.AddDynamic(this, &AWindFan::OnOverlapBegin);
}

void AWindFan::OnOverlapBegin(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (WindType == EWindType::Constant) return;

    ACharacter* Character = Cast<ACharacter>(OtherActor);

    if (Character)
    {
        FVector LaunchDir = Character->GetActorLocation() - GetActorLocation();
        LaunchDir.Normalize();

        Character->LaunchCharacter(LaunchDir * BounceStrength * 1.5f, true, true);
    }
}

void AWindFan::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);

    if (WindType == EWindType::Bounce) return;

    TArray<AActor*> OverlappingActors;
    WindArea->GetOverlappingActors(OverlappingActors, ACharacter::StaticClass());

    for (AActor* Actor : OverlappingActors) 
    {
        ACharacter* Character = Cast<ACharacter>(Actor);

        if (Character) 
        {
            FVector PushDir = GetActorForwardVector();
            //Character->GetCharacterMovement()->AddForce(PushDir * ConstantStrength * true);
            Character->LaunchCharacter(PushDir * ConstantStrength * DeltaTime, false, false);
        }
    }
}
