//gimmick.h

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
	class USceneComponent* SceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "gimmick1|Components")
	class UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "gimmick1|Assets")
	class UMaterialInterface* MaterialAssets;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "gimmick1|Assets")
	class UStaticMesh* MeshAsset;

	FVector StartLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "gimmick1|Rotation", meta = (EditCondition = "MovementType == 0"))
	float RotationSpeed = 90.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "gimmick1|Movement", meta = (EditCondition = "MovementType == 1"))
	float MoveSpeed = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "gimmick1|Movement", meta = (EditCondition = "MovementType == 1"))
	float MoveDistance = 200.0f;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& Transform) override;

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

};