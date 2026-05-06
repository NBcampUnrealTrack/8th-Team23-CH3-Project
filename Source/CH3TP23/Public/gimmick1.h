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

	USceneComponent* SceneRoot;
	UStaticMeshComponent* StaticMeshComp;

	FVector StartLocation;

	float RotationSpeed;
	float MoveSpeed;
	float MoveDistance;

	virtual void BeginPlay() override; // 게임이 시작되거나 생성될때 호출
	virtual void Tick(float DeltaTime) override; // 모든 프레임 호출

protected:
	UPROPERTY(VisibleAnywhere, Category = "Gimmick")
	class UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere, Category = "Gimmick")
	float JumpStrength = 750.0f;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp
		, AActor* OtherActor
		, UPrimitiveComponent* OtherComp
		, int32 OtherBodyIndex
		, bool bFromSweep
		, const FHitResult& SweepResult);

};