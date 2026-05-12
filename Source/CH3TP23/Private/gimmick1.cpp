// gimmick.cpp


#include "gimmick1.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

Agimmick1::Agimmick1()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);
	SceneRoot->SetMobility(EComponentMobility::Movable);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(SceneRoot);

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &Agimmick1::OnOverlapBegin);

	PrimaryActorTick.bCanEverTick = true;
	RotationSpeed = 90.0f;
	MoveSpeed = 5.0f;
	MoveDistance = 200.0;

}

void Agimmick1::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
}

void Agimmick1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MovementType == 0) //(!FMath::IsNearlyZero(RotationSpeed))
	{
		AddActorLocalRotation(FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f));
	}

	else if (MovementType == 1)
	{
		FVector NewLocation = StartLocation;

		float Movement = FMath::Sin(GetGameTimeSinceCreation() * MoveSpeed) * MoveDistance;
		NewLocation.X += Movement;
		SetActorLocation(NewLocation);

		//AddActorLocalOffset(FVector(0.0f, 100.0f, 160.0f));
	}

	else if (MovementType == 3)
	{
		TArray<AActor*> OverlappingActors;
		CollisionBox->GetOverlappingActors(OverlappingActors, ACharacter::StaticClass());
		for (AActor* Actor : OverlappingActors)
		{
			if (ACharacter* Character = Cast<ACharacter>(Actor))
			{
				Character->GetCharacterMovement()->AddInputVector(GetActorForwardVector() * WindStrength);
			}
		}
	}
}

void Agimmick1::OnOverlapBegin(UPrimitiveComponent* OverlappedComp
	, AActor* OtherActor
	, UPrimitiveComponent* OtherComp
	, int32 OtherBodyIndex
	, bool bFromSweep
	, const FHitResult& SweepResult)
{
	if (MovementType == 2 && OtherActor && (OtherActor != this))
	{
		ACharacter* Character = Cast<ACharacter>(OtherActor);

		if (Character)
		{
			FVector LaunchDirection = GetActorUpVector() * JumpStrength;
			Character->LaunchCharacter(LaunchDirection, false, true);
		}
	}
}

void Agimmick1::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (MaterialAssets)
	{
		StaticMeshComp->SetMaterial(0, MaterialAssets);
	}

	if (MeshAsset)
	{
		StaticMeshComp->SetStaticMesh(MeshAsset);
	}
}