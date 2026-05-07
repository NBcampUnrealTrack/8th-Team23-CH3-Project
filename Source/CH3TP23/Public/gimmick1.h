// gimmick.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "gimmick1.generated.h"

UCLASS()
class CH3TP23_API Agimmick1 : public AActor
{
	GENERATED_BODY()

public:
	Agimmick1(); //생성자

protected:
	UPROPERTY(EditAnywhere)
	int32 MovementType = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "gimmick1|Components")
	USceneComponent* SceneRoot;
	UStaticMeshComponent* StaticMeshComp;

	FVector StartLocation;

	float RotationSpeed;
	float MoveSpeed;
	float MoveDistance;

	virtual void BeginPlay() override; // 게임이 시작되거나 생성될때 호출
	virtual void Tick(float DeltaTime) override; // 모든 프레임 호출

protected:
	
	UPROPERTY(VisibleAnywhere, Category = "Gimmick1")
	class UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere, Category = "Gimmick1")
	float JumpStrength = 750.0f;
	float WindStrength = 100.f; // 선풍기 밀어내는 힘

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp
		, AActor* OtherActor
		, UPrimitiveComponent* OtherComp
		, int32 OtherBodyIndex
		, bool bFromSweep
		, const FHitResult& SweepResult);

protected:
	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<AActor> ActorClassToSpawn;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	float SpawnInterval = 0.5f;

	float SpawnTimer = 0.f;
};