// gimmick.cpp


#include "gimmick1.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

Agimmick1::Agimmick1()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh")); //CreateDefaultSubobject 컴포넌트를 생성
	StaticMeshComp->SetupAttachment(SceneRoot);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/SM_Shelf.SM_Shelf"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Resources/Materials/M_Metal_Steel.M_Metal_Steel"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	}

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &Agimmick1::OnOverlapBegin);

	PrimaryActorTick.bCanEverTick = true;
	RotationSpeed = 90.0f;
	MoveSpeed = 5.0f;
	MoveDistance = 200.0;

}

void Agimmick1::BeginPlay()
{
	Super::BeginPlay();

	//SetActorLocation(FVector(0.0f, 0.0f, 90.0f));
	//SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
	//SetActorScale3D(FVector(2.0f));

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

	else if (MovementType == 4)
	{
		SpawnTimer += DeltaTime;
		if (SpawnTimer >= SpawnInterval && ActorClassToSpawn)
		{
			SpawnTimer = 0.f;
			FVector SpawnPos = GetActorLocation() + FVector(FMath::RandRange(-200.f, 200.f), FMath::RandRange(-200.f, 200.f), 0.f);
			GetWorld()->SpawnActor<AActor>(ActorClassToSpawn, SpawnPos, FRotator::ZeroRotator);
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
